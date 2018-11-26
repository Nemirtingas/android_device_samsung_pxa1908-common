#ifndef ENGINE_H_
#define ENGINE_H_

#include "CameraHAL.h"
#include "CameraSetting.h"

class Engine
{
public:
    static void getCameraInfo(int id, mrvl_camera_info_t *caminfos);
};

#endif
