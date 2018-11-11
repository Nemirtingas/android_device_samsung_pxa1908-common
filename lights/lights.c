/*
 * Copyright (C) 2008 The Android Open Source Project
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
// #define LOG_NDEBUG 0
#define LOG_TAG "lights"
#include <cutils/log.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <hardware/lights.h>
/******************************************************************************/
#define UNUSED(x) ((void)(x))

static pthread_once_t g_init = PTHREAD_ONCE_INIT;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

char const*const LIGHT_ID_LEDSERVICE = "ledservice";

char const*const GED_LED_DELAY_OFF_FILE_PATHS[] =
{
    "/sys/class/leds/led_r/delay_off",
    "/sys/class/leds/led_g/delay_off",
    "/sys/class/leds/led_b/delay_off",
    NULL,
};

char const*const GED_LED_DELAY_ON_FILE_PATHS[] =
{
    "/sys/class/leds/led_r/delay_on",
    "/sys/class/leds/led_g/delay_on",
    "/sys/class/leds/led_b/delay_on",
    NULL,
};

char const*const GED_LED_BRIGHTNESS_FILE_PATHS[] = 
{
    "/sys/class/leds/led_r/brightness",
    "/sys/class/leds/led_g/brightness",
    "/sys/class/leds/led_b/brightness",
    NULL,
};

char const*const GED_LED_TRIGGER_FILE_PATHS[] =
{
    "/sys/class/leds/led_r/trigger",
    "/sys/class/leds/led_g/trigger",
    "/sys/class/leds/led_b/trigger",
    NULL,
};

char const*const LCD_FILE_PATHS[] = 
{
    "/sys/class/leds/lcd-backlight/brightness",
    "/sys/class/backlight/panel/brightness",
    "/sys/class/backlight/lcd-bl/brightness",
    "/sys/class/backlight/msmfb_bl0/brightness",
    NULL,
};

char const*const BUTTON_FILE_PATHS[] =
{
    "/sys/class/sec/sec_touchkey/brightness",
    "/sys/class/leds/button-backlight/brightness",
    "/sys/class/backlight/touchkey-led/brightness",
    NULL,
};

char const*const KEYBOARD_FILE_PATHS[] =
{
    "/sys/class/sec/sec_keypad/brightness",
    "/sys/class/leds/keyboard-backlight/brightness",
    NULL,
};

char const*const SEC_LED_PATTERN_FILE_PATHS[] =
{
    "/sys/class/sec/led/led_pattern",
    NULL,
};

char const*const SEC_LED_BLINK_FILE_PATHS[] =
{
    "/sys/class/sec/led/led_blink",
    NULL,
};

char const*const*const g_lights_file_paths[] = 
{
    LCD_FILE_PATHS,
    BUTTON_FILE_PATHS,
    KEYBOARD_FILE_PATHS,
    SEC_LED_PATTERN_FILE_PATHS,
    SEC_LED_BLINK_FILE_PATHS,
};

int32_t g_lights_fds[5];
int32_t g_leds_brightness_fds[3];
int32_t g_leds_trigger_fds[3];

/**
 * device methods
 */
void initialize_fds()
{
    char const*const* filePaths;
    char const* filePath;
    int32_t fd;
    int i,j;

    ALOGE("%s: start", __FUNCTION__);
    for( i = 0; i < (sizeof(g_lights_file_paths)/sizeof(g_lights_file_paths[0])); ++i )
    {
        filePaths = g_lights_file_paths[i]; 
        for( j = 0; filePaths[j] != NULL; ++j )
        {
            filePath = filePaths[j];
            ALOGE("!@ initialize_fds : g_lights_file_paths[%d][%d] : %s\n", i, j, filePath);
            fd = open(filePath, O_RDWR);
            g_lights_fds[i] = fd;
            if( fd >= 0 )
            {
                    ALOGE("!@ initialize_fds : g_lights_file_paths : FOUND! : 0x%x\n", fd);
                    break;
            }
            ALOGE("!@ initialize_fds : g_lights_fds Open error! : [%d]\n", errno);
        }
    }
    if( g_lights_fds[4] < 0 )
    {
        for( i = 0; i < 3; ++i )
        {
            g_leds_brightness_fds[i] = open(GED_LED_BRIGHTNESS_FILE_PATHS[i], O_RDWR);
            g_leds_trigger_fds[i]   = open(GED_LED_TRIGGER_FILE_PATHS[i], O_RDWR);
        }
        for( i = 0; i < 3; ++i )
        {
            if( g_leds_brightness_fds[i] < 0 )
                ALOGE("led_brightness_fd: NOT FOUND! : color = %d(0=R,1=G,2=B).\n", i);
            if( g_leds_trigger_fds[i] < 0 )
                ALOGE("led_trigger_fd: NOT FOUND! : color = %d(0=R,1=G,2=B).\n", i);
        }
    }
}

