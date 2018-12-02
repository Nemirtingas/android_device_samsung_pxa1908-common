#ifndef STOCKCAMERA_H_
#define STOCKCAMERA_H_

#include "CameraSetting.h"

class libstockcamera
{
    libstockcamera();
    libstockcamera(const libstockcamera&);

    void *_lib;

public:
    static libstockcamera& Inst();

    int   (*camera_open_dev)(const hw_module_t* mod, const char* name, hw_device_t** dev);
    int   (*camera_get_number_of_cameras)();
    int   (*camera_get_camera_info)(int id, struct camera_info* info);
    int   (*HAL_getNumberOfCameras)();
    void  (*HAL_getCameraInfo)(int id, mrvl_camera_info_t *info);

    void* (*CameraHardwareDxOConstructor1)(void* ptr, int cameraId);
    void* (*CameraHardwareDxODestructor1)(void* ptr);
    void* (*CameraHardwareSmtConstructor1)(void* ptr, int cameraId);
    void* (*CameraHardwareSmtDestructor1)(void* ptr);

    struct
    {
        int   (*setPreviewWindow)      (void*, struct preview_stream_ops *ops);
        void  (*setCallbacks)          (void*, camera_notify_callback notify_callback, camera_data_callback data_callback, camera_data_timestamp_callback timestamp_callback, camera_request_memory request_memory, void *datas);
        void  (*enableMsgType)         (void*, int32_t msg_type);
        void  (*disableMsgType)        (void*, int32_t msg_type);
        int   (*msgTypeEnabled)        (void*, int32_t msg_type);
        int   (*startPreview)          (void*);
        void  (*stopPreview)           (void*);
        int   (*previewEnabled)        (void*);
        int   (*storeMetaDataInBuffers)(void*, int store);
        int   (startRecording)        (void*){return 0;}
        void  (stopRecording)         (void*){}
        int   (recordingEnabled)      (void*){return 0;}
        void  (releaseRecordingFrame) (void*, const void *frame){}
        int   (*autoFocus)             (void*);
        int   (*cancelAutoFocus)       (void*);
        int   (*takePicture)           (void*);
        int   (*cancelPicture)         (void*);
        int   (*setParameters)         (void*, const char *parameters);
        void  (*putParameters)         (void*, char *parameters);
        char* (*getParameters)         (void*);
        int   (*sendCommand)           (void*, int32_t cmd, int32_t arg1, int32_t arg2);
        void  (*release)               (void*);
        int   (*dump)                  (void*, int fd);
    } CameraHardwareBase;

    struct
    {
        int  (*startRecording)(void *obj);
        void (*stopRecording)(void *obj);
        int  (*recordingEnabled)(void *obj);
        void (*releaseRecordingFrame)(void *obj, const void *frame);
    } CameraHardwareDxO;

    struct
    {
        int  (*startRecording)(void *obj);
        void (*stopRecording)(void *obj);
        int  (*recordingEnabled)(void *obj);
        void (*releaseRecordingFrame)(void *obj, const void *frame);
    } CameraHardwareSmt;

    camera_module_t *HMI;
    int *iNumOfSensors;
};

class StockCameraHardwareBase
{
public:
    char memory[904];

    virtual ~StockCameraHardwareBase()
    {
    }

    int setPreviewWindow(struct preview_stream_ops *ops)
    {
        return libstockcamera::Inst().CameraHardwareBase.setPreviewWindow(memory, ops);
    }

    void setCallbacks(camera_notify_callback notify_callback, camera_data_callback data_callback, camera_data_timestamp_callback timestamp_callback, camera_request_memory request_memory, void *datas)
    {
        libstockcamera::Inst().CameraHardwareBase.setCallbacks(memory, notify_callback, data_callback, timestamp_callback, request_memory, datas);
    }

    void enableMsgType(int32_t msg_type)
    {
        libstockcamera::Inst().CameraHardwareBase.enableMsgType(memory, msg_type);
    }

    void disableMsgType(int32_t msg_type)
    {
        libstockcamera::Inst().CameraHardwareBase.disableMsgType(memory, msg_type);
    }

