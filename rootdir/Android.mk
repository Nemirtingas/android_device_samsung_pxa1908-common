LOCAL_PATH:= $(call my-dir)

# Configuration scripts

#include $(CLEAR_VARS)
#LOCAL_MODULE       := init.qcom.bt.sh
#LOCAL_MODULE_TAGS  := optional eng
#LOCAL_MODULE_CLASS := ETC
#LOCAL_SRC_FILES    := etc/init.qcom.bt.sh
#include $(BUILD_PREBUILT)

# Init scripts

#include $(CLEAR_VARS)
#LOCAL_MODULE       := init.qcom.rc
#LOCAL_MODULE_TAGS  := optional eng
#LOCAL_MODULE_CLASS := ETC
#LOCAL_SRC_FILES    := init.qcom.rc
#LOCAL_MODULE_PATH  := $(TARGET_ROOT_OUT)
#include $(BUILD_PREBUILT)

#include $(CLEAR_VARS)
#LOCAL_MODULE       := ueventd.pxa1908.rc
#LOCAL_MODULE_TAGS  := optional eng
#LOCAL_MODULE_CLASS := ETC
#LOCAL_SRC_FILES    := ueventd.pxa1908.rc
#LOCAL_MODULE_PATH  := $(TARGET_ROOT_OUT)
#include $(BUILD_PREBUILT)
