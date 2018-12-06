#ifndef __CAMERAHARDWARESMT_DEFINED__
#define __CAMERAHARDWARESMT_DEFINED__

#include "CameraHardwareBase.h"

class CameraHardwareSmt : public CameraHardwareBase
{
public:
    CameraHardwareSmt(int cameraId) : CameraHardwareBase(cameraId)
    {}
};

#endif
