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

TARGET_BOARD_PLATFORM := mrvl
TARGET_BOARD_PLATFORM_GPU := vivante-gc700
TARGET_SOC := pxa1908

TARGET_CUSTOM_DTBTOOL := dtbToolpxa1908

# Init
TARGET_INIT_VENDOR_LIB := libinit_pxa1908
TARGET_UNIFIED_DEVICE := true

# Malloc
MALLOC_SVELTE := true

#TARGET_SPECIFIC_HEADER_PATH := $(COMMON_PATH)/include
# CMHW
#BOARD_HARDWARE_CLASS += $(COMMON_PATH)/cmhw

# Custom RIL class
#BOARD_RIL_CLASS := ../../../$(COMMON_PATH)/ril

# Fonts
#EXTENDED_FONT_FOOTPRINT := true

# Properties (reset them here, include more in device if needed)
#TARGET_SYSTEM_PROP := $(COMMON_PATH)/system.prop

# SELinux
#-include device/qcom/sepolicy/sepolicy.mk
#BOARD_SEPOLICY_DIRS += $(COMMON_PATH)/sepolicy
