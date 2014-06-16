#include "CCProfileEventDispatcher.h"
#include "CCDomainFactory.h"
#include "CCDomainHelper.h"
#include "CCEventDispatcher.h"

namespace soomla {

    USING_NS_CC;

    static CCProfileEventDispatcher *s_SharedInstance = NULL;

    CCProfileEventDispatcher *CCProfileEventDispatcher::getInstance() {
        if (!s_SharedInstance) {
            s_SharedInstance = new CCProfileEventDispatcher();
            s_SharedInstance->init();
        }

        return s_SharedInstance;
    }

    bool CCProfileEventDispatcher::init() {
        
        mEventHandlers = __Set::create();
        mEventHandlers->retain();
        
        CCEventDispatcher *eventDispatcher = CCEventDispatcher::getInstance();

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_CANCELLED,
                [this](__Dictionary *) {
                    this->onLoginCancelledEvent();
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_FAILED,
                [this](__Dictionary *parameters) {
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    this->onLoginFailed(errorDescription);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_FINISHED,
                [this](__Dictionary *parameters) {
                    CCUserProfile *userProfile = this->extractUserProfile(parameters->objectForKey("userProfile"));
                    this->onLoginFinished(userProfile);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGIN_STARTED,
                [this](__Dictionary *parameters) {
                    __String *provider = dynamic_cast<__String *>(parameters->objectForKey("provider"));
                    this->onLoginStarted(provider);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGOUT_FAILED,
                [this](__Dictionary *parameters) {
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    this->onLogoutFailed(errorDescription);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGOUT_FINISHED,
                [this](__Dictionary *parameters) {
                    CCUserProfile *userProfile = this->extractUserProfile(parameters->objectForKey("userProfile"));
                    this->onLogoutFinished(userProfile);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_LOGOUT_STARTED,
                [this](__Dictionary *parameters) {
                    __String *provider = dynamic_cast<__String *>(parameters->objectForKey("provider"));
                    this->onLogoutStarted(provider);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_CONTACTS_FAILED,
                [this](__Dictionary *parameters) {
                    __String *socialActionType = dynamic_cast<__String *>(parameters->objectForKey("socialActionType"));
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    this->onGetContactsFailed(socialActionType, errorDescription);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_CONTACTS_FINISHED,
                [this](__Dictionary *parameters) {
                    __String *socialActionType = dynamic_cast<__String *>(parameters->objectForKey("socialActionType"));
                    __Array *contacts = this->extractUserProfileArray(parameters->objectForKey("contacts"));
                    this->onGetContactsFinished(socialActionType, contacts);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_GET_CONTACTS_STARTED,
                [this](__Dictionary *parameters) {
                    __String *socialActionType = dynamic_cast<__String *>(parameters->objectForKey("socialActionType"));
                    this->onGetContactsStarted(socialActionType);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_SOCIAL_ACTION_FAILED,
                [this](__Dictionary *parameters) {
                    __String *socialActionType = dynamic_cast<__String *>(parameters->objectForKey("socialActionType"));
                    __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
                    this->onSocialActionFailedEvent(socialActionType, errorDescription);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_SOCIAL_ACTION_FINISHED,
                [this](__Dictionary *parameters) {
                    __String *socialActionType = dynamic_cast<__String *>(parameters->objectForKey("socialActionType"));
                    this->onSocialActionFinishedEvent(socialActionType);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_SOCIAL_ACTION_STARTED,
                [this](__Dictionary *parameters) {
                    __String *socialActionType = dynamic_cast<__String *>(parameters->objectForKey("socialActionType"));
                    this->onSocialActionStartedEvent(socialActionType);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_REWARD_GIVEN,
                [this](__Dictionary *parameters) {
                    __Dictionary *rewardDict = dynamic_cast<__Dictionary *>(parameters->objectForKey("reward"));
                    CC_ASSERT(rewardDict);
                    CCReward *reward  = dynamic_cast<CCReward *>(CCDomainFactory::getInstance()->createWithDictionary(rewardDict));
                    CC_ASSERT(reward);
                    this->onRewardGivenEvent(reward);
                });

        eventDispatcher->registerEventHandler(CCProfileConsts::EVENT_USER_PROFILE_UPDATED,
                [this](__Dictionary *parameters) {
                    CCUserProfile *userProfile = this->extractUserProfile(parameters->objectForKey("userProfile"));
                    this->onUserProfileUpdatedEvent(userProfile);
                });

        return true;
    }

    CCProfileEventDispatcher::~CCProfileEventDispatcher() {
        CC_SAFE_RELEASE(mEventHandlers);
    }

	void CCProfileEventDispatcher::addEventHandler(CCProfileEventHandler *eventHandler) {
		mEventHandlers->addObject(eventHandler);
	}

	void CCProfileEventDispatcher::removeEventHandler(CCProfileEventHandler *eventHandler) {
		mEventHandlers->removeObject(eventHandler);
	}

    CCUserProfile *CCProfileEventDispatcher::extractUserProfile(Ref *userProfileRef) {
        __Dictionary *userProfileDict = dynamic_cast<__Dictionary *>(userProfileRef);
        CC_ASSERT(userProfileDict);
        CCUserProfile *userProfile = dynamic_cast<CCUserProfile *>(
                CCDomainFactory::getInstance()->createWithDictionaryAndType(userProfileDict, CCProfileConsts::JSON_JSON_TYPE_USER_PROFILE));
        CC_ASSERT(userProfile);
        return userProfile;
    }

    __Array *CCProfileEventDispatcher::extractUserProfileArray(Ref *userProfileDictArray) {
        __Array *contactsDict = dynamic_cast<__Array *>(userProfileDictArray);
        CC_ASSERT(contactsDict);
        return CCDomainHelper::getInstance()->getDomainsFromDictArray(contactsDict, CCProfileConsts::JSON_JSON_TYPE_USER_PROFILE);
    }

    void CCProfileEventDispatcher::onLoginFailed(cocos2d::__String *errorDescription) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onLoginFailed(errorDescription);
        }
    }

    void CCProfileEventDispatcher::onLoginFinished(CCUserProfile *userProfile) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onLoginFinished(userProfile);
        }
    }

    void CCProfileEventDispatcher::onLoginStarted(cocos2d::__String *provider) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onLoginStarted(provider);
        }
    }

    void CCProfileEventDispatcher::onLogoutFailed(cocos2d::__String *errorDescription) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onLogoutFailed(errorDescription);
        }
    }

    void CCProfileEventDispatcher::onLogoutFinished(CCUserProfile *userProfile) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onLogoutFinished(userProfile);
        }
    }

    void CCProfileEventDispatcher::onLogoutStarted(cocos2d::__String *provider) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onLogoutStarted(provider);
        }
    }

