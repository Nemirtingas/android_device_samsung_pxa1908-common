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
        int cam_id = mMrvlCameraInfo[i].camera_id;
        if( cam_id != -1 && cam_id == id )
            break;
    }
    if( i == iNumOfSensors )
    {
        ALOGE("No matching sensor in list. Pls check CameraSetting::mMrvlCameraInfo[]");
        return NULL;
    }

    return &mMrvlCameraInfo[i];
}
