#include "Engine.h"

//#define LOG_TAG "CameraMrvl"
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
        caminfos->ports = infos->ports
    }
    else
    {
        ALOGE("Error occur when get CameraInfo");
    }
}
