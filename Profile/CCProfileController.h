//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCProfileController_H_
#define __CCProfileController_H_

#include "cocos2d.h"
#include "CCIStoreAssets.h"
#include "CCProfileError.h"
#include "CCReward.h"
#include "CCUserProfile.h"

namespace soomla {
	/** \class CCProfileController
		\brief An interface to the native StoreController class.

		An interface to the native StoreController class, use this class to
		access the native StoreController functionality.
	 */
    class CCProfileController: public cocos2d::Ref {
    public:
		/**
		   This class is singleton, use this function to access it.
		*/
        static CCProfileController* getInstance();

        static void initShared(cocos2d::__Dictionary *profileParams);

        CCProfileController();
        virtual ~CCProfileController();

        virtual bool init(cocos2d::__Dictionary *profileParams);

        void login(const char *provider, CCReward *reward, CCProfileError **soomlaError);

        void login(const char *provider, CCProfileError **soomlaError);

        void logout(const char *provider, CCProfileError **soomlaError);

        CCUserProfile *getStoredUserProfile(const char *provider, CCProfileError **soomlaError);

        void updateStatus(const char *provider, const char *status, CCReward *reward, CCProfileError **soomlaError);

        void updateStory(const char *provider, const char *message, const char *name, const char *caption,
                const char *description, const char *link, const char *picture,
                CCReward *reward, CCProfileError **soomlaError);

        void uploadImage(const char *provider, const char *message, const char *filePath,
                CCReward *reward, CCProfileError **soomlaError);

        void getContacts(const char *provider, CCReward *reward, CCProfileError **soomlaError);

    };
};

#endif // !__CCProfileController_H_
