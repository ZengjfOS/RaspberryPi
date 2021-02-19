LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := liblog
LOCAL_SRC_FILES := test/android_10/client.c binder.c
# LOCAL_CFLAGS += $(svc_c_flags)
LOCAL_CFLAGS += -Wno-unused-parameter -Wno-unused-variable
LOCAL_MODULE := bclient
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := liblog
LOCAL_SRC_FILES := test/android_10/service.c binder.c
# LOCAL_CFLAGS += $(svc_c_flags)
LOCAL_CFLAGS += -Wno-unused-parameter -Wno-unused-variable
LOCAL_MODULE := bservice
include $(BUILD_EXECUTABLE)

# # static link
# include $(CLEAR_VARS)
# LOCAL_STATIC_LIBRARIES := liblog
# LOCAL_SRC_FILES := android_10/client.c binder.c
# # LOCAL_CFLAGS += $(svc_c_flags)
# LOCAL_CFLAGS += -Wno-unused-parameter -Wno-unused-variable
# LOCAL_LDFLAGS += -static
# LOCAL_MODULE := bclient
# LOCAL_FORCE_STATIC_EXECUTABLE := true
# include $(BUILD_EXECUTABLE)
#
# include $(CLEAR_VARS)
# LOCAL_STATIC_LIBRARIES := liblog
# LOCAL_SRC_FILES := android_10/service.c binder.c
# # LOCAL_CFLAGS += $(svc_c_flags)
# LOCAL_CFLAGS += -Wno-unused-parameter -Wno-unused-variable
# LOCAL_LDFLAGS += -static
# LOCAL_MODULE := bservice
# LOCAL_FORCE_STATIC_EXECUTABLE := true
# include $(BUILD_EXECUTABLE)

