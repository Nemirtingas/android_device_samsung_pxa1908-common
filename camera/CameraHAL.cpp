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

#include <cstdlib>
#include <hardware/camera_common.h>
#include <hardware/hardware.h>

#include <pthread.h>

//#define LOG_NDEBUG 0

#define ATRACE_TAG (ATRACE_TAG_CAMERA | ATRACE_TAG_HAL)
#include <cutils/trace.h>
#include <cutils/properties.h>

#define LOG_TAG "CameraReversing"
#include <cutils/log.h>

class __DEBUG_CLASS__
{
    const char* _func;
    public:
        __DEBUG_CLASS__(int line, const char* func):_func(func)
        {
            ALOGD("Entering %s at line %d", _func, line);
        }

        ~__DEBUG_CLASS__()
        {
            ALOGD("Exiting %s", _func);
        }
};

#define log_func_entry         __DEBUG_CLASS__ __debug_obj__(__LINE__, __func__)
#define log_func_line(fmt,...) ALOGD("%s at %d: " fmt, __func__, __LINE__, ## __VA_ARGS__)

#include "CameraHAL.h"

#include "CameraHardwareSmt.h"
#include "CameraHardwareDxO.h"

#include <dlfcn.h>

/*
 * This file serves as the entry point to the HAL.  It contains the module
 * structure and functions used by the framework to load and interface to this
 * HAL, as well as the handles to the individual camera devices.
 */

namespace default_camera_hal {

// Can we open multiple cameras at a time
static bool gMultiopen;
static int gCamerasOpen;
static int gNumCameras;
static CameraHardwareBase *gCameraHals[5];
static mrvl_camera_info_t  gCameraInfo[5];

static void *vendor_camera_library;

pthread_mutex_t gCameraMutex = PTHREAD_MUTEX_INITIALIZER;

extern "C" {

static int get_number_of_cameras()
{
    log_func_entry;
    return 0;
}

static int get_camera_info(int id, struct camera_info* info)
{
    log_func_entry;



    return 0;
}

static int camera_set_preview_window(camera_device_t *_dev, struct preview_stream_ops *ops)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if( dev == NULL )
        return -EINVAL;

    return gCameraHals[dev->cameraId]->setPreviewWindow(ops);
}

static void camera_set_callbacks(camera_device *_dev, camera_notify_callback notify_callback,
                                                      camera_data_callback data_callback,
                                                      camera_data_timestamp_callback timestamp_callback,
                                                      camera_request_memory request_memory, void *datas)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        gCameraHals[dev->cameraId]->setCallbacks(notify_callback, data_callback, timestamp_callback, request_memory,datas);
}

static void camera_enable_msg_type(camera_device_t *_dev, int32_t msg_type)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        gCameraHals[dev->cameraId]->enableMsgType(msg_type);
}

static void camera_disable_msg_type(camera_device_t *_dev, int32_t msg_type)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        gCameraHals[dev->cameraId]->disableMsgType(msg_type);
}

static int camera_msg_type_enabled(camera_device_t *_dev, int32_t msg_type)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->msgTypeEnabled(msg_type);

    return 0;
}

static int camera_start_preview(camera_device_t *_dev)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->startPreview();

    return -EINVAL;
}

static void camera_stop_preview(camera_device_t *_dev)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        gCameraHals[dev->cameraId]->stopPreview();
}

static int camera_preview_enabled(camera_device_t *_dev)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->previewEnabled();

    return -EINVAL;
}

static int camera_store_meta_data_in_buffers(camera_device_t *_dev, int store)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->storeMetaDataInBuffers(store);

    return -EINVAL;
}

static int camera_start_recording(camera_device_t *_dev)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->startRecording();

    return -EINVAL;
}

static void camera_stop_recording(camera_device_t *_dev)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        gCameraHals[dev->cameraId]->stopRecording();
}

static int camera_recording_enabled(camera_device_t *_dev)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->recordingEnabled();

    return -EINVAL;
}

static void camera_release_recording_frame(camera_device_t *_dev, const void *frame)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        gCameraHals[dev->cameraId]->releaseRecordingFrame(frame);
}

