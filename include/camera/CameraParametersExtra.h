// Overload this file in your device specific config if you need
// to add extra camera parameters.
// A typical file would look like this:
/*
 * Copyright (C) 2014 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define CAMERA_PARAMETERS_EXTRA_C \
const char CameraParameters::KEY_SUPPORTED_ISO_MODES[]    = "iso-mode-values"; \
const char CameraParameters::PIXEL_FORMAT_YUV420P_I420[]  = "yuv420p-i420"; \
const char CameraParameters::PIXEL_FORMAT_YUV420SP_NV12[] = "yuv420sp-nv12"; \
const char CameraParameters::PIXEL_FORMAT_YUV420SP_NV21[] = "nv21"; \
const char CameraParameters::PIXEL_FORMAT_YUV422I_UYVY[]  = "yuv422i-uyvy"; \
const char CameraParameters::PIXEL_FORMAT_YUV422P[]       = "yuv422p"; \
const char CameraParameters::KEY_MAX_CONTRAST[]           = "max-contrast"; \
const char CameraParameters::KEY_MIN_CONTRAST[]           = "min-contrast"; \
const char CameraParameters::KEY_MAX_SATURATION[]         = "max-saturation"; \
const char CameraParameters::KEY_MIN_SATURATION[]         = "min-saturation"; \
const char CameraParameters::KEY_MAX_BRIGHTNESS[]         = "max-brightness"; \
const char CameraParameters::KEY_MIN_BRIGHTNESS[]         = "min-brightness"; \
const char CameraParameters::KEY_MAX_SHARPNESS[]          = "max-sharpness"; \
const char CameraParameters::KEY_MIN_SHARPNESS[]          = "min-sharpness"; \
const char CameraParameters::BURST_CAPTURE_MODE_OFF[]     = "off-burst"; \
const char CameraParameters::KEY_SUPPORTED_BURST_CAPTURE_MODES[] = "burst-capture-mode-values"; \
const char CameraParameters::KEY_MAX_BURST_CAPTURE_NUM[]  = "max-burst-capture-number"; \
const char CameraParameters::KEY_BURST_CAPTURE_MODE[]     = "burst-capture-mode"; \
const char CameraParameters::HDR_MODE_OFF[]               = "off"; \
const char CameraParameters::HDR_MODE_ON[]                = "on"; \
const char CameraParameters::KEY_SUPPORTED_HDR_MODES[]    = "hdr-mode-values"; \
const char CameraParameters::KEY_FACE_BEAUTIFY_SUPPORTED[]= "face-beautify-supported"; \
const char CameraParameters::KEY_VIDEO_TNR_SUPPORTED[]    = "video-tnr-supported"; \
const char CameraParameters::KEY_SMILE_DETECTION_SUPPORTED[] = "smile-detection-supported"; \
const char CameraParameters::KEY_BLINK_DETECTION_SUPPORTED[] = "blink-detection-supported"; \
const char CameraParameters::KEY_SUPPORTED_VIDEO_SCENE_MODES[] = "video-scene-mode-values"; \
const char CameraParameters::KEY_VIDEO_SCENE_MODE[]       = "video-scene-mode"; \
const char CameraParameters::EFFECT_VIVID[]               = "vivid"; \
const char CameraParameters::EFFECT_OLDMOVIE[]            = "oldmovie"; \
const char CameraParameters::EFFECT_TOONSHADING[]         = "toonshading"; \
const char CameraParameters::EFFECT_PENCILSKETCH[]        = "pencilsketch"; \
const char CameraParameters::EFFECT_GLOW[]                = "glow"; \
const char CameraParameters::EFFECT_TWIST[]               = "twist"; \
const char CameraParameters::EFFECT_FRAME[]               = "frame"; \
const char CameraParameters::EFFECT_SUNSHINE[]            = "sunshine"; \
const char CameraParameters::FOCUS_MODE_MANUAL[]          = "manual"; \
const char CameraParameters::SCENE_MODE_MACRO[]           = "macro"; \
const char CameraParameters::SCENE_MODE_DETECT[]          = "scene-detect"; \
const char CameraParameters::SCENE_MODE_BESTSHOT[]        = "best-shot"; \
const char CameraParameters::SCENE_MODE_TEST[]            = "scene-test"; \
const char CameraParameters::ISO_MODE_AUTO[]              = "auto"; \
const char CameraParameters::ISO_MODE_50[]                = "50"; \
const char CameraParameters::ISO_MODE_100[]               = "100"; \
const char CameraParameters::ISO_MODE_200[]               = "200"; \
const char CameraParameters::ISO_MODE_400[]               = "400"; \
const char CameraParameters::ISO_MODE_800[]               = "800"; \
const char CameraParameters::ISO_MODE_1600[]              = "1600"; \
const char CameraParameters::ISO_MODE_3200[]              = "3200"; \
const char CameraParameters::BURST_CAPTURE_MODE_FAST[]    = "fast-burst"; \
const char CameraParameters::BURST_CAPTURE_MODE_BRACKET[] = "bracket-burst"; \
const char CameraParameters::BURST_CAPTURE_MODE_INFINITE[]= "infinite-burst"; \
const char CameraParameters::KEY_ISO_MODE[]               = "iso-mode"; \
const char CameraParameters::KEY_HDR_MODE[]               = "hdr-mode"; \
const char CameraParameters::KEY_BRIGHTNESS[]             = "light_key"; \
const char CameraParameters::KEY_SHARPNESS[]              = "sharpness"; \
const char CameraParameters::KEY_CONTRAST[]               = "contrast"; \
const char CameraParameters::KEY_SATURATION[]             = "saturation"; \
const char CameraParameters::KEY_BURST_CAPTURE_NUM[]      = "burst-capture-number"; \
const char CameraParameters::KEY_EXPOSURE_MODE[]          = "exposure-mode"; \
const char CameraParameters::KEY_SHUTTER_SPEED[]          = "shutter-speed"; \
const char CameraParameters::KEY_FOCUS_POSITION[]         = "focus-position"; \
const char CameraParameters::KEY_Y_DNS[]                  = "y-dns"; \
const char CameraParameters::KEY_UV_DNS[]                 = "uv-dns"; \
const char CameraParameters::KEY_DNS_TIMES[]              = "dns-times"; \
const char CameraParameters::KEY_FACE_BEAUTIFY[]          = "face-beautify"; \
const char CameraParameters::KEY_A_GAIN[]                 = "a-gain"; \
const char CameraParameters::KEY_D_GAIN[]                 = "g-gain"; \
const char CameraParameters::KEY_ISP_GAIN[]               = "isp-gain"; \
const char CameraParameters::KEY_B_GAIN[]                 = "b-gain"; \
const char CameraParameters::KEY_GB_GAIN[]                = "gb-gain"; \
const char CameraParameters::KEY_R_GAIN[]                 = "r-gain"; \
const char CameraParameters::KEY_GR_GAIN[]                = "gr-gain"; \
const char CameraParameters::KEY_VIDEO_TNR[]              = "video-tnr"; \

#define CAMERA_PARAMETERS_EXTRA_H \
    static const char KEY_SUPPORTED_ISO_MODES[]; \
    static const char PIXEL_FORMAT_YUV420P_I420[]; \
    static const char PIXEL_FORMAT_YUV420SP_NV12[]; \
    static const char PIXEL_FORMAT_YUV420SP_NV21[]; \
    static const char PIXEL_FORMAT_YUV422I_UYVY[]; \
    static const char PIXEL_FORMAT_YUV422P[]; \
    static const char KEY_MAX_CONTRAST[]; \
    static const char KEY_MIN_CONTRAST[]; \
    static const char KEY_MAX_SATURATION[]; \
    static const char KEY_MIN_SATURATION[]; \
    static const char KEY_MAX_BRIGHTNESS[]; \
    static const char KEY_MIN_BRIGHTNESS[]; \
    static const char KEY_MAX_SHARPNESS[]; \
    static const char KEY_MIN_SHARPNESS[]; \
    static const char BURST_CAPTURE_MODE_OFF[]; \
    static const char KEY_SUPPORTED_BURST_CAPTURE_MODES[]; \
    static const char KEY_MAX_BURST_CAPTURE_NUM[]; \
    static const char KEY_BURST_CAPTURE_MODE[]; \
    static const char HDR_MODE_OFF[]; \
    static const char HDR_MODE_ON[]; \
    static const char KEY_SUPPORTED_HDR_MODES[]; \
    static const char KEY_FACE_BEAUTIFY_SUPPORTED[]; \
    static const char KEY_VIDEO_TNR_SUPPORTED[]; \
    static const char KEY_SMILE_DETECTION_SUPPORTED[]; \
    static const char KEY_BLINK_DETECTION_SUPPORTED[]; \
    static const char KEY_SUPPORTED_VIDEO_SCENE_MODES[]; \
    static const char KEY_VIDEO_SCENE_MODE[]; \
    static const char EFFECT_VIVID[]; \
    static const char EFFECT_OLDMOVIE[]; \
    static const char EFFECT_TOONSHADING[]; \
    static const char EFFECT_PENCILSKETCH[]; \
    static const char EFFECT_GLOW[]; \
    static const char EFFECT_TWIST[]; \
    static const char EFFECT_FRAME[]; \
    static const char EFFECT_SUNSHINE[]; \
    static const char FOCUS_MODE_MANUAL[]; \
    static const char SCENE_MODE_MACRO[]; \
    static const char SCENE_MODE_DETECT[]; \
    static const char SCENE_MODE_BESTSHOT[]; \
    static const char SCENE_MODE_TEST[]; \
    static const char ISO_MODE_AUTO[]; \
    static const char ISO_MODE_50[]; \
    static const char ISO_MODE_100[]; \
    static const char ISO_MODE_200[]; \
    static const char ISO_MODE_400[]; \
    static const char ISO_MODE_800[]; \
    static const char ISO_MODE_1600[]; \
    static const char ISO_MODE_3200[]; \
    static const char BURST_CAPTURE_MODE_FAST[]; \
    static const char BURST_CAPTURE_MODE_BRACKET[]; \
    static const char BURST_CAPTURE_MODE_INFINITE[]; \
    static const char KEY_ISO_MODE[]; \
    static const char KEY_HDR_MODE[]; \
    static const char KEY_BRIGHTNESS[]; \
    static const char KEY_SHARPNESS[]; \
    static const char KEY_CONTRAST[]; \
    static const char KEY_SATURATION[]; \
    static const char KEY_BURST_CAPTURE_NUM[]; \
    static const char KEY_EXPOSURE_MODE[]; \
    static const char KEY_SHUTTER_SPEED[]; \
    static const char KEY_FOCUS_POSITION[]; \
    static const char KEY_Y_DNS[]; \
    static const char KEY_UV_DNS[]; \
    static const char KEY_DNS_TIMES[]; \
    static const char KEY_FACE_BEAUTIFY[]; \
    static const char KEY_A_GAIN[]; \
    static const char KEY_D_GAIN[]; \
    static const char KEY_ISP_GAIN[]; \
    static const char KEY_B_GAIN[]; \
    static const char KEY_GB_GAIN[]; \
    static const char KEY_R_GAIN[]; \
    static const char KEY_GR_GAIN[]; \
    static const char KEY_VIDEO_TNR[]; \
