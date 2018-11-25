#ifndef __CAMERAHARDWAREDXO_DEFINED__
#define __CAMERAHARDWAREDXO_DEFINED__

#include "CameraHardwareBase.h"

class CameraHardwareDxO : public CameraHardwareBase
{
public:
    CameraHardwareDxO(int cameraId) : CameraHardwareBase(cameraId)
    {}
};

#endif
