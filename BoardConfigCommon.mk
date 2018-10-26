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

DEVICE_PATH := device/samsung/pxa1908-common

TARGET_BOARD_PLATFORM := mrvl
TARGET_BOARD_SOC := pxa1908

TARGET_CUSTOM_DTBTOOL := dtbToolpxa1908
BOARD_CUSTOM_BOOTIMG_MK := device/samsung/mrvl-common/tools/custom_mkbootimg.mk

# GPU
TARGET_BOARD_PLATFORM_GPU := vivante-gc700

# Enabling this resolv zygote's descriptor table, but ROM doesn't boot...
#TARGET_SPECIFIC_HEADER_PATH := $(DEVICE_PATH)/include

# Init
TARGET_INIT_VENDOR_LIB := libinit_pxa1908
TARGET_UNIFIED_DEVICE := true

# Camera
TARGET_PROVIDES_CAMERA_HAL := true
USE_DEVICE_SPECIFIC_CAMERA := true

# Charger
BOARD_CHARGER_ENABLE_SUSPEND := true
BOARD_CHARGER_SHOW_PERCENYAGE := true

# Charging Mode
BOARD_CHARGING_MODE_BOOTING_LPM := true

# Crypto
#TARGET_HW_DISK_ENCRYPTION := true

# Display & Graphics
USE_OPENGL_RENDERER := true
ENABLE_WEBGL := true
LOCAL_CFLAGS += -DSK_SUPPORT_LEGACY_SETCONFIG
BOARD_EGL_CFG := $(DEVICE_PATH)/configs/egl/egl.cfg
BOARD_HAVE_PIXEL_FORMAT_INFO := true
NUM_FRAMEBUFFER_SURFACE_BUFFERS := 3
BOARD_ENABLE_MULTI_DISPLAYS := true
BOARD_USE_VIVANTE_GRALLOC := true
HDMI_SUPPORT_3D := true
# Enable Marvell interface in SurfaceFlinger
MRVL_INTERFACE_ANIMATION := true
# Launch DMS in SurfaceFlinger process
MRVL_LAUNCH_DMS_IN_SURFACEFLINGER := true

# Flags
LOCAL_CFLAGS += -DMRVL_HARDWARE
LOCAL_CFLAGS += -DNEEDS_VECTORIMPL_SYMBOLS
LOCAL_CFLAGS += -DNO_SECURE_DISCARD

# Webkit
ENABLE_WEBGL := true
BOARD_USE_SKIA_LCDTEXT := true
BOARD_NEEDS_CUTILS_LOG := true
BOARD_USES_HWCOMPOSER := true

# Wifi
#BOARD_WLAN_VENDOR := MRVL
#MRVL_WIRELESS_DAEMON_API := true
#BOARD_WLAN_DEVICE                := qcwcn
#BOARD_HOSTAPD_DRIVER             := NL80211
#BOARD_HOSTAPD_PRIVATE_LIB        := lib_driver_cmd_$(BOARD_WLAN_DEVICE)
#BOARD_WPA_SUPPLICANT_DRIVER      := NL80211
#BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_$(BOARD_WLAN_DEVICE)
#TARGET_PROVIDES_WCNSS_QMI        := true
#TARGET_USES_QCOM_WCNSS_QMI       := true
#TARGET_USES_WCNSS_CTRL           := true
#WPA_SUPPLICANT_VERSION           := VER_0_8_X
#WIFI_DRIVER_FW_PATH_STA          := "/system/etc/firmware/mrvl/sd8777_uapsta.bin"
#WIFI_DRIVER_FW_PATH_AP           := "/system/etc/firmware/mrvl/sd8777_uapsta.bin"
