# Copyright (C) 2014 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Inherit from mrvl-common
-include device/samsung/mrvl-common/BoardConfigCommon.mk

COMMON_PATH := device/samsung/pxa1908-common

include $(COMMON_PATH)/board/*.mk

TARGET_SYSTEM_PROP := $(COMMON_PATH)/system.prop

# Board specific headers
TARGET_SPECIFIC_HEADER_PATH := $(COMMON_PATH)/include

BOARD_PROVIDES_MKBOOTIMG := true
BOARD_MKBOOTIMG_MRVL := true

BOARD_PROVIDES_MKIMAGE := true
BOARD_MKIMAGE_MRVL := true

BOARD_CUSTOM_BOOTIMG_MK := hardware/marvell/bootimage/mkbootimg.mk

# CMHW
#BOARD_HARDWARE_CLASS += $(COMMON_PATH)/cmhw

# Custom RIL class
BOARD_RIL_CLASS := ../../../$(COMMON_PATH)/ril

# Fonts
EXTENDED_FONT_FOOTPRINT := true

# Init
TARGET_INIT_VENDOR_LIB := libinit_pxa1908
#TARGET_UNIFIED_DEVICE := true

# Display & Graphics
BOARD_EGL_CFG := $(COMMON_PATH)/configs/egl/egl.cfg
USE_OPENGL_RENDERER := true
ENABLE_WEBGL := true
LOCAL_CFLAGS += -DSK_SUPPORT_LEGACY_SETCONFIG
BOARD_HAVE_PIXEL_FORMAT_INFO := true
NUM_FRAMEBUFFER_SURFACE_BUFFERS := 3
BOARD_ENABLE_MULTI_DISPLAYS := true
BOARD_USE_VIVANTE_GRALLOC := true
HDMI_SUPPORT_3D := true

# Enable Marvell interface in SurfaceFlinger
#MRVL_INTERFACE_ANIMATION := true
# Launch DMS in SurfaceFlinger process
#MRVL_LAUNCH_DMS_IN_SURFACEFLINGER := true

ANDROID_ENABLE_RENDERSCRIPT := true

# Flags
LOCAL_CFLAGS += -DMRVL_HARDWARE
LOCAL_CFLAGS += -DNEEDS_VECTORIMPL_SYMBOLS
LOCAL_CFLAGS += -DNO_SECURE_DISCARD

# Webkit
ENABLE_WEBGL := true
BOARD_USE_SKIA_LCDTEXT := true
BOARD_NEEDS_CUTILS_LOG := true
BOARD_USES_HWCOMPOSER := true
