#include "Engine.h"

//#define LOG_TAG "CameraMrvl"
#define LOG_TAG "CameraReversing"
#include <cutils/log.h>
#include <cutils/properties.h>
#include <cstdlib>

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

int Engine::iSensorCount = 0;
CameraProperties Engine::stCameraProp[4];

void Engine::getCameraInfo(int id, mrvl_camera_info_t *caminfos)
{

    SettingCamInfo *infos;
    infos = CameraSetting::getMrvlCameraInfo(id);
    if( infos )
    {
        caminfos->facing = infos->facing;
        caminfos->field_8 = 256;
        caminfos->field_C = 0;
        caminfos->orientation = infos->orientation;
        caminfos->ports = infos->ports;
    }
    else
    {
        ALOGE("Error occur when get CameraInfo");
    }
}

void Engine::getModuleInfo(int id, ModuleInfo* modinfo)
{

    SettingCamInfo *caminfo;
    int i;
    char *sensor;

    caminfo = CameraSetting::getMrvlCameraInfo(id);
    if( caminfo )
    {
        sensor = caminfo->sensor;
        for( i = 0; i < iSensorCount; ++i )
        {
            if( !strcmp(sensor, stCameraProp[i].name) )
                break;
        }
        if( i == iSensorCount )
        {
            ALOGE("Error cannot find the module info for sensor %s", sensor);
            return;
        }
        memcpy(modinfo, &stCameraProp[i].info, sizeof(ModuleInfo));
    }
    else
    {
        ALOGE("Error occur when get ModuleInfo");
    }
}

int Engine::getNumberOfCameras()
{

    CamHandle camHandle;
    static int orientations[] = {270,90,180};
    CameraProperties *camprop = stCameraProp;
    int orient;
    int sensorid;
    int facing;
    char prop[PROPERTY_VALUE_MAX];

    if( libcameraengine::Inst().CAM_GetHandle(&camHandle) )
        return 0;


    if( libcameraengine::Inst().CAM_EnumSensors(camHandle, &iSensorCount, stCameraProp) )
    {
        libcameraengine::Inst().CAM_FreeHandle(&camHandle);
        return 0;
    }

    for( int i = 0; i < iSensorCount; ++i, ++camprop )
    {
        if( camprop->orient > 3 )
            orient = 0;
        else
            orient = orientations[camprop->orient-1];

        facing = camprop->face;

        property_get("service.camera.sensor.facing", prop, "");
        if( !strcmp(prop, "back") )
            facing = 0;
        else if( !strcmp(prop, "front") )
            facing = 1;

        property_get("service.camera.sensor.orient", prop, "");
        if( prop[0] )
            orient = atoi(prop);

        if( iSensorCount == 1 )
            sensorid = 0;
        else
        {
            if( facing )
                sensorid = 1;
            else
                sensorid = 0;
        }
        CameraSetting::initCameraTable(camprop, sensorid, i, facing, orient);
        ALOGI("name=%s, id=%d, eng_id=%d, portnum=%d, face=%d, orient=%d", camprop->name, sensorid, i, camprop->portnum+1, camprop->face, orient);
    }

    if( libcameraengine::Inst().CAM_FreeHandle(&camHandle) )
        return 0;

    return CameraSetting::getNumOfCameras();
}
;
