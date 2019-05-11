/*
 * Copyright (C) 2015 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "PowerHAL"

#include <hardware/hardware.h>
#include <hardware/power.h>

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <utils/Log.h>

#include "power.h"

/* touchkeys */
#define TK_POWER "/sys/class/input/input1/enabled"
/* touchscreen */
const char* TS_PATHS[] =
{
    /* Don't know what thoses devices are, but disable them too :) */
    "/sys/devices/platform/aksm/power",
    "/sys/bus/i2c/devices/3-0020/power",
    "/sys/class/graphics/fb0/device/power",                   // screen framebuffer
    "/sys/class/graphics/fb1/device/power",                   // screen overlay framebuffer
    "/sys/bus/platform/drivers/mmp-vdma/d4209000.vdma/power",
    "/sys/bus/platform/drivers/mmp-disp/mmp-disp/power",      // screen display
    NULL,
};

/* This will hold all the paths that can be disabled */
const char** TS_POWER = NULL;
static int TS_NUMBER = 0;

static int is_init = 0;

#define CPUFREQ_PATH "/sys/devices/system/cpu/cpu0/cpufreq/"
#define INTERACTIVE_PATH "/sys/devices/system/cpu/cpufreq/interactive/"

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static int boostpulse_fd = -1;

static int current_power_profile = PROFILE_BALANCED;
static int requested_power_profile = -1;

static int sysfs_write_str(char *path, char *s)
{
    char buf[80];
    int len;
    int ret = 0;
    int fd;

    fd = open(path, O_WRONLY);
    if (fd < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error opening %s: %s\n", path, buf);
        return -1 ;
    }

    len = write(fd, s, strlen(s));
    if (len < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error writing to %s: %s\n", path, buf);
        ret = -1;
    }

    close(fd);

    return ret;
}

static int sysfs_write_int(char *path, int value)
{
    char buf[80];
    snprintf(buf, 80, "%d", value);
    return sysfs_write_str(path, buf);
}

static bool check_governor(void)
{
    struct stat s;
    int err = stat(INTERACTIVE_PATH, &s);
    if (err != 0) return false;
    if (S_ISDIR(s.st_mode)) return true;
    return false;
}

static int is_profile_valid(int profile)
{
    return profile >= 0 && profile < PROFILE_MAX;
}

int is_pm_supported( const char *control, const char *runtime )
{
    char buff[12];
    int fd;

    if( access(control, F_OK) < 0 )
        return 0;
    
    fd = open(runtime, 0);
    if( fd < 0 )
        return 0;

    if( read(fd, buff, sizeof(buff)-1) < 0 )
    {
        close(fd);
        return 0;
    }

    close(fd);
    if( !strncmp(buff, "unsupported", 11) )
        return 0;

    /* Runtime power mode is supported! */
    return 1;
}

void wait_pm_changed( const char *device_path, int on )
{
    const char *state;
    char *runtime;
    int retry = 1000;
    int fd;
    char buff[80];

    if( on ) state = "active";
    else     state = "suspended";

    runtime = (char*)malloc(strlen(device_path) + strlen("/runtime_status") + 1);
    strcpy(runtime, device_path);
    strcat(runtime, "/runtime_status");

    while( retry-- > 0 )
    {
        fd = open(runtime, 0);
        if( fd < 0 )
            break;
        if( read(fd, buff, sizeof(buff)-1) < 0 )
        {
            close(fd);
            break;
        }
        close(fd);
        if( !strncmp(buff, "unsupported", 11) )
            break;
        if( !strncmp(buff, state, strlen(state)) )
            break;

        usleep(1000);
    }
    free(runtime);
}

static void power_init(__attribute__((unused)) struct power_module *module)
{
    ALOGI("%s", __func__);
    char *control, *runtime;
    const char **device_path;
    
    pthread_mutex_lock(&lock);
    if( !is_init )
    {
        /* Make the list of the devices that can be disabled at runtime */
        for( device_path = TS_PATHS; *device_path != NULL; ++device_path )
        {
            control = (char*)malloc(strlen(*device_path) + strlen("/control") + 1);
            runtime = (char*)malloc(strlen(*device_path) + strlen("/runtime_status") + 1);
            strcpy(control, *device_path);
            strcat(control, "/control");
            strcpy(runtime, *device_path);
            strcat(runtime, "/runtime_status");
            if( is_pm_supported(control, runtime) )
            {
                ALOGD("%s support runtime pm", *device_path);
                TS_POWER = realloc(TS_POWER, sizeof(char**)*TS_NUMBER+1);
                TS_POWER[TS_NUMBER++] = *device_path;
            }
            else
                ALOGD("%s doesn't support runtime pm", *device_path);
            free(control);
            free(runtime);
        }
        is_init = 1;
    }
    pthread_mutex_unlock(&lock);
}

static int boostpulse_open()
{
    pthread_mutex_lock(&lock);
    if (boostpulse_fd < 0) {
        boostpulse_fd = open(INTERACTIVE_PATH "boostpulse", O_WRONLY);
    }
    pthread_mutex_unlock(&lock);

    return boostpulse_fd;
}

