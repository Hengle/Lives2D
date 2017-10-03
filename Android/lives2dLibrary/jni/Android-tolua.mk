# Copyright (C) 2009 The Android Open Source Project
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
#
LOCAL_PATH:= $(call my-dir)
JNI_PATH:=$(call my-dir)

# ProgmaBegin BuildLua
LUA_SRC_PATH:=../../../../Lives2D_Depends/lua-5.1.4/lua-5.1.4/src
include $(CLEAR_VARS)
LOCAL_PATH:=$(LUA_SRC_PATH)

LOCAL_MODULE    := libLua
LOCAL_SRC_FILES := lapi.c \
				lauxlib.c \
				lbaselib.c \
				lcode.c \
				ldblib.c \
				ldebug.c \
				ldo.c \
				ldump.c \
				lfunc.c \
				lgc.c \
				linit.c \
				liolib.c \
				llex.c \
				lmathlib.c \
				lmem.c \
				loadlib.c \
				lobject.c \
				lopcodes.c \
				loslib.c \
				lparser.c \
				lstate.c \
				lstring.c \
				lstrlib.c \
				ltable.c \
				ltablib.c \
				ltm.c \
				lua.c \
				luac.c \
				lundump.c \
				lvm.c \
				lzio.c \
				print.c \

include $(BUILD_STATIC_LIBRARY)

# ProgmaEnd

# ProgmaBegin BuildTOLUAPP

TOLUAPP_SRC_PATH:=../../../../Lives2D_Depends/toluapp-master/toluapp-master

include $(CLEAR_VARS)

LOCAL_PATH:=$(TOLUAPP_SRC_PATH)

LOCAL_MODULE    := libTOLUAPP

LOCAL_C_INCLUDES:= $(LUA_SRC_PATH) $(TOLUAPP_SRC_PATH)/include

LOCAL_SRC_FILES:=src/lib/tolua_event.c \
src/lib/tolua_is.c \
src/lib/tolua_map.c \
src/lib/tolua_push.c \
src/lib/tolua_to.c \

LOCAL_CPP_FEATURES:=rtti exceptions
#LOCAL_CFLAGS:=-O3 -fPIC

include $(BUILD_STATIC_LIBRARY)

# ProgmaEnd

include $(CLEAR_VARS)
LOCAL_PATH:= $(JNI_PATH)

LOCAL_MODULE    := liblives2d
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := AndroidGame.cpp
LOCAL_LDLIBS    := -llog -lGLESv2

LOCAL_C_INCLUDES:=$(LUA_SRC_PATH) $(TOLUAPP_SRC_PATH)/include
LOCAL_STATIC_LIBRARIES := libLua libTOLUAPP

include $(BUILD_SHARED_LIBRARY)