    void CCProfileEventDispatcher::onGetContactsFailed(cocos2d::__String *socialActionType, cocos2d::__String *errorDescription) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onGetContactsFailed(socialActionType, errorDescription);
        }
    }

    void CCProfileEventDispatcher::onGetContactsFinished(cocos2d::__String *socialActionType, cocos2d::__Array *contactsDict) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onGetContactsFinished(socialActionType, contactsDict);
        }
    }

    void CCProfileEventDispatcher::onGetContactsStarted(cocos2d::__String *socialActionType) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onGetContactsStarted(socialActionType);
        }
    }

    void CCProfileEventDispatcher::onSocialActionFailedEvent(cocos2d::__String *socialActionType, cocos2d::__String *errorDescription) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onSocialActionFailedEvent(socialActionType, errorDescription);
        }
    }

    void CCProfileEventDispatcher::onSocialActionFinishedEvent(cocos2d::__String *socialActionType) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onSocialActionFinishedEvent(socialActionType);
        }
    }

    void CCProfileEventDispatcher::onSocialActionStartedEvent(cocos2d::__String *socialActionType) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onSocialActionStartedEvent(socialActionType);
        }
    }

    void CCProfileEventDispatcher::onLoginCancelledEvent() {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onLoginCancelledEvent();
        }
    }

    void CCProfileEventDispatcher::onRewardGivenEvent(CCReward *reward) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onRewardGivenEvent(reward);
        }
    }

    void CCProfileEventDispatcher::onUserProfileUpdatedEvent(CCUserProfile *userProfile) {
        __SetIterator i;
        for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {
            CCProfileEventHandler *eventHandler = dynamic_cast<CCProfileEventHandler *>(*i);
            eventHandler->onUserProfileUpdatedEvent(userProfile);
        }
    }
}
