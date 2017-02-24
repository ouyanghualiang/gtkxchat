# Copyright 2014 The GTK+Android Developers. See the COPYRIGHT
# file at the top-level directory of this distribution and at
# https://github.com/eugals/GTKAndroid/wiki/COPYRIGHT.
#
# Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
# http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
# <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
# option. This file may not be copied, modified, or distributed
# except according to those terms.
#
# Author(s): Evgeny Sologubov
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog
MY_COMMON_FILES := $(wildcard $(LOCAL_PATH)/common/*.c)
MY_COMMON_FILES := $(MY_COMMON_FILES:$(LOCAL_PATH)/%=%)

MY_GTK_FILES := $(wildcard $(LOCAL_PATH)/foo/*.c)
MY_GTK_FILES := $(MY_GTK_FILES:$(LOCAL_PATH)/%=%)


LOCAL_MODULE    := gtka_test
LOCAL_SRC_FILES := main.c\
		robot_main.c mysock.c\
		Provider.c #$(MY_COMMON_FILES) $(MT_GTK_FILES)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/common $(LOCAL_PATH)/fe-gtk $(LOCAL_PATH) $(LOCAL_PATH)/dirent $(LOCAL_PATH)/fe-text $(LOCAL_PATH)/htm $(LOCAL_PATH)/libenchant_win8 system/core/include/cutils
LOCAL_SHARED_LIBRARIES := libcutil

include $(LOCAL_PATH)/../../clibs/gtk/build-gtk-shared-library.mk

