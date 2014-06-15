/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "CCUserProfile.h"
#include "CCReward.h"

#ifndef __CCProfileEventHandler__
#define __CCProfileEventHandler__

namespace soomla {
    class CCProfileEventHandler : public cocos2d::Ref {
    public:
        virtual void onLoginFailed(cocos2d::__String *errorDescription) = 0;
        virtual void onLoginFinished(CCUserProfile *userProfile) = 0;
        virtual void onLoginStarted(cocos2d::__String *provider) = 0;
        virtual void onLogoutFailed(cocos2d::__String *errorDescription) = 0;
        virtual void onLogoutFinished(CCUserProfile *userProfile) = 0;
        virtual void onLogoutStarted(cocos2d::__String *provider) = 0;
        virtual void onGetContactsFailed(cocos2d::__String *socialActionType, cocos2d::__String *errorDescription) = 0;
        virtual void onGetContactsFinished(cocos2d::__String *socialActionType, cocos2d::__Array *contactsDict) = 0;
        virtual void onGetContactsStarted(cocos2d::__String *socialActionType) = 0;
        virtual void onSocialActionFailedEvent(cocos2d::__String *socialActionType, cocos2d::__String *errorDescription) = 0;
        virtual void onSocialActionFinishedEvent(cocos2d::__String *socialActionType) = 0;
        virtual void onSocialActionStartedEvent(cocos2d::__String *socialActionType) = 0;
        virtual void onLoginCancelledEvent() = 0;
        virtual void onRewardGivenEvent(CCReward *reward) = 0;
        virtual void onUserProfileUpdatedEvent(CCUserProfile *userProfile) = 0;
    };

};

#endif /* defined(__CCProfileEventHandler__) */