static void power_set_interactive_ext(int on) {
    ALOGD("%s: %s input devices", __func__, on ? "enabling" : "disabling");
    char *device_control;
    const char** device_path = (on ? &TS_POWER[TS_NUMBER-1] : TS_POWER );

    int i;
    int start, end, inc;
    if( on )
    {
        start = TS_NUMBER-1;
        end = -1;
        inc = -1;
    }
    else
    {
        start = 0;
        end = TS_NUMBER;
        inc = 1;
    }

    for( i = start; i != end; i+=inc )
    {
        device_control = (char*)malloc(strlen(TS_POWER[i]) + strlen("/control") + 1);
        strcpy(device_control, TS_POWER[i]);
        strcat(device_control, "/control");
        sysfs_write_str(device_control, on ? "on" : "auto");
        wait_pm_changed(TS_POWER[i], on);
    }
};

static void power_set_interactive(__attribute__((unused)) struct power_module *module, int on)
{
    if (!is_profile_valid(current_power_profile)) {
        ALOGD("%s: no power profile selected yet", __func__);
        return;
    }

    power_set_interactive_ext(on);

    // break out early if governor is not interactive
    if (!check_governor()) return;

    if (on) {
        sysfs_write_int(INTERACTIVE_PATH "hispeed_freq",
                        profiles[current_power_profile].hispeed_freq);
        sysfs_write_int(INTERACTIVE_PATH "go_hispeed_load",
                        profiles[current_power_profile].go_hispeed_load);
        sysfs_write_str(INTERACTIVE_PATH "target_loads",
                        profiles[current_power_profile].target_loads);
    } else {
        sysfs_write_int(INTERACTIVE_PATH "hispeed_freq",
                        profiles[current_power_profile].hispeed_freq_off);
        sysfs_write_int(INTERACTIVE_PATH "go_hispeed_load",
                        profiles[current_power_profile].go_hispeed_load_off);
        sysfs_write_str(INTERACTIVE_PATH "target_loads",
                        profiles[current_power_profile].target_loads_off);
    }
}

static void set_power_profile(int profile)
{
    if (!is_profile_valid(profile)) {
        ALOGE("%s: unknown profile: %d", __func__, profile);
        return;
    }

    // break out early if governor is not interactive
    if (!check_governor()) return;

    if (profile == current_power_profile)
        return;

    ALOGD("%s: setting profile %d", __func__, profile);

    sysfs_write_int(INTERACTIVE_PATH "boost",
                    profiles[profile].boost);
    sysfs_write_int(INTERACTIVE_PATH "boostpulse_duration",
                    profiles[profile].boostpulse_duration);
    sysfs_write_int(INTERACTIVE_PATH "go_hispeed_load",
                    profiles[profile].go_hispeed_load);
    sysfs_write_int(INTERACTIVE_PATH "hispeed_freq",
                    profiles[profile].hispeed_freq);
    sysfs_write_int(INTERACTIVE_PATH "io_is_busy",
                    profiles[profile].io_is_busy);
    sysfs_write_int(INTERACTIVE_PATH "min_sample_time",
                    profiles[profile].min_sample_time);
    sysfs_write_int(INTERACTIVE_PATH "sampling_down_factor",
                    profiles[profile].sampling_down_factor);
    sysfs_write_str(INTERACTIVE_PATH "target_loads",
                    profiles[profile].target_loads);
    sysfs_write_int(CPUFREQ_PATH "scaling_max_freq",
                    profiles[profile].scaling_max_freq);

    current_power_profile = profile;
}

static void power_hint(__attribute__((unused)) struct power_module *module,
                       power_hint_t hint, void *data)
{
    char buf[80];
    int len;

    switch (hint)
    {
    case POWER_HINT_INTERACTION:
        if (!is_profile_valid(current_power_profile)) {
            ALOGD("%s: no power profile selected yet", __func__);
            return;
        }

        if (!profiles[current_power_profile].boostpulse_duration)
            return;

        // break out early if governor is not interactive
        if (!check_governor()) return;

        if (boostpulse_open() >= 0) {
            snprintf(buf, sizeof(buf), "%d", 1);
            len = write(boostpulse_fd, &buf, sizeof(buf));
            if (len < 0) {
                strerror_r(errno, buf, sizeof(buf));
                ALOGE("Error writing to boostpulse: %s\n", buf);

                pthread_mutex_lock(&lock);
                close(boostpulse_fd);
                boostpulse_fd = -1;
                pthread_mutex_unlock(&lock);
            }
        }
        break;
    case POWER_HINT_SET_PROFILE:
        pthread_mutex_lock(&lock);
        set_power_profile(*(int32_t *)data);
        pthread_mutex_unlock(&lock);
        break;
    case POWER_HINT_LOW_POWER:
        /* This hint is handled by the framework */
        break;
    default:
        break;
    }
}

static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};

static int get_feature(__attribute__((unused)) struct power_module *module,
                       feature_t feature)
{
    if (feature == POWER_FEATURE_SUPPORTED_PROFILES) {
        return PROFILE_MAX;
    }
    return -1;
}

struct power_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = POWER_MODULE_API_VERSION_0_2,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = POWER_HARDWARE_MODULE_ID,
        .name = "PXA1908 Power HAL",
        .author = "Gabriele M & Nemirtingas",
        .methods = &power_module_methods,
    },

    .init = power_init,
    .setInteractive = power_set_interactive,
    .powerHint = power_hint,
    .getFeature = get_feature
};
