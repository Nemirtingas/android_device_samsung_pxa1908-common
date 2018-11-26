#ifndef CAMERASETTING_H_
#define CAMERASETTING_H_

#include "CameraHAL.h"

struct SettingCamInfo
{
  int facing;
  int orientation;
  char gap8[8];
  char sensor[32];
  int sensorid;
  int engsensorid;
  int ports;
  char field_3C[8];
};


class CameraSetting
{

public:
    static SettingCamInfo mMrvlCameraInfo[NUM_CAMERAS];
    static int iNumOfSensors;

    static SettingCamInfo* getMrvlCameraInfo(int id);
    static int initCameraTable(CameraProperties *camprop, int sensorid, int engsendorid, int facing, int orient);
    static int getNumOfCameras();
};

#endif
