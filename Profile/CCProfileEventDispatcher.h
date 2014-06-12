#ifndef __CCSoomla_H_
#define __CCSoomla_H_

#include "cocos2d.h"
#include "CCProfileEventHandler.h"

namespace soomla {

	/** \class CCProfileEventDispatcher
		\brief Calls event handler functions when events are fired, also contains settings for StoreController.

		This class calls event handler functions when events are fired, to tie
		it to your event handler call addEventHandler(). You also set parameters
		for StoreController through this class.
	 */
    class CCProfileEventDispatcher : public cocos2d::Ref {
	private:
        cocos2d::__Set mEventHandlers;
    public:
		/**
		   This class is singleton, access it with this function.
		 */
        static CCProfileEventDispatcher *getInstance();

        virtual ~CCProfileEventDispatcher();

		/**
		   Call an NDK function by name and parameters.
		   \param parameters A dictionary containing the function to call and parameters to pass to it.
		 */
        void ndkCallBack(cocos2d::__Dictionary *parameters);

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

    private:
        CCUserProfile *extractUserProfile(Ref *userProfileRef);
        cocos2d::__Array *extractUserProfileArray(Ref *userProfileDictArray);
    };
};

#endif //__CCSoomla_H_
