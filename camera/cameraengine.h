#ifndef CAMERAENGINE_H_
#define CAMERAENGINE_H_

#include "CameraSetting.h"

typedef struct _CamHandle* CamHandle;

class libcameraengine
{
    libcameraengine();
    libcameraengine(const libcameraengine&);

    void *_lib;

public:
    static libcameraengine& Inst();
    int (*CAM_GetHandle)(CamHandle*);
    int (*CAM_EnumSensors)(CamHandle camHandle, int *sensorCount, CameraProperties *camprop);
    int (*CAM_FreeHandle)(CamHandle*);
};


#endif