static int camera_auto_focus(camera_device_t *_dev)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->autoFocus();

    return -EINVAL;
}

static int camera_cancel_auto_focus(camera_device_t *_dev)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->cancelAutoFocus();

    return -EINVAL;
}

static int camera_take_picture(camera_device_t *_dev)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->takePicture();

    return -EINVAL;
}

static int camera_cancel_picture(camera_device_t *_dev)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->cancelPicture();

    return -EINVAL;
}

static int camera_set_parameters(camera_device_t *_dev, const char *parameters)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->setParameters(parameters);

    return -EINVAL;
}

static void camera_put_parameters(camera_device_t *_dev, char *parameters)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        gCameraHals[dev->cameraId]->putParameters(parameters);
}

static char* camera_get_parameters(camera_device_t *_dev)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->getParameters();

    return NULL;
}

static int camera_send_command(camera_device_t *_dev, int32_t cmd, int32_t arg1, int32_t arg2)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->sendCommand(cmd, arg1, arg2);

    return -EINVAL;
}

static void camera_release(camera_device_t *_dev)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        gCameraHals[dev->cameraId]->release();
}

static int camera_dump(camera_device_t *_dev, int fd)
{
    log_func_entry;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    if ( dev )
        return gCameraHals[dev->cameraId]->dump(fd);

    return -EINVAL;
}

static int camera_device_close(hw_device_t *_dev)
{
    log_func_entry;
    int res = -EINVAL;
    int cameraId;
    mrvl_device_t *dev = (mrvl_device_t*)_dev;
    pthread_mutex_lock(&gCameraMutex);
    if ( dev )
    {
        cameraId = dev->cameraId;
        if ( gCameraHals[cameraId] )
        {
            delete gCameraHals[cameraId];
        }
        else
        {
            ALOGE("gCameraHals[cameraid] == NULL, camera %d already free!", cameraId);
        }
        gCameraHals[cameraId] = NULL;
        if ( dev->dev.ops )
            free(dev->dev.ops);
        free(dev);
        --gCamerasOpen;
        res = 0;
    }
    pthread_mutex_unlock((pthread_mutex_t *)&gCameraMutex);
    return res;
}