    int msgTypeEnabled(int32_t msg_type)
    {
        return libstockcamera::Inst().CameraHardwareBase.msgTypeEnabled(memory, msg_type);
    }

    int startPreview()
    {
        return libstockcamera::Inst().CameraHardwareBase.startPreview(memory);
    }

    void stopPreview()
    {
        libstockcamera::Inst().CameraHardwareBase.stopPreview(memory);
    }

    int previewEnabled()
    {
        return libstockcamera::Inst().CameraHardwareBase.previewEnabled(memory);
    }

    int storeMetaDataInBuffers(int store)
    {
        return libstockcamera::Inst().CameraHardwareBase.storeMetaDataInBuffers(memory, store);
    }

    virtual int startRecording()
    {
        return 0;
    }

    virtual void stopRecording()
    {
    }

    virtual int recordingEnabled()
    {
        return 0;
    }

    virtual void releaseRecordingFrame(const void *frame)
    {
    }

    int autoFocus()
    {
        return libstockcamera::Inst().CameraHardwareBase.autoFocus(memory);
    }

    int cancelAutoFocus()
    {
        return libstockcamera::Inst().CameraHardwareBase.cancelAutoFocus(memory);
    }

    int takePicture()
    {
        return libstockcamera::Inst().CameraHardwareBase.takePicture(memory);
    }

    int cancelPicture()
    {
        return libstockcamera::Inst().CameraHardwareBase.cancelPicture(memory);
    }

    int setParameters(const char *parameters)
    {
        return libstockcamera::Inst().CameraHardwareBase.setParameters(memory, parameters);
    }

    void putParameters(char *parameters)
    {
        libstockcamera::Inst().CameraHardwareBase.putParameters(memory, parameters);
    }

    char* getParameters()
    {
        return libstockcamera::Inst().CameraHardwareBase.getParameters(memory);
    }

    int sendCommand(int32_t cmd, int32_t arg1, int32_t arg2)
    {
        return libstockcamera::Inst().CameraHardwareBase.sendCommand(memory, cmd, arg1, arg2);
    }

    void release()
    {
        libstockcamera::Inst().CameraHardwareBase.release(memory);
    }

    int dump(int fd)
    {
        return libstockcamera::Inst().CameraHardwareBase.dump(memory, fd);
    }
};

class StockCameraHardwareDxO : public StockCameraHardwareBase
{
public:
    StockCameraHardwareDxO(int cameraId)
    {
        libstockcamera::Inst().CameraHardwareDxOConstructor1(memory, cameraId);
    }

    virtual ~StockCameraHardwareDxO()
    {
        libstockcamera::Inst().CameraHardwareDxODestructor1(memory);
    }
    /*
    virtual int startRecording()
    {
        return libstockcamera::Inst().CameraHardwareDxO.startRecording(memory);
    }

    virtual void stopRecording()
    {
        libstockcamera::Inst().CameraHardwareDxO.stopRecording(memory);
    }

    virtual int recordingEnabled()
    {
        return libstockcamera::Inst().CameraHardwareDxO.recordingEnabled(memory);
    }

    virtual void releaseRecordingFrame(const void *frame)
    {
        libstockcamera::Inst().CameraHardwareDxO.releaseRecordingFrame(memory, frame);
    }
    */
};

class StockCameraHardwareSmt : public StockCameraHardwareBase
{
public:
    StockCameraHardwareSmt(int cameraId)
    {
        libstockcamera::Inst().CameraHardwareSmtConstructor1(memory, cameraId);
    }

    virtual ~StockCameraHardwareSmt()
    {
        libstockcamera::Inst().CameraHardwareSmtDestructor1(memory);
    }
    /*
    virtual int startRecording()
    {
        return libstockcamera::Inst().CameraHardwareSmt.startRecording(memory);
    }

    virtual void stopRecording()
    {
        libstockcamera::Inst().CameraHardwareSmt.stopRecording(memory);
    }

    virtual int recordingEnabled()
    {
        return libstockcamera::Inst().CameraHardwareSmt.recordingEnabled(memory);
    }

    virtual void releaseRecordingFrame(const void *frame)
    {
        libstockcamera::Inst().CameraHardwareSmt.releaseRecordingFrame(memory, frame);
    }
    */
};

#endif
