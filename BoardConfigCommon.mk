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

# RIL
BOARD_PROVIDES_LIBRIL := true
ANDROID_MULTI_SIM := true
ANDROID_SIM_COUNT_2 := true

# Board specific headers
TARGET_SPECIFIC_HEADER_PATH := $(COMMON_PATH)/include

BOARD_PROVIDES_MKBOOTIMG := true
BOARD_MKBOOTIMG_MRVL := true

BOARD_PROVIDES_MKIMAGE := true
BOARD_MKIMAGE_MRVL := true

BOARD_CUSTOM_BOOTIMG_MK := hardware/marvell/bootimage/mkbootimg.mk

BOARD_USE_MARVELL_ION := true

# CMHW
#BOARD_HARDWARE_CLASS += $(COMMON_PATH)/cmhw

# Custom RIL class
BOARD_RIL_CLASS := ../../../$(COMMON_PATH)/ril_class

# Fonts
EXTENDED_FONT_FOOTPRINT := true

# Init
TARGET_INIT_VENDOR_LIB := libinit_pxa1908
TARGET_UNIFIED_DEVICE := true

#BOARD_BUILD_SYSTEM_ROOT_IMAGE := true

BOARD_SEPOLICY_DIRS += $(COMMON_PATH)/sepolicy
-include device/marvell/sepolicy/sepolicy.mk