void deinitialize_fds()
{
    int i;
    for( i = 0; i < 5; ++i )
    {
        if( g_lights_fds[i] != -1 )
            close(g_lights_fds[i]);
    }
}

void init_globals(void)
{
    // init the mutex
    pthread_mutex_init(&g_lock, NULL);

    initialize_fds();
}

const char* fd_to_string(int32_t fd)
{
    int i = 0;
    while( fd != g_lights_fds[i] )
    {
       if( ++i == 5 )
           return "unknown";
    }
    switch( i )
    {
        case 1 : return "button";
        case 2 : return "keyboard";
        case 3 : return "led_pattern";
        case 4 : return "led_blink";
        default: return "lcd";
    }
}

int32_t write_led_info(int fd, const char *format, ...)
{
    char buffer[20];
    int32_t len;
    int32_t res;
    va_list vlist;

    va_start(vlist, format);
    if( fd < 0 )
    {
        ALOGE("write_led_info failed to open %d\n", fd);
        return 0;
    }
    len = vsnprintf(buffer, 20, format, vlist);
    res = write(fd, buffer, len);
    ALOGE("write_led_info : %s\n", buffer);
    return 0;
}

static int write_int(int32_t fd, int value)
{
    if (fd >= 0)
    {
        char buffer[20];
        const char* v5;
        int bytes = snprintf(buffer, 20, "%d\n", value);

        v5 = fd_to_string(fd);

        int amt = write(fd, buffer, bytes);
        ALOGE("%s : %d -\n", v5, value);
        if( amt != -1 )
            return 0;
    }
    else
    {
        ALOGE("write_int failed to open %d\n", fd);
    }
    return -errno;
}

int32_t sub_C1C(int32_t color, int32_t flashOnMS, int32_t flashOffMS)
{
    int i;
    int32_t fd;
    int32_t red, green, blue, dword_30A8;
    if( color )
    {
        red   = (color >> 16) & 0xFF;
        green = (color >> 8) & 0xFF;
        blue  = color & 0xFF;
        if( flashOffMS )
            dword_30A8 = 2;
        else
            dword_30A8 = 1;
    }
    else
    {
        red   = 0;
        green = 0;
        blue  = 0;
        flashOffMS = 0;
        flashOnMS  = 0;
        dword_30A8 = 0;
    }
    write_led_info(g_leds_brightness_fds[0], "%u", 0);
    write_led_info(g_leds_brightness_fds[1], "%u", 0);
    write_led_info(g_leds_brightness_fds[2], "%u", 0);
    if( dword_30A8 == 2 )
    {
        if( red )
            write_led_info(g_leds_trigger_fds[0], "timer");
        else
            write_led_info(g_leds_trigger_fds[0], "none");
        if( green )
            write_led_info(g_leds_trigger_fds[1], "timer");
        else
            write_led_info(g_leds_trigger_fds[1], "none");
        if( blue )
            write_led_info(g_leds_trigger_fds[2], "timer");
        else
            write_led_info(g_leds_trigger_fds[2], "none");

        for( i = 0; i < 3; ++i )
        {
            fd = open(GED_LED_DELAY_OFF_FILE_PATHS[i], O_RDWR);

            if( fd < 0 )
                ALOGE("led_delay_off_fd : NOT FOUND! color = %d(0=R,1=G,2=B).\n", i);
            else
            {
                write_led_info(fd, "%u", flashOffMS);
                close(fd);
            }


            fd = open(GED_LED_DELAY_ON_FILE_PATHS[i], O_RDWR);

            if( fd < 0 )
                ALOGE("led_delay_on_fd : NOT FOUND! color = %d(0=R,1=G,2=B).\n", i);
            else
            {
                write_led_info(fd, "%u", flashOnMS);
                close(fd);
            }
        }
    }
    else
    {
        for( i = 0; i < 3; ++i )
        {
            write_led_info(g_leds_trigger_fds[i], "none");
        }
        write_led_info(g_leds_brightness_fds[0], "%u", red);
        write_led_info(g_leds_brightness_fds[1], "%u", green);
        write_led_info(g_leds_brightness_fds[2], "%u", blue);
    }

    return 0;
}

