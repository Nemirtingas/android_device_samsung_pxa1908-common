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

$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)

# Overlay
DEVICE_PACKAGE_OVERLAYS += $(LOCAL_PATH)/overlay

# Screen density
PRODUCT_AAPT_CONFIG := normal
PRODUCT_AAPT_PREF_CONFIG := hdpi

# Boot animation
TARGET_SCREEN_HEIGHT := 960
TARGET_SCREEN_WIDTH  := 540

# RTCCD3 (zram daemon)
PRODUCT_PACKAGES += \
    rtccd3

# Audio
PRODUCT_PACKAGES += \
    audio.primary.default \
    audio_policy.default \
    audio.a2dp.default \
    audio.r_submix.default \
    audio.primary.mrvl \
    audio.usb.default \

PRODUCT_PACKAGES += libstlport

# Camera
############
##  WIP  ###
############
PRODUCT_PACKAGES += \
    libstlport \
    libvndbnd \
    camera.stock \
    camera.mrvl \
    camera_client \
    Torch \
    #Snap \


PRODUCT_PACKAGES += vndui

# Data patterns
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/camera/datapattern_420sp.yuv:system/cameradata/datapattern_420sp.yuv \
    $(LOCAL_PATH)/configs/camera/datapattern_front_420sp.yuv:system/cameradata/datapattern_front_420sp.yuv

# Camera configs
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/camera/back_camera_scene.cfg:system/etc/back_camera_scene.cfg \
    $(LOCAL_PATH)/configs/camera/camera_module_info.xml:system/etc/camera_module_info.xml \
    $(LOCAL_PATH)/configs/camera/camera_profiles.xml:system/etc/camera_profiles.xml \
    $(LOCAL_PATH)/configs/camera/control_param_uvdns.txt:system/etc/control_param_uvdns.txt \
    $(LOCAL_PATH)/configs/camera/front_camera_scene.cfg:system/etc/front_camera_scene.cfg \
    $(LOCAL_PATH)/configs/camera/pipeline_config.xml:system/etc/pipeline_config.xml

# Camera datas
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/camera/common_scene_tuning.data:system/etc/common_scene_tuning.data \
    $(LOCAL_PATH)/configs/camera/gc2235_still_tuning.data:system/etc/gc2235_still_tuning.data \
    $(LOCAL_PATH)/configs/camera/gc2235_video_tuning.data:system/etc/gc2235_video_tuning.data \
    $(LOCAL_PATH)/configs/camera/imx132_still_tuning.data:system/etc/imx132_still_tuning.data \
    $(LOCAL_PATH)/configs/camera/imx132_video_tuning.data:system/etc/imx132_video_tuning.data \
    $(LOCAL_PATH)/configs/camera/imx135_still_tuning.data:system/etc/imx135_still_tuning.data \
    $(LOCAL_PATH)/configs/camera/imx135_video_tuning.data:system/etc/imx135_video_tuning.data \
    $(LOCAL_PATH)/configs/camera/kerr_samsung.s5k4h5_tuning.data:system/etc/kerr_samsung.s5k4h5_tuning.data \
    $(LOCAL_PATH)/configs/camera/lsi3h5_still_tuning.data:system/etc/lsi3h5_still_tuning.data \
    $(LOCAL_PATH)/configs/camera/lsi3h5_video_tuning.data:system/etc/lsi3h5_video_tuning.data \
    $(LOCAL_PATH)/configs/camera/lsi3h7_still_tuning.data:system/etc/lsi3h7_still_tuning.data \
    $(LOCAL_PATH)/configs/camera/lsi3h7_video_tuning.data:system/etc/lsi3h7_video_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov5647_darling_still_tuning.data:system/etc/ov5647_darling_still_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov5647_darling_video_tuning.data:system/etc/ov5647_darling_video_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov5647_qtech_still_tuning.data:system/etc/ov5647_qtech_still_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov5647_qtech_video_tuning.data:system/etc/ov5647_qtech_video_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov5647_sunny_still_tuning.data:system/etc/ov5647_sunny_still_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov5647_sunny_video_tuning.data:system/etc/ov5647_sunny_video_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov5648_sunny_af_still_tuning.data:system/etc/ov5648_sunny_af_still_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov5648_sunny_af_video_tuning.data:system/etc/ov5648_sunny_af_video_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov5648_sunny_ff_still_tuning.data:system/etc/ov5648_sunny_ff_still_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov5648_sunny_ff_video_tuning.data:system/etc/ov5648_sunny_ff_video_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov8825_still_tuning.data:system/etc/ov8825_still_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov8825_video_tuning.data:system/etc/ov8825_video_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov8835_still_tuning.data:system/etc/ov8835_still_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov8835_video_tuning.data:system/etc/ov8835_video_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov8850_still_tuning.data:system/etc/ov8850_still_tuning.data \
    $(LOCAL_PATH)/configs/camera/ov8850_video_tuning.data:system/etc/ov8850_video_tuning.data \
    $(LOCAL_PATH)/configs/camera/semco_3h5_tuning.data:system/etc/semco_3h5_tuning.data \
    $(LOCAL_PATH)/configs/camera/semco_imx219_tuning.data:system/etc/semco_imx219_tuning.data \
    $(LOCAL_PATH)/configs/camera/semco_samsung.s5k3l2_tuning.data:system/etc/semco_samsung.s5k3l2_tuning.data \
    $(LOCAL_PATH)/configs/camera/semco_samsung.sr544_tuning.data:system/etc/semco_samsung.sr544_tuning.data \
    $(LOCAL_PATH)/configs/camera/semco_ssa.s5k5e3_tuning.data:system/etc/semco_ssa.s5k5e3_tuning.data \
    $(LOCAL_PATH)/configs/camera/semco_xcover_samsung.sr544_tuning.data:system/etc/semco_xcover_samsung.sr544_tuning.data \
    $(LOCAL_PATH)/configs/camera/sunny_ovt.ov13850_tuning.data:system/etc/sunny_ovt.ov13850_tuning.data \
    $(LOCAL_PATH)/configs/camera/sunny_ovt.ov13850r2a_tuning.data:system/etc/sunny_ovt.ov13850r2a_tuning.data \
    $(LOCAL_PATH)/configs/camera/sunny_ovt.ov2680_tuning.data:system/etc/sunny_ovt.ov2680_tuning.data \
    $(LOCAL_PATH)/configs/camera/sunny_ovt.ov5648_tuning.data:system/etc/sunny_ovt.ov5648_tuning.data

