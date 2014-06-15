LOCAL_PATH := $(call my-dir)

# cocos2dx-store
include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_profile_static
LOCAL_MODULE_FILENAME := libcocos2dxprofile
LOCAL_SRC_FILES := ../../Profile/CCProfileController.cpp \
	../../Profile/CCProfileEventDispatcher.cpp \
  ../../Profile/CCProfileService.cpp \
	../../Profile/data/CCProfileJsonConsts.cpp \
	../../Profile/domain/CCUserProfile.cpp \
	../../Profile/domain/rewards/CCAggregateReward.cpp \
	../../Profile/domain/rewards/CCBadgeReward.cpp \
	../../Profile/domain/rewards/CCRandomReward.cpp \
	../../Profile/domain/rewards/CCReward.cpp \
	../../Profile/domain/rewards/CCSequenceReward.cpp \
	../../Profile/domain/rewards/CCVirtualItemReward.cpp \
	../../Soomla/CCDomainFactory.cpp \
	../../Soomla/CCDomainHelper.cpp \
  ../../Soomla/CCError.cpp \
	../../Soomla/CCEventDispatcher.cpp \
	../../Soomla/CCJsonHelper.cpp \
  ../../Soomla/CCNdkBridge.cpp \
	../../Soomla/data/CCCommonJsonConsts.cpp \
	../../Soomla/domain/CCDomain.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Profile
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Profile/data
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Profile/domain
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Profile/domain/rewards
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Soomla
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Soomla/data
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Soomla/domain

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += jansson_static


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../..
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/../../Profile
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/../../Profile/data
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/../../Profile/domain
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/../../Profile/domain/rewards
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/../../Soomla
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/../../Soomla/data
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/../../Soomla/domain

include $(BUILD_STATIC_LIBRARY)

$(call import-module,external/jansson)
