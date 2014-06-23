//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCProfileController_H_
#define __CCProfileController_H_

#include "cocos2d.h"
#include "CCError.h"
#include "CCReward.h"
#include "CCUserProfile.h"

namespace soomla {
	/** \class CCProfileController
		\brief An interface to the native StoreController class.

		An interface to the native StoreController class, use this class to
		access the native StoreController functionality.
	 */
    class CCProfileController: public cocos2d::Ref {
    private:
        bool mInited;
    public:
		/**
		   This class is singleton, use this function to access it.
		*/
        static CCProfileController* getInstance();

        CCProfileController();
        virtual bool init();

        void login(const char *provider, CCReward *reward, CCError **soomlaError);

        void login(const char *provider, CCError **soomlaError);

        void logout(const char *provider, CCError **soomlaError);

        CCUserProfile *getStoredUserProfile(const char *provider, CCError **soomlaError);

        void updateStatus(const char *provider, const char *status, CCReward *reward, CCError **soomlaError);

        void updateStory(const char *provider, const char *message, const char *name, const char *caption,
                const char *description, const char *link, const char *picture,
                CCReward *reward, CCError **soomlaError);

        void uploadImage(const char *provider, const char *message, const char *filePath,
                CCReward *reward, CCError **soomlaError);

        void getContacts(const char *provider, CCReward *reward, CCError **soomlaError);

    };
};

#endif // !__CCProfileController_H_
