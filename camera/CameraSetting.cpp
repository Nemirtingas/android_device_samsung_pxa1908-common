#include "CameraSetting.h"

//#define LOG_TAG "CameraSetting"
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

int CameraSetting::iNumOfSensors = 0;
SettingCamInfo CameraSetting::mMrvlCameraInfo[NUM_CAMERAS];

SettingCamInfo* CameraSetting::getMrvlCameraInfo(int id)
{

    int i;
    for( i = 0; i < iNumOfSensors; ++i )
    {
        int cam_id = mMrvlCameraInfo[i].sensorid;
        if( cam_id != -1 && cam_id == id )
        {
            ALOGD("Found %d at %d", cam_id, i);
            break;
        }
    }

    if( i == iNumOfSensors )
    {
        ALOGE("No matching sensor in list. Pls check CameraSetting::mMrvlCameraInfo[]");
        return NULL;
    }

    return &mMrvlCameraInfo[i];
}

int CameraSetting::initCameraTable(CameraProperties *camprop, int sensorid, int engsendorid, int facing, int orient)
{

    ALOGI("%s: sensorname=%s, sensorid=%d, engsensorid=%d, portnum=%d, facing=%d, orient=%d", __FUNCTION__, camprop->name, sensorid, engsendorid, camprop->portnum+1, facing, orient);
    if( iNumOfSensors <= 4 )
    {
        SettingCamInfo *caminfo = &mMrvlCameraInfo[iNumOfSensors];
        strncpy(caminfo->sensor, camprop->name, sizeof(caminfo->sensor)-1);
        caminfo->sensor[sizeof(caminfo->sensor)-1] = '\0';
        caminfo->sensorid = sensorid;
        caminfo->engsensorid;
        caminfo->facing = facing;
        caminfo->ports = camprop->portnum + 1;
        caminfo->orientation = orient;

        if( camprop->info.field_2C[0] )
        {
            strncpy(caminfo->field_3C, camprop->info.field_2C, sizeof(caminfo->field_3C));
        }
        else if( !strcmp(camprop->name, "sr200") )
        {
            strncpy(caminfo->field_3C, "2.35", sizeof(caminfo->field_3C));
        }
        else
        {
            strncpy(caminfo->field_3C, "3.7", sizeof(caminfo->field_3C));
        }
        caminfo->field_3C[7] = 0;

        ++iNumOfSensors;
        return 0;
    }
    else
    {
        ALOGE("Invalid sensor cnt=%d, max cnt=%d", iNumOfSensors, 4);
        return -EINVAL;
    }
}

int CameraSetting::getNumOfCameras()
{
    return iNumOfSensors;
}
