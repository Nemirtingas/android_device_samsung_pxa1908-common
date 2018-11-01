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

PRODUCT_PACKAGES += \
    libOmxCore \
    libOmxVdec \
    libOmxVenc \
    libstagefrighthw

# Permissions
#PRODUCT_COPY_FILES += \
#    frameworks/native/data/etc/android.hardware.audio.low_latency.xml:system/etc/permissions/android.hardware.audio.low_latency.xml \
#    frameworks/native/data/etc/android.hardware.bluetooth.xml:system/etc/permissions/android.hardware.bluetooth.xml \
#    frameworks/native/data/etc/android.hardware.bluetooth_le.xml:system/etc/permissions/android.hardware.bluetooth_le.xml \
#    frameworks/native/data/etc/android.hardware.camera.autofocus.xml:system/etc/permissions/android.hardware.camera.autofocus.xml \
#    frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:system/etc/permissions/android.hardware.camera.flash-autofocus.xml \
#    frameworks/native/data/etc/android.hardware.camera.front.xml:system/etc/permissions/android.hardware.camera.front.xml \
#    frameworks/native/data/etc/android.hardware.camera.xml:system/etc/permissions/android.hardware.camera.xml \
#    frameworks/native/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
#    frameworks/native/data/etc/android.hardware.sensor.accelerometer.xml:system/etc/permissions/android.hardware.sensor.accelerometer.xml \
#    frameworks/native/data/etc/android.hardware.sensor.compass.xml:system/etc/permissions/android.hardware.sensor.compass.xml \
#    frameworks/native/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
#    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
#    frameworks/native/data/etc/android.hardware.telephony.cdma.xml:system/etc/permissions/android.hardware.telephony.cdma.xml \
#    frameworks/native/data/etc/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml \
#    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml \
#    frameworks/native/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml \
#    frameworks/native/data/etc/android.hardware.usb.host.xml:system/etc/permissions/android.hardware.usb.host.xml \
#    frameworks/native/data/etc/android.hardware.wifi.direct.xml:system/etc/permissions/android.hardware.wifi.direct.xml \
#    frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
#    frameworks/native/data/etc/android.software.sip.voip.xml:system/etc/permissions/android.software.sip.voip.xml \
#    frameworks/native/data/etc/handheld_core_hardware.xml:system/etc/permissions/handheld_core_hardware.xml

# Audio Configs
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/audio/audio_swvol_element.xml:system/etc/audio/audio_swvol_element.xml \
    $(LOCAL_PATH)/configs/audio/audio_basic_element_codec.xml:system/etc/audio_basic_element_codec.xml \
    $(LOCAL_PATH)/configs/audio/audio_basic_element_apu.xml:system/etc/audio_basic_element_apu.xml \
    $(LOCAL_PATH)/configs/audio/platform_audio_config.xml:system/etc/platform_audio_config.xml \
    $(LOCAL_PATH)/configs/audio/audio_virtualpath_config.xml:system/etc/audio_virtualpath_config.xml \
    $(LOCAL_PATH)/configs/audio/audio_path_config_apu.xml:system/etc/audio_path_config_apu.xml \
    $(LOCAL_PATH)/configs/audio/audio_path_config_codec.xml:system/etc/audio_path_config_codec.xml \
    $(LOCAL_PATH)/configs/audio/audio_gain_config.xml:system/etc/audio_gain_config.xml
    $(LOCAL_PATH)/configs/audio/media_codecs.xml:system/etc/media_codecs.xml \
    $(LOCAL_PATH)/configs/audio/media_codecs_google_audio.xml:system/etc/media_codecs_google_audio.xml \
    $(LOCAL_PATH)/configs/audio/media_codecs_google_telephony.xml:system/etc/media_codecs_google_telephony.xml \
    $(LOCAL_PATH)/configs/audio/media_codecs_google_video.xml:system/etc/media_codecs_google_video.xml

# GPS Configs
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/gps/mrvl_gps_platform.conf:system/etc/mrvl_gps_platform.conf \
    $(LOCAL_PATH)/configs/gps/pxa_testcfg.ini:system/etc/pxa_textcfg.ini

# Lights
PRODUCT_PACKAGES += \
    lights.$(TARGET_BOARD_PLATFORM)

# Power
PRODUCT_PACKAGES += \
    power.$(TARGET_BOARD_PLATFORM)

# Bluetooth
PRODUCT_PACKAGES += \
    libbt-vendor

# Wifi
PRODUCT_PACKAGES += \
    hostapd \
    wpa_supplicant

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/wifi/wpa_supplicant.conf:system/etc/wifi/wpa_supplicant.conf \
    $(LOCAL_PATH)/configs/wifi/p2p_supplicant_overlay.conf:system/etc/wifi/p2p_supplicant_overlay.conf \
    $(LOCAL_PATH)/configs/wifi/wpa_supplicant_overlay.conf:system/etc/wifi/wpa_supplicant_overlay.conf


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

# OMX
# XML
PRODUCT_PACKAGES += \
    libxml2

# Ramdisk
#PRODUCT_PACKAGES += \
#    init.pxa1908.bt.sh

PRODUCT_PACKAGES += \
    init.pxa1908.rc \
    init.pxa1908.usb.rc \
    init.pxa1908.tel.rc \
    init.pxa1908.security.rc \
    init.pxa1908.sensor.rc \
    ueventd.pxa1908.rc

# Torch
PRODUCT_PACKAGES += \
    Torch

# Marvell binaries
PRODUCT_PACKAGES += \
    MarvellWirelessDaemon \

PRODUCT_PACKAGES += libion

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/egl/gfx.cfg:system/etc/gfx.cfg

# Inherit from mrvl-common
$(call inherit-product, device/samsung/mrvl-common/mrvl-common.mk)
