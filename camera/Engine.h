#ifndef ENGINE_H_
#define ENGINE_H_

#include "CameraHAL.h"
#include "CameraSetting.h"
#include "cameraengine.h"

class Engine
{
public:
    static int iSensorCount;
    static CameraProperties stCameraProp[4];
    static void getCameraInfo(int id, mrvl_camera_info_t *caminfos);
    static void getModuleInfo(int id, ModuleInfo *modinfo);
    static int getNumberOfCameras();
};

#endif
