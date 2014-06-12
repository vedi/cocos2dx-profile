//
// Created by Fedor Shubin on 5/21/13.
//


#include "CCProfileError.h"

USING_NS_CC;

namespace soomla {
    #define JSON_ERROR_CODE "errorCode"

    #define TAG "CCProfileError"

    CCProfileError *CCProfileError::createWithObject(cocos2d::Ref *obj) {
        __Dictionary *dict = dynamic_cast<__Dictionary *>(obj);
        if (dict != NULL && dict->objectForKey(JSON_ERROR_CODE) != NULL) {
            __Integer *errorCode = dynamic_cast<__Integer *>(dict->objectForKey(JSON_ERROR_CODE));
            CC_ASSERT(errorCode);

            CCProfileError *ret = new CCProfileError();
            ret->autorelease();
            ret->init(errorCode->getValue());
            return ret;
        } else {
            return NULL;
        }
    }

    CCProfileError *CCProfileError::createProvideNotFoundException() {
        CCProfileError *ret = new CCProfileError();
        ret->autorelease();
        ret->init(SOOMLA_EXCEPTION_PROVIDER_NOT_FOUND_EXCEPTION);
        return ret;
    }

    CCProfileError *CCProfileError::createUserProfileNotFoundException() {
        CCProfileError *ret = new CCProfileError();
        ret->autorelease();
        ret->init(SOOMLA_EXCEPTION_USER_PROFILE_NOT_FOUND_EXCEPTION);
        return ret;
    }

    bool CCProfileError::init(int code) {
        mCode = code;

        if (code == SOOMLA_EXCEPTION_PROVIDER_NOT_FOUND_EXCEPTION) {
            cocos2d::log("%s %s", TAG, "SOOMLA/COCOS2DX Got ProvideNotFoundException exception");
            mInfo = "ProvideNotFoundException()";
        }
        else if (code == SOOMLA_EXCEPTION_USER_PROFILE_NOT_FOUND_EXCEPTION) {
            cocos2d::log("%s %s", TAG, "SOOMLA/COCOS2DX Got UserProfileNotFoundException exception");
            mInfo = "UserProfileNotFoundException()";
        }
        else {
            CC_ASSERT(false);
            return false;
        }

        return true;
    }
}
