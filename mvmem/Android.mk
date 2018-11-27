ifneq ($(filter pxa1908,$(TARGET_BOARD_SOC)),)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := libion liblog
LOCAL_C_INCLUDES       := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include system/core/libion/include
LOCAL_ADDITIONAL_DEPENDENCIES += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr
LOCAL_SRC_FILES := mvmem.cpp
LOCAL_MODULE    := libmvmem
LOCAL_MODULE_TAGS := optional
LOCAL_EXPORT_C_INCLUDES := mvmem.h

include $(BUILD_SHARED_LIBRARY)

endif
