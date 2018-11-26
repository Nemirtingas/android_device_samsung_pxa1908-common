#ifndef CAMERASETTING_H_
#define CAMERASETTING_H_

#include "CameraHAL.h"

struct SettingCamInfo
{
  int facing;
  int orientation;
  char gap8[40];
  int camera_id;
  int field_34;
  int ports;
  int field_3C;
  int field_40;
};


class CameraSetting
{

public:
    static SettingCamInfo mMrvlCameraInfo[NUM_CAMERAS];
    static int iNumOfSensors;
    SettingCamInfo* getMrvlCameraInfo(int id);
};

#endif
