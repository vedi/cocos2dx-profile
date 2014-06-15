#ifndef __CCProfileEventDispatcher_H_
#define __CCProfileEventDispatcher_H_

#include "cocos2d.h"
#include "CCProfileEventHandler.h"

namespace soomla {

	/** \class CCProfileEventDispatcher
		\brief Calls event handler functions when events are fired, also contains settings for StoreController.

		This class calls event handler functions when events are fired, to tie
		it to your event handler call addEventHandler(). You also set parameters
		for StoreController through this class.
	 */
    class CCProfileEventDispatcher : public CCProfileEventHandler {
	private:
        cocos2d::__Set *mEventHandlers;
    public:
		/**
		   This class is singleton, access it with this function.
		 */
        static CCProfileEventDispatcher *getInstance();

        CCProfileEventDispatcher():
                mEventHandlers(NULL) {
        }
        bool init();

        virtual ~CCProfileEventDispatcher();

		/**
		   Add an event handler. This retains the event handler.
		   \param eventHandler A pointer to the event handler you'd like to add.
		 */
		void addEventHandler(CCProfileEventHandler *eventHandler);

		/**
		   Remove an event handler. This releases the event handler.
		   \param eventHandler A pointer to the event handler you'd like to remove.
		*/
		void removeEventHandler(CCProfileEventHandler *eventHandler);

        virtual void onLoginFailed(cocos2d::__String *errorDescription);

        virtual void onLoginFinished(CCUserProfile *userProfile);

        virtual void onLoginStarted(cocos2d::__String *provider);

        virtual void onLogoutFailed(cocos2d::__String *errorDescription);

        virtual void onLogoutFinished(CCUserProfile *userProfile);

        virtual void onLogoutStarted(cocos2d::__String *provider);

        virtual void onGetContactsFailed(cocos2d::__String *socialActionType, cocos2d::__String *errorDescription);

        virtual void onGetContactsFinished(cocos2d::__String *socialActionType, cocos2d::__Array *contactsDict);

        virtual void onGetContactsStarted(cocos2d::__String *socialActionType);

        virtual void onSocialActionFailedEvent(cocos2d::__String *socialActionType, cocos2d::__String *errorDescription);

        virtual void onSocialActionFinishedEvent(cocos2d::__String *socialActionType);

        virtual void onSocialActionStartedEvent(cocos2d::__String *socialActionType);

        virtual void onLoginCancelledEvent();

        virtual void onRewardGivenEvent(CCReward *reward);

        virtual void onUserProfileUpdatedEvent(CCUserProfile *userProfile);

    private:
        CCUserProfile *extractUserProfile(Ref *userProfileRef);
        cocos2d::__Array *extractUserProfileArray(Ref *userProfileDictArray);
    };
};

#endif //__CCProfileEventDispatcher_H_