# Display
PRODUCT_PACKAGES += \
    gralloc.mrvl \
    hwcomposer.mrvl \
    memtrack.mrvl

# Input Device Config
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/idc/Synaptics_HID_TouchPad.idc:system/usr/idc/Synaptics_HID_TouchPad.idc \
    $(LOCAL_PATH)/idc/elan-ts.idc:system/usr/idc/elan-ts.idc \
    $(LOCAL_PATH)/idc/ft5306-ts.idc:system/usr/idc/ft5306-ts.idc \
    $(LOCAL_PATH)/idc/msg2133.idc:system/usr/idc/msg2133.idc \
    $(LOCAL_PATH)/idc/synaptics_dsx_i2c.idc:system/usr/idc/synaptics_dsx_i2c.idc

# Keylayouts
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/keylayout/sec_touchscreen.kl:system/usr/keylayout/sec_touchscreen.kl

# Keystore
PRODUCT_PACKAGES += \
    keystore.mrvl

# Lights
PRODUCT_PACKAGES += \
    lights.mrvl

# Media
PRODUCT_COPY_FILES += \
    frameworks/av/media/libstagefright/data/media_codecs_google_audio.xml:system/etc/media_codecs_google_audio.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_telephony.xml:system/etc/media_codecs_google_telephony.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_video.xml:system/etc/media_codecs_google_video.xml \
    $(LOCAL_PATH)/configs/media/media_codecs.xml:system/etc/media_codecs.xml \
    $(LOCAL_PATH)/configs/media/somxreg.conf:system/etc/somxreg.conf

# OMX
PRODUCT_PACKAGES += \
    libstagefright_soft_h264dec \
    libstagefright_soft_h264enc \
#    libstagefrighthw \
    libMrvlOmx \

# Shims
PRODUCT_PACKAGES += \
    libui_shim \
    libutils_shim

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.audio.low_latency.xml:system/etc/permissions/android.hardware.audio.low_latency.xml \
    frameworks/native/data/etc/android.hardware.bluetooth.xml:system/etc/permissions/android.hardware.bluetooth.xml \
    frameworks/native/data/etc/android.hardware.bluetooth_le.xml:system/etc/permissions/android.hardware.bluetooth_le.xml \
    frameworks/native/data/etc/android.hardware.camera.autofocus.xml:system/etc/permissions/android.hardware.camera.autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:system/etc/permissions/android.hardware.camera.flash-autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.front.xml:system/etc/permissions/android.hardware.camera.front.xml \
    frameworks/native/data/etc/android.hardware.camera.xml:system/etc/permissions/android.hardware.camera.xml \
    frameworks/native/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
    frameworks/native/data/etc/android.hardware.sensor.accelerometer.xml:system/etc/permissions/android.hardware.sensor.accelerometer.xml \
    frameworks/native/data/etc/android.hardware.sensor.compass.xml:system/etc/permissions/android.hardware.sensor.compass.xml \
    frameworks/native/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/native/data/etc/android.hardware.telephony.cdma.xml:system/etc/permissions/android.hardware.telephony.cdma.xml \
    frameworks/native/data/etc/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml \
    frameworks/native/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml \
    frameworks/native/data/etc/android.hardware.usb.host.xml:system/etc/permissions/android.hardware.usb.host.xml \
    frameworks/native/data/etc/android.hardware.wifi.direct.xml:system/etc/permissions/android.hardware.wifi.direct.xml \
    frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
    frameworks/native/data/etc/android.software.sip.voip.xml:system/etc/permissions/android.software.sip.voip.xml \
    frameworks/native/data/etc/android.hardware.nfc.hce.xml:system/etc/permissions/android.hardware.nfc.hce.xml \
    frameworks/native/data/etc/android.hardware.nfc.xml:system/etc/permissions/android.hardware.nfc.xml \
    frameworks/native/data/etc/android.software.webview.xml:system/etc/permissions/android.software.webview.xml \
    frameworks/native/data/etc/handheld_core_hardware.xml:system/etc/permissions/handheld_core_hardware.xml

