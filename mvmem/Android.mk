ifeq (0,1)
ifneq ($(filter pxa1908,$(TARGET_BOARD_SOC)),)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := libion liblog
LOCAL_C_INCLUDES       := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include system/core/libion
LOCAL_SRC_FILES := mvmem.c
LOCAL_MODULE:= libmvmem
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

endif
endif
