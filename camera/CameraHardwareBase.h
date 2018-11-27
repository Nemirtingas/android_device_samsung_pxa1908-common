#ifndef __CAMERAHARDWAREBASE_DEFINED__
#define __CAMERAHARDWAREBASE_DEFINED__

#include "Camera.h"
#include "stockcamera.h"
#include <utils/RefBase.h>

class CameraMsg;

class CameraHardwareBase : public android::RefBase
{
public:
    pthread_mutex_t camera_mutex;
    int field_C;
    CameraMsg *mMsg;
    int field_14;
    camera_request_memory request_memory;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
    int field_70;
    int field_74;
    int field_78;
    int field_7C;
    int field_80;
    int field_84;
    int field_88;
    int field_8C;
    int field_90;
    int field_94;
    int field_98;
    int field_9C;
    int field_A0;
    int field_A4;
    int field_A8;
    int field_AC;
    int field_B0;
    int field_B4;
    int field_B8;
    int field_BC;
    int field_C0;
    int field_C4;
    int field_C8;
    int field_CC;
    int field_D0;
    int field_D4;
    int field_D8;
    int field_DC;
    int field_E0;
    int field_E4;
    int field_E8;
    int field_EC;
    int field_F0;
    int field_F4;
    int field_F8;
    int field_FC;
    int field_100;
    int field_104;
    int frames;
    char field_10C[28];
    int32_t video_start_time_s;
    int32_t video_start_time_us;
    int32_t video_end_time_s;
    int32_t video_end_time_us;
    char y[53];
    char store_metadata_in_buffer;
    char field_16E[518];
    int field_378;
    int field_384;


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
