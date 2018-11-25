#include "CameraHardwareBase.h"

#include <cstdlib>

#define LOG_TAG "CameraReversing"
#include <cutils/log.h>

#include <camera/CameraParameters.h>

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

static bool gDebug = false;

CameraHardwareBase::CameraHardwareBase(int cameraId):camera_mutex(PTHREAD_MUTEX_INITIALIZER)
{
}

CameraHardwareBase::~CameraHardwareBase()
{
}

void CameraHardwareBase::cameraLock()
{
    pthread_mutex_lock(&camera_mutex);
}

void CameraHardwareBase::cameraUnlock()
{
    pthread_mutex_unlock(&camera_mutex);
}

int CameraHardwareBase::setPreviewWindow(struct preview_stream_ops *ops)
{
    log_func_entry;
    return 0;
}

void CameraHardwareBase::setCallbacks(camera_notify_callback notify_callback, camera_data_callback data_callback, camera_data_timestamp_callback timestamp_callback, camera_request_memory request_memory, void *datas)
{
    log_func_entry;
}

void CameraHardwareBase::enableMsgType(int32_t msg_type)
{
    log_func_entry;
}

void CameraHardwareBase::disableMsgType(int32_t msg_type)
{
    log_func_entry;
}

int CameraHardwareBase::msgTypeEnabled(int32_t msg_type)
{
    log_func_entry;
    return -EINVAL;
}

int CameraHardwareBase::startPreview()
{
    log_func_entry;
    return -EINVAL;
}

void CameraHardwareBase::stopPreview()
{
    log_func_entry;
}

int CameraHardwareBase::previewEnabled()
{
    log_func_entry;
    return -EINVAL;
}

int CameraHardwareBase::storeMetaDataInBuffers(int store)
{
    log_func_entry;
    return -EINVAL;
}

int CameraHardwareBase::startRecording()
{
    log_func_entry;
    return -EINVAL;
}

void CameraHardwareBase::stopRecording()
{
    log_func_entry;
}

int CameraHardwareBase::recordingEnabled()
{
    log_func_entry;
    return -EINVAL;
}

void CameraHardwareBase::releaseRecordingFrame(const void *frame)
{
    log_func_entry;
}

int CameraHardwareBase::autoFocus()
{
    log_func_entry;
    return -EINVAL;
}

int CameraHardwareBase::cancelAutoFocus()
{
    log_func_entry;
    return -EINVAL;
}

int CameraHardwareBase::takePicture()
{
    log_func_entry;
    return -EINVAL;
}

int CameraHardwareBase::cancelPicture()
{
    log_func_entry;
    return -EINVAL;
}

int CameraHardwareBase::setParameters(const char *parameters)
{
    log_func_entry;
    return -EINVAL;
}

void CameraHardwareBase::putParameters(char *parameters)
{
    log_func_entry;
}

char* CameraHardwareBase::getParameters()
{
    log_func_entry;

    android::String8 str;
    android::CameraParameters params;
    char *res;
    size_t len = 0;

    cameraLock();

    params.flatten().setTo(str);

    if( str.string() )
        len = str.length();

    res = (char*)malloc(sizeof(char) * len+1);

    strcpy(res, str.string());
    if( gDebug )
        params.dump();

    cameraUnlock();

    return res;
}

int CameraHardwareBase::sendCommand(int32_t cmd, int32_t arg1, int32_t arg2)
{
    log_func_entry;
    return -EINVAL;
}

void CameraHardwareBase::release()
{
    log_func_entry;
}

int CameraHardwareBase::dump(int fd)
{
    log_func_entry;
    return -EINVAL;
}
