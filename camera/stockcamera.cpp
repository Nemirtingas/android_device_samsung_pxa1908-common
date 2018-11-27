#include "stockcamera.h"

#include <dlfcn.h>

#define LOAD_FUNC(lib, func)   (*(int*)&func) = (int)dlsym(_lib, #func)

libstockcamera::libstockcamera()
{
    _lib = dlopen("/system/lib/hw/camera.stock.mrvl.so", RTLD_NOW);
    LOAD_FUNC(_lib, open_dev);
    *(int*)&CameraHardwareDxOConstructor1 = (int)dlsym(_lib, "_ZN7android17CameraHardwareDxOC1Ei");
    *(int*)&CameraHardwareDxODestructor1 = (int)dlsym(_lib, "_ZN7android17CameraHardwareDxOD1Ev");
    *(int*)&CameraHardwareSmtConstructor1 = (int)dlsym(_lib, "_ZN7android17CameraHardwareSmtC1Ei");
    *(int*)&CameraHardwareSmtDestructor1 = (int)dlsym(_lib, "_ZN7android17CameraHardwareSmtD1Ev");

    *(int*)&CameraHardwareBase.setPreviewWindow       = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase16setPreviewWindowEP18preview_stream_ops");
    *(int*)&CameraHardwareBase.setCallbacks           = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase12setCallbacksEPFviiiPvEPFviPK13camera_memoryjP21camera_frame_metadataS1_EPFvxiS6_jS1_EPFPS4_ijjS1_ES1_");
    *(int*)&CameraHardwareBase.enableMsgType          = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase13enableMsgTypeEi");
    *(int*)&CameraHardwareBase.disableMsgType         = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase14disableMsgTypeEi");
    *(int*)&CameraHardwareBase.msgTypeEnabled         = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase14msgTypeEnabledEi");
    *(int*)&CameraHardwareBase.startPreview           = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase12startPreviewEv");
    *(int*)&CameraHardwareBase.stopPreview            = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase11stopPreviewEv");
    *(int*)&CameraHardwareBase.previewEnabled         = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase14previewEnabledEv");
    *(int*)&CameraHardwareBase.storeMetaDataInBuffers = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase22storeMetaDataInBuffersEi");
    //*(int*)&CameraHardwareBase.startRecording         = (int)dlsym(_lib,
    //*(int*)&CameraHardwareBase.stopRecording          = (int)dlsym(_lib,
    //*(int*)&CameraHardwareBase.recordingEnabled       = (int)dlsym(_lib,
    //*(int*)&CameraHardwareBase.releaseRecordingFrame  = (int)dlsym(_lib,
    *(int*)&CameraHardwareBase.autoFocus              = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase9autoFocusEv");
    *(int*)&CameraHardwareBase.cancelAutoFocus        = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase15cancelAutoFocusEv");
    *(int*)&CameraHardwareBase.takePicture            = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase11takePictureEv");
    *(int*)&CameraHardwareBase.cancelPicture          = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase13cancelPictureEv");
    *(int*)&CameraHardwareBase.setParameters          = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase13setParametersEPKc");
    *(int*)&CameraHardwareBase.putParameters          = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase13putParametersEPc");
    *(int*)&CameraHardwareBase.getParameters          = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase13getParametersEv");
    *(int*)&CameraHardwareBase.sendCommand            = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase11sendCommandEiii");
    *(int*)&CameraHardwareBase.release                = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase7releaseEv");
    *(int*)&CameraHardwareBase.dump                   = (int)dlsym(_lib, "_ZN7android18CameraHardwareBase4dumpEi");
}

libstockcamera& libstockcamera::Inst()
{
    static libstockcamera x;
    return x;
}
