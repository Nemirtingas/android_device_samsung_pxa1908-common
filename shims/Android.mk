LOCAL_PATH:= $(call my-dir)

#include $(CLEAR_VARS)

#LOCAL_SRC_FILES := uishim.cpp
#LOCAL_SHARED_LIBRARIES := libui
#LOCAL_MODULE := libui_shim
#LOCAL_MODULE_TAGS := optional

#include $(BUILD_SHARED_LIBRARY)

#include $(CLEAR_VARS)

#LOCAL_SRC_FILES := utilsshim.cpp
#LOCAL_SHARED_LIBRARIES := libutils
#LOCAL_MODULE := libutils_shim
#LOCAL_MODULE_TAGS := optional

#include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := system/media/audio_utils/include
LOCAL_SRC_FILES := modded_audioutils.cpp
LOCAL_SHARED_LIBRARIES := libutils libdl liblog
LOCAL_MODULE := libmodaudiout
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
