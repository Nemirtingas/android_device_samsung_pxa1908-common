ifneq ($(filter pxa1908,$(TARGET_BOARD_SOC)),)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := libion liblog
LOCAL_C_INCLUDES       := hardware/marvell/pxa1908/original-kernel-headers system/core/libion/include
LOCAL_SRC_FILES := mvmem.cpp
LOCAL_MODULE    := libmvmem
LOCAL_MODULE_TAGS := optional
LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)

include $(BUILD_SHARED_LIBRARY)

endif
