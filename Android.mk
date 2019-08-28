LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-format
LOCAL_MODULE    := gpioIrq 
LOCAL_SRC_FILES := gpioIrq.c

include $(BUILD_EXECUTABLE)
