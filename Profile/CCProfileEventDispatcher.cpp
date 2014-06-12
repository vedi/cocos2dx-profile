#include "CCProfileEventDispatcher.h"
#include "CCDomainFactory.h"
#include "CCDomainHelper.h"

namespace soomla {

    USING_NS_CC;

    static CCProfileEventDispatcher *s_SharedInstance = NULL;

    CCProfileEventDispatcher *CCProfileEventDispatcher::getInstance() {
        if (!s_SharedInstance) {
            s_SharedInstance = new CCProfileEventDispatcher();
        }

        return s_SharedInstance;
    }

    CCProfileEventDispatcher::~CCProfileEventDispatcher() {
    }

	void CCProfileEventDispatcher::addEventHandler(CCProfileEventHandler *eventHandler) {
		mEventHandlers.addObject(eventHandler);
        eventHandler->retain();
	}

	void CCProfileEventDispatcher::removeEventHandler(CCProfileEventHandler *eventHandler) {
		mEventHandlers.removeObject(eventHandler);
        eventHandler->release();
	}

    void CCProfileEventDispatcher::ndkCallBack(__Dictionary *parameters) {
        __String *eventName = dynamic_cast<__String *>(parameters->objectForKey("event"));
        CC_ASSERT(eventName);
        if (eventName->compare("com.soomla.profile.events.auth.LoginCancelledEvent") == 0) {
            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onLoginCancelledEvent();
            }
        }
        else if (eventName->compare("com.soomla.profile.events.auth.LoginFailedEvent") == 0) {
            __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
			__SetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
				h->onLoginFailed(errorDescription);
			}
        }
        else if (eventName->compare("com.soomla.profile.events.auth.LoginFinishedEvent") == 0) {
            CCUserProfile *userProfile = this->extractUserProfile(parameters->objectForKey("userProfile"));
            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onLoginFinished(userProfile);
            }
        }
        else if (eventName->compare("com.soomla.profile.events.auth.LoginStartedEvent") == 0) {
            __String *provider = dynamic_cast<__String *>(parameters->objectForKey("provider"));
            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onLoginStarted(provider);
            }
        }
        else if (eventName->compare("com.soomla.profile.events.auth.LogoutFailedEvent") == 0) {
            __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onLogoutFailed(errorDescription);
            }
        }
        else if (eventName->compare("com.soomla.profile.events.auth.LogoutFinishedEvent") == 0) {
            CCUserProfile *userProfile = this->extractUserProfile(parameters->objectForKey("userProfile"));
            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onLogoutFinished(userProfile);
            }
        }
        else if (eventName->compare("com.soomla.profile.events.auth.LogoutStartedEvent") == 0) {
            __String *provider = dynamic_cast<__String *>(parameters->objectForKey("provider"));
            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onLogoutStarted(provider);
            }
        }
        else if (eventName->compare("com.soomla.profile.events.social.GetContactsFailedEvent") == 0) {
            __String *socialActionType = dynamic_cast<__String *>(parameters->objectForKey("socialActionType"));
            __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onGetContactsFailed(socialActionType, errorDescription);
            }
        }
        else if (eventName->compare("com.soomla.profile.events.social.GetContactsFinishedEvent") == 0) {
            __String *socialActionType = dynamic_cast<__String *>(parameters->objectForKey("socialActionType"));
            __Array *contacts = this->extractUserProfileArray(parameters->objectForKey("contacts"));

            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onGetContactsFinished(socialActionType, contacts);
            }
        }
        else if (eventName->compare("com.soomla.profile.events.social.GetContactsStartedEvent") == 0) {
            __String *socialActionType = dynamic_cast<__String *>(parameters->objectForKey("socialActionType"));
            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onGetContactsStarted(socialActionType);
            }
        }
        else if (eventName->compare("com.soomla.profile.events.social.SocialActionFailedEvent") == 0) {
            __String *socialActionType = dynamic_cast<__String *>(parameters->objectForKey("socialActionType"));
            __String *errorDescription = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onSocialActionFailedEvent(socialActionType, errorDescription);
            }
        }
        else if (eventName->compare("com.soomla.profile.events.social.SocialActionFinishedEvent") == 0) {
            __String *socialActionType = dynamic_cast<__String *>(parameters->objectForKey("socialActionType"));
            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onSocialActionFinishedEvent(socialActionType);
            }
        }
        else if (eventName->compare("com.soomla.profile.events.social.SocialActionStartedEvent") == 0) {
            __String *socialActionType = dynamic_cast<__String *>(parameters->objectForKey("socialActionType"));
            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onSocialActionStartedEvent(socialActionType);
            }
        }
        else if (eventName->compare("com.soomla.profile.events.RewardGivenEvent") == 0) {
            __Dictionary *rewardDict = dynamic_cast<__Dictionary *>(parameters->objectForKey("reward"));
            CC_ASSERT(rewardDict);
            CCReward *reward  = dynamic_cast<CCReward *>(CCDomainFactory::getInstance()->createWithDictionary(rewardDict));
            CC_ASSERT(reward);
            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onRewardGivenEvent(reward);
            }
        }
        else if (eventName->compare("com.soomla.profile.events.UserProfileUpdatedEvent") == 0) {
            CCUserProfile *userProfile = this->extractUserProfile(parameters->objectForKey("userProfile"));
            __SetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCProfileEventHandler *h = dynamic_cast<CCProfileEventHandler *>(*i);
                h->onUserProfileUpdatedEvent(userProfile);
            }
        }
		else {
            CC_ASSERT(false);
        }
    }

    CCUserProfile *CCProfileEventDispatcher::extractUserProfile(Ref *userProfileRef) {
        __Dictionary *userProfileDict = dynamic_cast<__Dictionary *>(userProfileRef);
        CC_ASSERT(userProfileDict);
        CCUserProfile *userProfile = dynamic_cast<CCUserProfile *>(
                CCDomainFactory::getInstance()->createWithDictionaryAndType(userProfileDict, JSON_JSON_TYPE_USER_PROFILE));
        CC_ASSERT(userProfile);
        return userProfile;
    }

    __Array *CCProfileEventDispatcher::extractUserProfileArray(Ref *userProfileDictArray) {
        __Array *contactsDict = dynamic_cast<__Array *>(userProfileDictArray);
        CC_ASSERT(contactsDict);
        return CCDomainHelper::getInstance()->getDomainsFromDictArray(contactsDict, JSON_JSON_TYPE_USER_PROFILE);
    }
}
