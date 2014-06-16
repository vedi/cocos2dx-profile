//
// Created by Fedor Shubin on 5/20/13.
//

#include "CCProfileService.h"
#include "CCNdkBridge.h"
#include "CCDomainFactory.h"
#include "CCBadgeReward.h"
#include "CCRandomReward.h"
#include "CCSequenceReward.h"
#include "CCVirtualItemReward.h"
#include "CCProfileController.h"

using namespace cocos2d;
typedef DictElement CCDictElement;

namespace soomla {
    #define TAG "SOOMLA StoreController"

    USING_NS_CC;

    static CCProfileService *sInstance = NULL;

    CCProfileService *CCProfileService::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCProfileService();
            sInstance->retain();
        }
        return sInstance;
    }

    void CCProfileService::initShared(__Dictionary *profileParams) {
        CCProfileService *profileService = CCProfileService::getInstance();
        if (!profileService->init(profileParams)) {
            exit(1);
        }
    }

    CCProfileService::CCProfileService() {
    }

    bool CCProfileService::init(__Dictionary *profileParams) {

        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileService::init"), "method");
        params->setObject(profileParams, "params");
        CCNdkBridge::callNative(params, nullptr);

        CCDomainFactory::getInstance()->registerCreator(CCProfileConsts::JSON_JSON_TYPE_BADGE,
                (TDomainCreator) &CCBadgeReward::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCProfileConsts::JSON_JSON_TYPE_RANDOM,
                (TDomainCreator) &CCRandomReward::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCProfileConsts::JSON_JSON_TYPE_SEQUENCE,
                (TDomainCreator) &CCSequenceReward::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCProfileConsts::JSON_JSON_TYPE_ITEM,
                (TDomainCreator) &CCVirtualItemReward::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCProfileConsts::JSON_JSON_TYPE_USER_PROFILE,
                (TDomainCreator) &CCUserProfile::createWithDictionary);

        return CCProfileController::getInstance()->init();
    }
}
