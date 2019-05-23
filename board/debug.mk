# default gpu pixel format RGBA888

# debug opengl calls: frameworks/base/libs/hwui/Android.mk
#   default: false (HWUI_ENABLE_OPENGL_VALIDATION)
#TARGET_HWUI_ENABLE_OPENGL_VALIDATION := true

# frameworks/native/libs/ui/Android.mk
#   default: false
#BOARD_EGL_NEEDS_HANDLE_VALUE := true

# frameworks/native/opengl/libs/Android.mk
#   default: 1024
#MAX_EGL_CACHE_KEY_SIZE := 12*1024
#   default: (64 * 1024)
#MAX_EGL_CACHE_SIZE := 2048*1024

# frameworks/native/libs/gui/Android.mk
#   default: false (TARGET_BOARD_PLATFORM := tegra)
#TARGET_DONT_USE_FENCE_SYNC := true

# frameworks/rs/Android.mk
#RS_FIND_OFFSETS := true

# frameworks/native/services/surfaceflinger/Android.mk
#TARGET_USES_HWC2  := true
#TARGET_HAS_HH_VSYNC_ISSUE:=true
#TARGET_DISABLE_TRIPLE_BUFFERING:=true
#TARGET_RUNNING_WITHOUT_SYNC_FRAMEWORK:=true
#TARGET_FORCE_HWC_FOR_VIRTUAL_DISPLAYS:=true
#VSYNC_EVENT_PHASE_OFFSET_NS       := 50000
#SF_VSYNC_EVENT_PHASE_OFFSET_NS    := 500000
#PRESENT_TIME_OFFSET_FROM_VSYNC_NS := 1000000

# frameworks/av/media/libstagefright/Android.mk
#BOARD_CANT_REALLOCATE_OMX_BUFFERS:=true

#NUM_FRAMEBUFFER_SURFACE_BUFFERS := 3

#VSYNC_EVENT_PHASE_OFFSET_NS       := 0
#SF_VSYNC_EVENT_PHASE_OFFSET_NS    := 0
#PRESENT_TIME_OFFSET_FROM_VSYNC_NS := 0

#BOARD_HAVE_PIXEL_FORMAT_INFO := true
#BOARD_EGL_NEEDS_LEGACY_FB := true

#BOARD_WITH_HEADSET_OUTPUT_ONLY := true