# Power
PRODUCT_PACKAGES += \
    power.mrvl

# GPS
PRODUCT_PACKAGES += \
    gps.mrvl

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/gps/gps.conf:system/etc/gps.conf \
    $(LOCAL_PATH)/configs/gps/gnss_ulc1.bin:system/etc/gnss_ulc1.bin \
    $(LOCAL_PATH)/configs/gps/mrvl_gps_platform.conf:system/etc/mrvl_gps_platform.conf \
    $(LOCAL_PATH)/configs/gps/mrvl_agps_default.conf:system/etc/mrvl_agps_default.conf \
    $(LOCAL_PATH)/configs/gps/pxa_testcfg.ini:system/etc/pxa_testcfg.ini

# Bluetooth
PRODUCT_PACKAGES += \
    bluetooth.default \
    libbt-vendor

# Wifi
PRODUCT_PACKAGES += \
    MarvellWirelessDaemon \
    hostapd \
    wpa_supplicant \
    wpa_supplicant.conf

# Bluetooth & Wifi Firmware
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/firmware/ispfw_v325.bin:system/etc/firmware/ispfw_v325.bin \
    $(LOCAL_PATH)/configs/firmware/mrvl/SDIO8777_SDIO_SDIO.bin:system/etc/firmware/mrvl/SDIO8777_SDIO_SDIO.bin \
    $(LOCAL_PATH)/configs/firmware/mrvl/WlanCalData_ext.conf:system/etc/firmware/mrvl/WlanCalData_ext.conf \
    $(LOCAL_PATH)/configs/firmware/mrvl/bt_cal_data.conf:system/etc/firmware/mrvl/bt_cal_data.conf \
    $(LOCAL_PATH)/configs/firmware/mrvl/bt_init_cfg.conf:system/etc/firmware/mrvl/bt_init_cfg.conf \
    $(LOCAL_PATH)/configs/firmware/mrvl/reg_alpha2:system/etc/firmware/mrvl/reg_alpha2 \
    $(LOCAL_PATH)/configs/firmware/mrvl/sd8777_uapsta.bin:system/etc/firmware/mrvl/sd8777_uapsta.bin \
    $(LOCAL_PATH)/configs/firmware/mrvl/txbackoff.txt:system/etc/firmware/mrvl/txbackoff.txt \
    $(LOCAL_PATH)/configs/firmware/mrvl/txpower_FC.bin:system/etc/firmware/mrvl/txpower_FC.bin \
    $(LOCAL_PATH)/configs/firmware/mrvl/txpwrlimit_cfg.bin:system/etc/firmware/mrvl/txpwrlimit_cfg.bin

# RIL
PRODUCT_PACKAGES += \
    $(LOCAL_PATH)/configs/ril/plmn_se13.bin:system/etc/plmn_se13.bin

# XML
PRODUCT_PACKAGES += \
    libxml2

# Ramdisk
PRODUCT_PACKAGES += \
    init.pxa1908.rc \
    init.pxa1908.usb.rc \
    init.pxa1908.tel.rc \
    init.pxa1908.security.rc \
    init.pxa1908.sensor.rc \
    init.recovery.pxa1908.rc \
    ueventd.pxa1908.rc

PRODUCT_PACKAGES += \
    libgpucsc \

# NFC
#PRODUCT_PACKAGES += \
    Nfc-nci \
    Tag \

# FMRadio
PRODUCT_PACKAGES += \
    FMRadio \
    libfmjni \
    libfmhal \
    libMarvellWireless \

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/fm/mrvlfm-amon.cfg:system/etc/mrvlfm-amon.cfg \
    $(LOCAL_PATH)/configs/fm/mrvlfm-horus.cfg:system/etc/mrvlfm-horus.cfg \

#PRODUCT_PACKAGES += \
    Snap

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/egl/gfx.cfg:system/etc/gfx.cfg

# Inherit from mrvl-common
$(call inherit-product, device/samsung/mrvl-common/mrvl-common.mk)
