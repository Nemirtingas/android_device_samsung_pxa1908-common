#ifndef FAKECAM_H_
#define FAKECAM_H_

#include "CameraHAL.h"

#define NUM_FAKE_CAMERAS 2

class FakeCam
{

public:
    static mrvl_camera_info_t mCameraInfo[NUM_FAKE_CAMERAS];
    static void getCameraInfo(int id, mrvl_camera_info_t *caminfo);
    static int getNumberOfCameras();
};

#endif
