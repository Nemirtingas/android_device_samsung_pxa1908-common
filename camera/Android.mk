# Copyright (C) 2012 The Android Open Source Project
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

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := camera.mrvl
LOCAL_MODULE_RELATIVE_PATH := hw

LOCAL_C_INCLUDES += \
	system/core/include \
	system/media/camera/include \
    framework/av/include \

LOCAL_SRC_FILES := \
    CameraHAL.cpp \
    stockcamera.cpp \

LOCAL_SHARED_LIBRARIES := \
	libcamera_metadata \
	libcutils \
	liblog \
	libsync \
	libutils \
	libmvmem

LOCAL_STATIC_LIBRARIES := libcamera_parameters

LOCAL_CFLAGS += -Wall -Wextra -fvisibility=hidden

LOCAL_MODULE_TAGS := optional

LOCAL_ADDITIONAL_DEPENDENCIES := \
    $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/camera.stock.so \

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := camera.stock.so
LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)/include

LOCAL_MODULE := camera.stock
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_TAG := optional
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_PRELINK_MODULE := false

include $(BUILD_PREBUILT)
