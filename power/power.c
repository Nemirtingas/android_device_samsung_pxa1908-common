/*
 * Copyright (C) 2012 The Android Open Source Project
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
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LOG_TAG "PowerHAL"
#include <utils/Log.h>

#include <hardware/hardware.h>
#include <hardware/power.h>

#define POWERHALCFG "/etc/powerhal.conf"

#define __AFILE__ "power.c"

struct power_cpu_info
{
	char path[256];
	char runtime_path[256];
	int  control_fd;
	struct power_cpu_info *next;
	struct power_cpu_info *prev;
};

static struct power_cpu_info *devices = NULL;
static struct power_cpu_info *last_device = NULL;

int add_to_list( const char* buffer, int control_fd )
{
	struct power_cpu_info *device;
	struct power_cpu_info *old_last_device;

	device = (struct power_cpu_info*)malloc(sizeof(struct power_cpu_info));
	if( device )
	{
		memset(device, 0, sizeof(struct power_cpu_info));
		strncpy(device->path, buffer, 256);
		strncpy(device->runtime_path, buffer, 256);
		strncat(device->runtime_path, "/runtime_status", 256);
		device->control_fd = control_fd;
		if( devices )
		{
			old_last_device = last_device;
			last_device->next = device;
			last_device = device;
			last_device->prev = old_last_device;
		}
		else
		{
			last_device = device;
			devices = device;
		}

		return 0;
	}
	else
	{
		ALOGE("malloc failed for creating new node");
	}
	return -1;
}

int is_pm_supported( const char *control, const char *runtime )
{
	char buf[12];
	int fd;
	if( access(control, 0) < 0 )
	{
		ALOGW("%s doesn't exist\n", control);
		return -1;
	}
	fd = open(runtime, 0);
	if( fd < 0 )
	{
		ALOGW("Error opening %s: %s\n", runtime, strerror(errno));
		return -1;
	}
	if( read(fd, buf, sizeof(buf)) < 0 )
	{
		ALOGW("Error reading %s: %s\n", runtime, strerror(errno));
		close(fd);
		return -1;
	}
	if( !strncmp(buf, "unsupported", 11) )
	{
		ALOGW("%s is unsupported\n", runtime);
		close(fd);
		return -1;
	}
	close(fd);
	return 0;
}

void pm_set_for_device( struct power_cpu_info *device, int on )
{
	if( on )
	{
		if( write(device->control_fd, "on", 2) < 0 )
		{
			ALOGE("Error writing %s to %s: %s\n", "on", device->path, strerror(errno));
			return;
		}
		ALOGD("write on done\n");
		return;
	}
	if( write(device->control_fd, "auto", 4) >= 0 )
		ALOGD("write auto done\n");
	else
		ALOGE("Error writing %s to %s: %s\n", "auto", device->path, strerror(errno));
}

void wait_for_set_complete(const char* runtime_path, int on )
{
	int fd;
	char buf[12];
	int retry = 1000;
	const char *state;
	int state_len;

	while( retry-- > 0 )
	{
		fd = open(runtime_path, 0);
		if( fd < 0 )
		{
			ALOGE("Error opening %s: %s\n", runtime_path, strerror(errno));
			return;
		}
		if( read(fd, buf, sizeof(buf)) < 0 )
		{
			close(fd);
			ALOGE("Error reading %s: %s\n", runtime_path, strerror(errno));
		}
		else
		{
			close(fd);
			if( !strncmp(buf, "unsupported", 11) )
			{
				ALOGE("%s is unsupported\n", runtime_path);
				break;
			}
			if( on )
			{
				state = "active";
				state_len = 6;
			}
			else
			{
				state = "suspended";
				state_len = 9;
			}
			if( !strncmp(buf, state, state_len) )
				break;

			usleep(1000);
		}
	}
	if( retry <= 0 )
		ALOGW("DEVICE SUSPEND/RESUME FAILED!\n");
	ALOGD("wait_for_set_complete done, status is %s", buf);
}

static void power_init(__attribute__((unused)) struct power_module *module)
{
	FILE *conf = fopen(POWERHALCFG, "r");
	int fd;
	char buffer[256];
	char control[256];
	char runtime[256];
	if( !conf )
	{
		ALOGW("%s does not exist! No devices for early suspend/late resume", POWERHALCFG);
		return;
	}
	while( fgets(buffer, 256, conf) )
	{
		memset(control, 0, sizeof(control));
		if( buffer[0] != '#' && buffer[0] != '\n' && buffer[0] != ' ' )
		{
			buffer[strlen(buffer)-1] = '\0';
			strncpy(control, buffer, 256);
			strncat(control, "/control", 256);
			strncpy(runtime, buffer, 256);
			strncat(runtime, "/runtime_status", 256);
			if( is_pm_supported(control, runtime) )
			{
				ALOGE("device %s doesn't support pm\n", buffer);
				continue;
			}
			fd = open(control, 2);
			if( fd >= 0 )
			{
				ALOGD("add device %s to list\n", buffer);
				if( add_to_list(buffer, fd) )
				{
					ALOGE("add device %s to list failed\n", buffer);
				}
			}
			else
			{
				ALOGE("Error opening %s: %s\n", control, strerror(errno));
			}
		}
	}
	fclose(conf);
}

static void power_set_interactive(__attribute__((unused)) struct power_module *module, int on)
{
	struct power_cpu_info *i;

	ALOGD("power_set_interactive called with on %d\n", on);
	if( on )
	{
		for( i = last_device; i; i = i->prev )
		{
			pm_set_for_device(i, on);
		}
	}
	else
	{
		for( i = devices; i; i = i->next )
		{
			pm_set_for_device(i, 0);
		}
	}
	for( i = last_device; i; i = i->prev )
	{
		wait_for_set_complete(i->runtime_path, on);
	}
}

static void power_hint(__attribute__((unused)) struct power_module *module, power_hint_t hint,
                       __attribute__((unused)) void *data) {
    switch (hint) {
    default:
        break;
    }
}

static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};

struct power_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = POWER_MODULE_API_VERSION_0_2,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = POWER_HARDWARE_MODULE_ID,
        .name = "Marvell Power HAL",
        .author = "Nemirtingas",
        .methods = &power_module_methods,
    },

    .init = power_init,
    .setInteractive = power_set_interactive,
    .powerHint = power_hint,
};

__attribute__((constructor)) void __module_load__()
{
	ALOGI("%s loaded.", "power.mrvl.so");
}

__attribute__((destructor)) void __module_unload__()
{
	ALOGI("%s unloaded.", "power.mrvl.so");
}
