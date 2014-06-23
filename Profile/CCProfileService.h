//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCProfileService_H_
#define __CCProfileService_H_

#include "cocos2d.h"
#include "CCError.h"
#include "CCReward.h"
#include "CCUserProfile.h"

namespace soomla {

    class CCProfileService: public cocos2d::Ref {
    public:
		/**
		   This class is singleton, use this function to access it.
		*/
        static CCProfileService* getInstance();

        static void initShared(cocos2d::__Dictionary *profileParams);

        CCProfileService();

        virtual bool init(cocos2d::__Dictionary *profileParams);

    };
};

#endif // !__CCProfileController_H_