int32_t set_light_leds(struct light_state_t const* state)
{
    int32_t flashOnMS = state->flashOnMS;
    int32_t flashOffMS = state->flashOffMS;
    int32_t flashMode = state->flashMode;
    int32_t fd;
    int32_t res = 0;
    char buffer[32];
    int32_t len;

    pthread_mutex_lock(&g_lock);
    switch( flashMode )
    {
        case 0:
            if( g_lights_fds[3] >= 0 )
            {
                write_int(g_lights_fds[3], 0);
            }
            res = sub_C1C(0,0,0);
            break;
        case 1: case 2:
            if( g_lights_fds[4] < 0 )
            {
                res = sub_C1C(state->color, state->flashOnMS, state->flashOffMS);
                break;
            }
            else
            {
                len = snprintf(buffer, 32, "0x%x %d %d\n", state->color, state->flashOnMS, state->flashOffMS);
                ALOGE("%s : %s +\n", fd_to_string(g_lights_fds[4]), buffer);
                res = write(g_lights_fds[4], buffer, len);
                ALOGE("%s : %s -\n", fd_to_string(g_lights_fds[4]), buffer);
                if( res == -1 )
                    res = -errno;
                else
                    res = 0;
                break;
            }
        case 10: res = write_int(g_lights_fds[3], 1); break;
        case 11: res = write_int(g_lights_fds[3], 2); break;
        case 12: res = write_int(g_lights_fds[3], 3); break;
        case 13: res = write_int(g_lights_fds[3], 4); break;
        case 14: res = write_int(g_lights_fds[3], 5); break;
        case 15: res = write_int(g_lights_fds[3], 6); break;
    }
    pthread_mutex_unlock(&g_lock);
    return res;
}

static int is_lit(struct light_state_t const* state)
{
    return state->color & 0x00ffffff;
}

static int rgb_to_brightness(struct light_state_t const* state)
{
    int color = state->color & 0x00ffffff;
    return ((77*((color>>16)&0x00ff))
            + (150*((color>>8)&0x00ff)) + (29*(color&0x00ff))) >> 8;
}

static int set_light_backlight(struct light_device_t* dev, struct light_state_t const* state)
{
    UNUSED(dev);

    int err = 0;
    int brightness = rgb_to_brightness(state);
    pthread_mutex_lock(&g_lock);
    err = write_int(g_lights_fds[0], brightness);
    pthread_mutex_unlock(&g_lock);
    return err;
}

static int set_light_keyboard(struct light_device_t* dev, struct light_state_t const* state)
{
    UNUSED(dev);
    int err = 0;
    int on = is_lit(state);
    pthread_mutex_lock(&g_lock);
    err = write_int(g_lights_fds[2], on?1:0);
    pthread_mutex_unlock(&g_lock);
    return err;
}

static int set_light_buttons(struct light_device_t* dev, struct light_state_t const* state)
{
    UNUSED(dev);
    int err = 0;
    int on = is_lit(state);
    pthread_mutex_lock(&g_lock);
    err = write_int(g_lights_fds[1], on?1:0);
    pthread_mutex_unlock(&g_lock);
    return err;
}

static int set_light_battery(struct light_device_t* dev, struct light_state_t const* state)
{
    UNUSED(dev);
    return set_light_leds(state);
}

static int set_light_notifications(struct light_device_t* dev, struct light_state_t const* state)
{
    UNUSED(dev);
    return set_light_leds(state);
}

static int set_light_attention(struct light_device_t* dev, struct light_state_t const* state)
{
    UNUSED(dev);
    return set_light_leds(state);
}

static int set_light_ledservice(struct light_device_t* dev, struct light_state_t const* state)
{
    UNUSED(dev);
    return set_light_leds(state);
}

/** Close the lights device */
static int close_lights(struct light_device_t *dev)
{
    if (dev) {
        free(dev);
    }
    return 0;
}
/******************************************************************************/
/**
 * module methods
 */
/** Open a new instance of a lights device using name */
static int open_lights(const struct hw_module_t* module, char const* name, struct hw_device_t** device)
{
    int (*set_light)(struct light_device_t* dev,
            struct light_state_t const* state);
    if (0 == strcmp(LIGHT_ID_BACKLIGHT, name))
        set_light = set_light_backlight;
    else if (0 == strcmp(LIGHT_ID_KEYBOARD, name))
        set_light = set_light_keyboard;
    else if (0 == strcmp(LIGHT_ID_BUTTONS, name))
        set_light = set_light_buttons;
    else if (0 == strcmp(LIGHT_ID_BATTERY, name))
        set_light = set_light_battery;
    else if (0 == strcmp(LIGHT_ID_NOTIFICATIONS, name))
        set_light = set_light_notifications;
    else if (0 == strcmp(LIGHT_ID_ATTENTION, name))
        set_light = set_light_attention;
    else if (0 == strcmp(LIGHT_ID_LEDSERVICE, name))
        set_light = set_light_ledservice;
    else
        return -EINVAL;

    pthread_once(&g_init, init_globals);

    struct light_device_t *dev = malloc(sizeof(struct light_device_t));
    memset(dev, 0, sizeof(*dev));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t*)module;
    dev->common.close = (int (*)(struct hw_device_t*))close_lights;
    dev->set_light = set_light;

    *device = (struct hw_device_t*)dev;

    return 0;
}

static struct hw_module_methods_t lights_module_methods = {
    .open =  open_lights,
};
/*
 * The lights Module
 */
const struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = LIGHTS_HARDWARE_MODULE_ID,
    .name = "Samsung lights Module",
    .author = "Google, Inc.",
    .methods = &lights_module_methods,
};
