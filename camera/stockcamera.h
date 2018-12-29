#ifndef STOCKCAMERA_H_
#define STOCKCAMERA_H_

#include "CameraHAL.h"

class libstockcamera
{
    libstockcamera(const libstockcamera&);

    void *_lib;

public:
    libstockcamera();
    ~libstockcamera();

    int   (*camera_open_dev)(const hw_module_t* mod, const char* name, hw_device_t** dev);
    int   (*camera_get_number_of_cameras)();
    int   (*camera_get_camera_info)(int id, struct camera_info* info);

    camera_module_t *HMI;
    int *iNumOfSensors;
};

#endif
