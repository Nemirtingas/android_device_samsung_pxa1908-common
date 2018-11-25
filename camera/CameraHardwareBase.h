#ifndef __CAMERAHARDWAREBASE_DEFINED__
#define __CAMERAHARDWAREBASE_DEFINED__

#include "Camera.h"

class CameraHardwareBase
{
public:
    char x[8];
    pthread_mutex_t camera_mutex;
    char field_C[252];
    int frames;
    char field_10C[28];
    int32_t video_start_time_s;
    int32_t video_start_time_us;
    int32_t video_end_time_s;
    int32_t video_end_time_us;
    char y[592];

    CameraHardwareBase(int cameraId);
    virtual ~CameraHardwareBase();
    void cameraLock();
    void cameraUnlock();
    int setPreviewWindow(struct preview_stream_ops *ops);
    void setCallbacks(camera_notify_callback notify_callback, camera_data_callback data_callback, camera_data_timestamp_callback timestamp_callback, camera_request_memory request_memory, void *datas);
    void enableMsgType(int32_t msg_type);
    void disableMsgType(int32_t msg_type);
    int msgTypeEnabled(int32_t msg_type);
    int startPreview();
    void stopPreview();
    int previewEnabled();
    int storeMetaDataInBuffers(int store);
    virtual int startRecording();
    virtual void stopRecording();
    virtual int recordingEnabled();
    virtual void releaseRecordingFrame(const void *frame);
    int autoFocus();
    int cancelAutoFocus();
    int takePicture();
    int cancelPicture();
    int setParameters(const char *parameters);
    void putParameters(char *parameters);
    char* getParameters();
    int sendCommand(int32_t cmd, int32_t arg1, int32_t arg2);
    void release();
    int dump(int fd);
};

#endif
