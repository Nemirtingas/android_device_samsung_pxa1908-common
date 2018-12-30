#include "stockcamera.h"

#include <dlfcn.h>

#define LOG_TAG "CameraReversing"
#include <cutils/log.h>
#include <errno.h>
#include <exception>

#define LOAD_FUNC(lib, func)   (*(int*)&func) = (int)dlsym(lib, #func)
#define LOAD_FUNC_CXX(lib, func, name) (*(int*)&func) = (int)dlsym(lib, name)

#define STOCKCAMLIB "/system/lib/hw/camera.stock.so"

libstockcamera::libstockcamera()
{
    _lib = dlopen(STOCKCAMLIB, RTLD_NOW);

    if( _lib == NULL )
        throw(std::exception());

    // Get the original exported structure so we can get the camera_get_camera_info & camera_get_number_of_cameras
    LOAD_FUNC(_lib, HMI);
    if( HMI == NULL )
        throw(std::exception());

    camera_open_dev = HMI->common.methods->open;
    camera_get_number_of_cameras = HMI->get_number_of_cameras;
    camera_get_camera_info = HMI->get_camera_info;

    ALOGE("HMI: %p", HMI);
    ALOGE("camera_open_dev: %p", camera_open_dev);
    ALOGE("camera_get_number_of_cameras: %p", camera_get_number_of_cameras);
    ALOGE("camera_get_camera_info: %p", camera_get_camera_info);

    // Get the number of sensors, it not working on Android 6.0+ so we'll skip the sensor detection if we already have detected the 2 cameras
    LOAD_FUNC_CXX(_lib, iNumOfSensors, "_ZN7android13CameraSetting13iNumOfSensorsE");
}

libstockcamera::~libstockcamera()
{
    dlclose(_lib);
}
