#include "FakeCam.h"

#include <camera/CameraParameters.h>
#include <cutils/properties.h>
#include <cstdlib>

mrvl_camera_info_t FakeCam::mCameraInfo[NUM_FAKE_CAMERAS] = {
    {
        .facing = 0,
        .orientation = 90,
        .field_8 = 256,
        .field_C = 0,
        .ports = 1
    },
    {
        .facing = 1,
        .orientation = 0,
        .field_8 = 256,
        .field_C = 0,
        .ports = 1
    },
};

static android::CameraParameters FakeCamParameters[NUM_FAKE_CAMERAS];

void FakeCam::getCameraInfo(int id, mrvl_camera_info_t *caminfo)
{
    char prop[PROPERTY_VALUE_MAX];

    *caminfo = mCameraInfo[id];
    property_get("service.camera.fake.facing", prop, "");
    if ( !strcmp(prop, "back") )
    {
        caminfo->facing = 0;
    }
    else if ( !strcmp(prop, "front") )
    {
        caminfo->facing = 1;
    }
    property_get("service.camera.fake.orient", prop, "");
    if ( prop[0] )
        caminfo->orientation = atoi(prop);
    caminfo->field_8 = 256;
}

int FakeCam::getNumberOfCameras()
{
    android::CameraParameters params;

    params.set(android::CameraParameters::KEY_PREVIEW_SIZE                  , "640x480");
    params.set(android::CameraParameters::KEY_SUPPORTED_PREVIEW_SIZES       , "176x144,320x240,640x480,720x480,800x480,1280x720");
    params.set(android::CameraParameters::KEY_PREVIEW_FORMAT                , "yuv420sp");
    params.set(android::CameraParameters::KEY_VIDEO_FRAME_FORMAT            , "yuv420sp");
    params.set(android::CameraParameters::KEY_SUPPORTED_PREVIEW_FORMATS     , "yuv420sp,yuv420p,yuv422i-uyvy,rgb565");
    params.set(android::CameraParameters::KEY_PREVIEW_FRAME_RATE            , "30");
    params.set(android::CameraParameters::KEY_SUPPORTED_PREVIEW_FRAME_RATES , "10,20,30");
    params.set(android::CameraParameters::KEY_PICTURE_SIZE                  , "2048x1536");
    params.set(android::CameraParameters::KEY_SUPPORTED_PICTURE_SIZES       , "176x144,320x240,640x480,720x480,800x480,1280x720,2048x1536");
    params.set(android::CameraParameters::KEY_PICTURE_FORMAT                , "jpeg");
    params.set(android::CameraParameters::KEY_SUPPORTED_PICTURE_FORMATS     , "jpeg");
    params.set(android::CameraParameters::KEY_JPEG_QUALITY                  , "90");
    params.set(android::CameraParameters::KEY_WHITE_BALANCE                 , "auto");
    params.set(android::CameraParameters::KEY_SUPPORTED_WHITE_BALANCE       , "auto,incandescent,fluorescent,warm-fluorescent,daylight,cloudy-daylight,twilight,shade");
    params.set(android::CameraParameters::KEY_EFFECT                        , "none");
    params.set(android::CameraParameters::KEY_SUPPORTED_EFFECTS             , "none,mono,negative,solarize,sepia,posterize,whiteboard,blackboard,aqua");
    params.set(android::CameraParameters::KEY_ANTIBANDING                   , "auto");
    params.set(android::CameraParameters::KEY_SUPPORTED_ANTIBANDING         , "auto,50hz,60hz,off");
    params.set(android::CameraParameters::KEY_FLASH_MODE                    , "off");
    params.set(android::CameraParameters::KEY_SUPPORTED_FLASH_MODES         , "off,auto,on,red-eye,torch");
    params.set(android::CameraParameters::KEY_FOCUS_MODE                    , "auto");
    params.set(android::CameraParameters::KEY_SUPPORTED_FOCUS_MODES         , "auto,infinity,macro,fixed,edof,continuous-video");
    params.set(android::CameraParameters::KEY_FOCAL_LENGTH                  , "0.1");
    params.set(android::CameraParameters::KEY_HORIZONTAL_VIEW_ANGLE         , "50");
    params.set(android::CameraParameters::KEY_FOCUS_DISTANCES               , "0.05,2,Infinity");
    params.set(android::CameraParameters::KEY_VERTICAL_VIEW_ANGLE           , "50");
    params.set(android::CameraParameters::KEY_JPEG_THUMBNAIL_WIDTH          , "160");
    params.set(android::CameraParameters::KEY_JPEG_THUMBNAIL_HEIGHT         , "120");
    params.set(android::CameraParameters::KEY_SUPPORTED_JPEG_THUMBNAIL_SIZES, "160x120,0x0");
    params.set(android::CameraParameters::KEY_JPEG_THUMBNAIL_QUALITY        , "80");
    params.set(android::CameraParameters::KEY_PREVIEW_FPS_RANGE             , "10000,30000");
    params.set(android::CameraParameters::KEY_SUPPORTED_PREVIEW_FPS_RANGE   , "10000,30000");
    params.set(android::CameraParameters::KEY_EXPOSURE_COMPENSATION         , "2");
    params.set(android::CameraParameters::KEY_MAX_EXPOSURE_COMPENSATION     , "7");
    params.set(android::CameraParameters::KEY_MIN_EXPOSURE_COMPENSATION     , "-7");
    params.set(android::CameraParameters::KEY_EXPOSURE_COMPENSATION_STEP    , "0.5");
    params.set(android::CameraParameters::KEY_ZOOM                          , "0");
    params.set(android::CameraParameters::KEY_MAX_ZOOM                      , "0");
    params.set(android::CameraParameters::KEY_ZOOM_RATIOS                   , "100");
    params.set(android::CameraParameters::KEY_ZOOM_SUPPORTED                , "false");
    params.set(android::CameraParameters::KEY_SMOOTH_ZOOM_SUPPORTED         , "false");
    params.set(android::CameraParameters::KEY_VIDEO_SNAPSHOT_SUPPORTED      , "false");

    FakeCamParameters[0] = params;
    FakeCamParameters[1] = params;

    FakeCamParameters[0].set(android::CameraParameters::KEY_PREVIEW_SIZE, "640x480");
    FakeCamParameters[1].set(android::CameraParameters::KEY_PREVIEW_SIZE, "720x480");

    FakeCamParameters[0].setPreviewFormat("yuv420sp");
    FakeCamParameters[1].setPreviewFormat("yuv420sp");

    FakeCamParameters[0].set(android::CameraParameters::KEY_VIDEO_FRAME_FORMAT, "yuv420sp");
    FakeCamParameters[1].set(android::CameraParameters::KEY_VIDEO_FRAME_FORMAT, "yuv420sp");

    return 2;
}
