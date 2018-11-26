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

#ifndef CAMERA_H_
#define CAMERA_H_

#include <hardware/hardware.h>
#include <hardware/camera3.h>
#include <hardware/camera.h>
#include <utils/Mutex.h>

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

typedef struct _CamHandle* CamHandle;

namespace default_camera_hal {
// Camera represents a physical camera on a device.
// This is constructed when the HAL module is loaded, one per physical camera.
// It is opened by the framework, and must be closed before it can be opened
// again.
// This is an abstract class, containing all logic and data shared between all
// camera devices (front, back, etc) and common to the ISP.
class Camera {
    public:


    protected:

    private:
};
} // namespace default_camera_hal

#endif // CAMERA_H_
