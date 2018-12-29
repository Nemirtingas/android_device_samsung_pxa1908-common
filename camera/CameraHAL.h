/*
 * Copyright (C) 2013 The Android Open Source Project
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

#ifndef CAMERA_HAL_H_
#define CAMERA_HAL_H_

#include <cutils/bitops.h>
#include <hardware/hardware.h>
#include <hardware/camera_common.h>
#include <hardware/camera3.h>
#include <hardware/camera.h>
#include <system/camera_vendor_tags.h>

#define NUM_CAMERAS 5


struct mrvl_device_t
{
    camera_device_t dev;
    int32_t cameraId;
};

struct mrvl_camera_info_t
{
    int32_t facing;
    int32_t orientation;
    int32_t field_8;
    int32_t field_C;
    int32_t ports;
};

struct ModuleInfo
{
    char data[44];
    char field_2C[8];
    char field_34[864];
};

struct CameraProperties
{
    char name[32];
    int orient;
    int face;
    int portnum;
    ModuleInfo info;
};

namespace default_camera_hal {
// CameraHAL contains all module state that isn't specific to an individual
// camera device.

} // namespace default_camera_hal

#endif // CAMERA_HAL_H_
