#include "stockcamera.h"

#include <dlfcn.h>

#define LOG_TAG "CameraReversing"
#include <cutils/log.h>

#define LOAD_FUNC(lib, func)   (*(int*)&func) = (int)dlsym(lib, #func)
#define LOAD_FUNC_CXX(lib, func, name) (*(int*)&func) = (int)dlsym(lib, name)

libstockcamera::libstockcamera()
{
    _lib = dlopen("/system/lib/hw/camera.stock.mrvl.so", RTLD_NOW);

    LOAD_FUNC_CXX(_lib, HAL_getNumberOfCameras        , "_ZN7android22HAL_getNumberOfCamerasEv");
    LOAD_FUNC_CXX(_lib, HAL_getCameraInfo             , "_ZN7android17HAL_getCameraInfoEiPNS_16mrvl_camera_infoE");
    LOAD_FUNC_CXX(_lib, CameraHardwareDxOConstructor1 , "_ZN7android17CameraHardwareDxOC1Ei");
    LOAD_FUNC_CXX(_lib, CameraHardwareDxODestructor1  , "_ZN7android17CameraHardwareDxOD1Ev");
    LOAD_FUNC_CXX(_lib, CameraHardwareSmtConstructor1 , "_ZN7android17CameraHardwareSmtC1Ei");
    LOAD_FUNC_CXX(_lib, CameraHardwareSmtDestructor1  , "_ZN7android17CameraHardwareSmtD1Ev");

    // CameraHardwareBase functions
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.setPreviewWindow       ,"_ZN7android18CameraHardwareBase16setPreviewWindowEP18preview_stream_ops");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.setCallbacks           ,"_ZN7android18CameraHardwareBase12setCallbacksEPFviiiPvEPFviPK13camera_memoryjP21camera_frame_metadataS1_EPFvxiS6_jS1_EPFPS4_ijjS1_ES1_");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.enableMsgType          ,"_ZN7android18CameraHardwareBase13enableMsgTypeEi");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.disableMsgType         ,"_ZN7android18CameraHardwareBase14disableMsgTypeEi");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.msgTypeEnabled         ,"_ZN7android18CameraHardwareBase14msgTypeEnabledEi");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.startPreview           ,"_ZN7android18CameraHardwareBase12startPreviewEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.stopPreview            ,"_ZN7android18CameraHardwareBase11stopPreviewEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.previewEnabled         ,"_ZN7android18CameraHardwareBase14previewEnabledEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.storeMetaDataInBuffers ,"_ZN7android18CameraHardwareBase22storeMetaDataInBuffersEi");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.autoFocus              ,"_ZN7android18CameraHardwareBase9autoFocusEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.cancelAutoFocus        ,"_ZN7android18CameraHardwareBase15cancelAutoFocusEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.takePicture            ,"_ZN7android18CameraHardwareBase11takePictureEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.cancelPicture          ,"_ZN7android18CameraHardwareBase13cancelPictureEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.setParameters          ,"_ZN7android18CameraHardwareBase13setParametersEPKc");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.putParameters          ,"_ZN7android18CameraHardwareBase13putParametersEPc");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.getParameters          ,"_ZN7android18CameraHardwareBase13getParametersEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.sendCommand            ,"_ZN7android18CameraHardwareBase11sendCommandEiii");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.release                ,"_ZN7android18CameraHardwareBase7releaseEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareBase.dump                   ,"_ZN7android18CameraHardwareBase4dumpEi");

    // CameraHardwareDxO virtual functions
    LOAD_FUNC_CXX(_lib, CameraHardwareDxO.startRecording          ,"_ZN7android17CameraHardwareDxO14startRecordingEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareDxO.stopRecording           ,"_ZN7android17CameraHardwareDxO13stopRecordingEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareDxO.recordingEnabled        ,"_ZN7android17CameraHardwareSmt16recordingEnabledEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareDxO.releaseRecordingFrame   ,"_ZN7android17CameraHardwareDxO21releaseRecordingFrameEPKv");

    // CameraHardwareDxO virtual functions
    LOAD_FUNC_CXX(_lib, CameraHardwareSmt.startRecording          ,"_ZN7android17CameraHardwareSmt14startRecordingEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareSmt.stopRecording           ,"_ZN7android17CameraHardwareSmt13stopRecordingEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareSmt.recordingEnabled        ,"_ZN7android17CameraHardwareSmt16recordingEnabledEv");
    LOAD_FUNC_CXX(_lib, CameraHardwareSmt.releaseRecordingFrame   ,"_ZN7android17CameraHardwareSmt21releaseRecordingFrameEPKv");

    // Get the original exported structure so we can get the camera_get_camera_info & camera_get_umber_of_cameras
    LOAD_FUNC_CXX(_lib, HMI, "HMI");

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

libstockcamera& libstockcamera::Inst()
{
    static libstockcamera x;
    return x;
}
