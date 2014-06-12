//
// Created by Fedor Shubin on 5/20/13.
//

#include "CCProfileController.h"
#include "CCProfileNdkBridge.h"
#include "CCDomainFactory.h"
#include "CCBadgeReward.h"
#include "CCRandomReward.h"
#include "CCSequenceReward.h"
#include "CCVirtualItemReward.h"

using namespace cocos2d;
typedef DictElement CCDictElement;

namespace soomla {
    #define TAG "SOOMLA StoreController"

    USING_NS_CC;

    static CCProfileController *sInstance = NULL;

    CCProfileController *CCProfileController::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCProfileController();
            sInstance->retain();
        }
        return sInstance;
    }

    void CCProfileController::initShared(__Dictionary *profileParams) {
        CCProfileController *storeController = CCProfileController::getInstance();
        if (!storeController->init(profileParams)) {
            exit(1);
        }

        CCDomainFactory::getInstance()->registerCreator(JSON_JSON_TYPE_BADGE,
                (TDomainCreator) &CCBadgeReward::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(JSON_JSON_TYPE_RANDOM,
                (TDomainCreator) &CCRandomReward::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(JSON_JSON_TYPE_SEQUENCE,
                (TDomainCreator) &CCSequenceReward::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(JSON_JSON_TYPE_ITEM,
                (TDomainCreator) &CCVirtualItemReward::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(JSON_JSON_TYPE_USER_PROFILE,
                (TDomainCreator) &CCUserProfile::createWithDictionary);
    }

    CCProfileController::CCProfileController() {
    }

    CCProfileController::~CCProfileController() {

    }

    bool CCProfileController::init(__Dictionary *profileParams) {
        return true;
    }

    void CCProfileController::login(const char *provider, CCReward *reward, CCProfileError **soomlaError) {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::login"), "method");
        params->setObject(__String::create(provider), "provider");
        params->setObject(reward->toDictionary(), "reward");
        CCProfileNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::login(const char *provider, CCProfileError **soomlaError) {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::login"), "method");
        params->setObject(__String::create(provider), "provider");
        CCProfileNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::logout(const char *provider, CCProfileError **soomlaError) {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::logout"), "method");
        params->setObject(__String::create(provider), "provider");
        CCProfileNdkBridge::callNative(params, soomlaError);
    }

    CCUserProfile *CCProfileController::getStoredUserProfile(const char *provider, CCProfileError **soomlaError) {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::getStoredUserProfile"), "method");
        params->setObject(__String::create(provider), "provider");
        __Dictionary *retParams = (__Dictionary *) CCProfileNdkBridge::callNative(params, NULL);
        CCUserProfile *retValue = (CCUserProfile *) retParams->objectForKey("return");
        return retValue;
    }

    void CCProfileController::updateStatus(const char *provider, const char *status, CCReward *reward, CCProfileError **soomlaError) {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::updateStatus"), "method");
        params->setObject(__String::create(provider), "provider");
        params->setObject(__String::create(status), "status");
        params->setObject(reward->toDictionary(), "reward");
        CCProfileNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::updateStory(const char *provider, const char *message, const char *name,
            const char *caption, const char *description, const char *link, const char *picture,
            CCReward *reward, CCProfileError **soomlaError) {

        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::updateStory"), "method");
        params->setObject(__String::create(provider), "provider");
        params->setObject(__String::create(message), "message");
        params->setObject(__String::create(name), "name");
        params->setObject(__String::create(caption), "caption");
        params->setObject(__String::create(description), "description");
        params->setObject(__String::create(link), "link");
        params->setObject(__String::create(picture), "picture");
        params->setObject(reward->toDictionary(), "reward");
        CCProfileNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::uploadImage(const char *provider, const char *message, const char *filePath,
            CCReward *reward, CCProfileError **soomlaError) {

        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::uploadImage"), "method");
        params->setObject(__String::create(provider), "provider");
        params->setObject(__String::create(message), "message");
        params->setObject(__String::create(filePath), "filePath");
        params->setObject(reward->toDictionary(), "reward");
        CCProfileNdkBridge::callNative(params, soomlaError);
    }

    void CCProfileController::getContacts(const char *provider, CCReward *reward, CCProfileError **soomlaError) {

        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileController::getContacts"), "method");
        params->setObject(__String::create(provider), "provider");
        params->setObject(reward->toDictionary(), "reward");
        CCProfileNdkBridge::callNative(params, soomlaError);
    }
}
