#include "CCProfileEventDispatcher.h"
#include "CCDomainFactory.h"
#include "CCDomainHelper.h"
#include "CCSoomlaEventDispatcher.h"

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

        if (!CCAbstractAggregatedEventHandler::init()) {
            return false;
        }
        
        CCSoomlaEventDispatcher *eventDispatcher = CCSoomlaEventDispatcher::getInstance();

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
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLoginFailed(errorDescription);
        }
    }

    void CCProfileEventDispatcher::onLoginFinished(CCUserProfile *userProfile) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLoginFinished(userProfile);
        }
    }

    void CCProfileEventDispatcher::onLoginStarted(cocos2d::__String *provider) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLoginStarted(provider);
        }
    }

    void CCProfileEventDispatcher::onLogoutFailed(cocos2d::__String *errorDescription) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLogoutFailed(errorDescription);
        }
    }

    void CCProfileEventDispatcher::onLogoutFinished(CCUserProfile *userProfile) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLogoutFinished(userProfile);
        }
    }

    void CCProfileEventDispatcher::onLogoutStarted(cocos2d::__String *provider) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLogoutStarted(provider);
        }
    }

    void CCProfileEventDispatcher::onGetContactsFailed(cocos2d::__String *socialActionType, cocos2d::__String *errorDescription) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetContactsFailed(socialActionType, errorDescription);
        }
    }

    void CCProfileEventDispatcher::onGetContactsFinished(cocos2d::__String *socialActionType, cocos2d::__Array *contactsDict) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetContactsFinished(socialActionType, contactsDict);
        }
    }

    void CCProfileEventDispatcher::onGetContactsStarted(cocos2d::__String *socialActionType) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onGetContactsStarted(socialActionType);
        }
    }

    void CCProfileEventDispatcher::onSocialActionFailedEvent(cocos2d::__String *socialActionType, cocos2d::__String *errorDescription) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onSocialActionFailedEvent(socialActionType, errorDescription);
        }
    }

    void CCProfileEventDispatcher::onSocialActionFinishedEvent(cocos2d::__String *socialActionType) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onSocialActionFinishedEvent(socialActionType);
        }
    }

    void CCProfileEventDispatcher::onSocialActionStartedEvent(cocos2d::__String *socialActionType) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onSocialActionStartedEvent(socialActionType);
        }
    }

    void CCProfileEventDispatcher::onLoginCancelledEvent() {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onLoginCancelledEvent();
        }
    }

    void CCProfileEventDispatcher::onRewardGivenEvent(CCReward *reward) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onRewardGivenEvent(reward);
        }
    }

    void CCProfileEventDispatcher::onUserProfileUpdatedEvent(CCUserProfile *userProfile) {
        FOR_EACH_EVENT_HANDLER(CCProfileEventHandler)
            eventHandler->onUserProfileUpdatedEvent(userProfile);
        }
    }

}