static int camera_device_open(const hw_module_t* mod, const char* name, hw_device_t** dev)
{
    log_func_entry;
    char multiopenprop[PROPERTY_VALUE_MAX];
    int camera_id;
    mrvl_device_t *camera_dev;
    camera_device_ops_t *ops;

    property_get("service.camera.multiopen", multiopenprop, "0");
    if( !strcmp(multiopenprop, "1") )
        gMultiopen = true;

    pthread_mutex_lock(&gCameraMutex);

    if( name )
    {
        camera_id = atoi(name);
        if( gCamerasOpen == 1 && !gMultiopen )
        {
            ALOGE("already open one camera, not support open multi camera!");
            pthread_mutex_unlock(&gCameraMutex);
            return -EUSERS;
        }

        if( camera_id > gNumCameras || camera_id < 0 )
        {
            ALOGE("camera service provided cameraid out of bounds, cameraid = %d, num supported = %d", camera_id, gNumCameras);
            pthread_mutex_unlock(&gCameraMutex);
            return -EINVAL;
        }

        camera_dev = (mrvl_device_t*)malloc(sizeof(mrvl_device_t));
        if( camera_dev == NULL )
        {
            ALOGE("camera_device allocation fail");
            pthread_mutex_unlock(&gCameraMutex);
            return -ENOMEM;
        }

        ops = (camera_device_ops_t*)malloc(sizeof(camera_device_ops_t));
        if( ops == NULL )
        {
            ALOGE("camera_ops allocation fail");
            free(camera_dev);
            pthread_mutex_unlock(&gCameraMutex);
            return -ENOMEM;
        }

        memset(camera_dev, 0, sizeof(mrvl_device_t));
        memset(ops, 0, sizeof(camera_device_ops_t));

        camera_dev->dev.common.module = (hw_module_t*)mod;
        camera_dev->dev.ops = ops;
        camera_dev->dev.common.tag = HARDWARE_DEVICE_TAG;
        camera_dev->dev.common.close = camera_device_close;
        camera_dev->cameraId = camera_id;

        ops->set_preview_window         = camera_set_preview_window;
        ops->set_callbacks              = camera_set_callbacks;
        ops->enable_msg_type            = camera_enable_msg_type;
        ops->disable_msg_type           = camera_disable_msg_type;
        ops->msg_type_enabled           = camera_msg_type_enabled;
        ops->start_preview              = camera_start_preview;
        ops->stop_preview               = camera_stop_preview;
        ops->preview_enabled            = camera_preview_enabled;
        ops->store_meta_data_in_buffers = camera_store_meta_data_in_buffers;
        ops->start_recording            = camera_start_recording;
        ops->stop_recording             = camera_stop_recording;
        ops->recording_enabled          = camera_recording_enabled;
        ops->release_recording_frame    = camera_release_recording_frame;
        ops->auto_focus                 = camera_auto_focus;
        ops->cancel_auto_focus          = camera_cancel_auto_focus;
        ops->take_picture               = camera_take_picture;
        ops->cancel_picture             = camera_cancel_picture;
        ops->set_parameters             = camera_set_parameters;
        ops->put_parameters             = camera_put_parameters;
        ops->get_parameters             = camera_get_parameters;
        ops->send_command               = camera_send_command;
        ops->release                    = camera_release;
        ops->dump                       = camera_dump;
        *dev = (hw_device_t*)camera_dev;

        if( gCameraHals[camera_id] != NULL )
        {
            ALOGE("gCameraHals[cameraid] != NULL, previous camera %d not free!", camera_id);
            delete gCameraHals[camera_id];
        }

        ALOGI("cameraid = %d, gCameraInfo[cameraid].ports = %d", camera_id, gCameraInfo[camera_id].ports);
        if( gCameraInfo[camera_id].ports <= 0 )
            ALOGE("Camera has too many / too less ports, not supported!");
        else if( gCameraInfo[camera_id].ports == 1 )
            gCameraHals[camera_id] = new CameraHardwareSmt(camera_id);
        else
            gCameraHals[camera_id] = new CameraHardwareDxO(camera_id);
    }

    ++gCamerasOpen;

    pthread_mutex_unlock(&gCameraMutex);

    return 0;
}

void null()
{
}

static hw_module_methods_t gCameraModuleMethods = {
    open : camera_device_open
};

camera_module_t HAL_MODULE_INFO_SYM __attribute__ ((visibility("default"))) = {
    common : {
        tag                : HARDWARE_MODULE_TAG,
        module_api_version : CAMERA_MODULE_API_VERSION_1_0,
        hal_api_version    : HARDWARE_HAL_API_VERSION,
        id                 : CAMERA_HARDWARE_MODULE_ID,
        name               : "Default Camera HAL",
        author             : "The Android Open Source Project",
        methods            : &gCameraModuleMethods,
        dso                : NULL,
        reserved           : {0},
    },
    get_number_of_cameras : get_number_of_cameras,
    get_camera_info       : get_camera_info,
    set_callbacks         : NULL,
    //set_callbacks         : (int (*)(const camera_module_callbacks_t*))null,
    get_vendor_tag_ops    : NULL,
    open_legacy           : NULL,
    set_torch_mode        : NULL,
    init                  : NULL,
    reserved              : {0},
};
} // extern "C"

__attribute__((constructor)) void __module_load__()
{
    vendor_camera_library = dlopen("/system/lib/hw/camera.stock.mrvl.so", RTLD_LAZY);
    if( vendor_camera_library == NULL )
        ALOGE("Failed to load /system/lib/hw/camera.stock.mrvl.so");
    //dlsym(vendor_camera_library, "");
}

__attribute__((destructor)) void __module_unload__()
{
    if( vendor_camera_library )
    {
        dlclose(vendor_camera_library);
        vendor_camera_library = NULL;
    }
}

} // namespace default_camera_hal
