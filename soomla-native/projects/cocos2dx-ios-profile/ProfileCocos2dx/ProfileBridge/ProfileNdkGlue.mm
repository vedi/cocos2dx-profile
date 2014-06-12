//
// Created by Fedor Shubin on 5/24/13.
//

#import "ProfileNdkGlue.h"
#import "CCProfileNdkBridgeIos.h"
#include "jansson.h"
#import "Reward.h"
#import "DomainFactory.h"
#import "SoomlaProfile.h"
#import "UserProfile.h"
#import "UserProfileEventHandling.h"
#import "DomainHelper.h"
#import "ProfileEventHandlerBridge.h"
#import "StoreUtils.h"
#import "ProviderNotFoundException.h"
#import "UserProfileNotFoundException.h"
#import "ProfileService.h"

static ProfileEventHandlerBridge *eventDispatcherBridge = [ProfileEventHandlerBridge sharedInstance];

@implementation ProfileNdkGlue {
}

static NSString* TAG = @"SOOMLA ProfileNdkGlue";

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters {
    NSString *methodName = [parameters objectForKey:@"method"];

    NSMutableDictionary *retParameters = [NSMutableDictionary dictionary];

    @try {
        if ([methodName isEqualToString:@"CCProfileController::init"]) {
            [[ProfileService sharedProfileService] init];
        }
        else if ([methodName isEqualToString:@"CCProfileController::login"]) {
            NSString *provider = [parameters objectForKey:@"provider"];
            NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
            Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
            if (reward != nil) {
                [[SoomlaProfile getInstance] loginWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                     andReward:reward];
            } else {
                [[SoomlaProfile getInstance] loginWithProvider:[UserProfileUtils providerStringToEnum:provider]];
            }
        }
        else if ([methodName isEqualToString:@"CCProfileController::logout"]) {
            NSString *provider = [parameters objectForKey:@"provider"];
            [[SoomlaProfile getInstance] logoutWithProvider:[UserProfileUtils providerStringToEnum:provider]];
        }
        else if ([methodName isEqualToString:@"CCProfileController::getStoredUserProfile"]) {
            NSString *provider = [parameters objectForKey:@"provider"];
            UserProfile *userProfile = [[SoomlaProfile getInstance] getStoredUserProfileWithProvider:
                    [UserProfileUtils providerStringToEnum:provider]];
            if (userProfile != nil) {
                [retParameters setObject:[userProfile toDictionary] forKey:@"return"];
            }
        }
        else if ([methodName isEqualToString:@"CCProfileController::updateStatus"]) {
            NSString *provider = [parameters objectForKey:@"provider"];
            NSString *status = [parameters objectForKey:@"status"];
            NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
            Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
            [[SoomlaProfile getInstance] updateStatusWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                        andStatus:status
                                                        andReward:reward];
        }
        else if ([methodName isEqualToString:@"CCProfileController::updateStory"]) {
            NSString *provider = [parameters objectForKey:@"provider"];
            NSString *message = [parameters objectForKey:@"message"];
            NSString *name = [parameters objectForKey:@"name"];
            NSString *caption = [parameters objectForKey:@"caption"];
            NSString *description = [parameters objectForKey:@"description"];
            NSString *link = [parameters objectForKey:@"link"];
            NSString *picture = [parameters objectForKey:@"picture"];
            NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
            Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
            [[SoomlaProfile getInstance] updateStoryWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                      andMessage:message
                                                         andName:name
                                                      andCaption:caption
                                                  andDescription:description
                                                         andLink:link
                                                      andPicture:picture
                                                       andReward:reward];
        }
        else if ([methodName isEqualToString:@"CCProfileController::uploadImage"]) {
            NSString *provider = [parameters objectForKey:@"provider"];
            NSString *message = [parameters objectForKey:@"message"];
            NSString *filePath = [parameters objectForKey:@"filePath"];
            NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
            Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
            [[SoomlaProfile getInstance] uploadImageWithProvider:[UserProfileUtils providerStringToEnum:provider]
                                                      andMessage:message
                                                         andFilePath:filePath
                                                       andReward:reward];
        }
        else if ([methodName isEqualToString:@"CCProfileController::getContacts"]) {
            NSString *provider = [parameters objectForKey:@"provider"];
            [[SoomlaProfile getInstance] logoutWithProvider:[UserProfileUtils providerStringToEnum:provider]];
            NSDictionary *rewardDict = [parameters objectForKey:@"reward"];
            Reward *reward = rewardDict ? [[DomainFactory sharedDomainFactory] createWithDict:rewardDict] : nil;
            [[SoomlaProfile getInstance] getContactsWithProvider:[UserProfileUtils providerStringToEnum:provider] andReward:reward];
        }
        else {
            LogError(TAG, ([NSString stringWithFormat:@"Unsupported method %@", methodName]));
        }
    }
    @catch (ProviderNotFoundException* e) {
        [retParameters setObject: [NSNumber numberWithInt: -1] forKey: @"errorCode"];
    }
    @catch (UserProfileNotFoundException* e) {
        [retParameters setObject: [NSNumber numberWithInt: -2] forKey: @"errorCode"];
    }
    return retParameters;
}

+ (void)dispatchNDKCallback:(NSNotification*)notification {
    NSMutableDictionary *parameters = [NSMutableDictionary dictionary];
    if ([notification.name isEqualToString:EVENT_UP_LOGIN_CANCELLED]) {
        [parameters setObject:@"com.soomla.profile.events.auth.LoginCancelledEvent" forKey:@"method"];
    }
    else if ([notification.name isEqualToString:EVENT_UP_LOGIN_FAILED]) {
        [parameters setObject:@"com.soomla.profile.events.auth.LoginFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
    }
    else if ([notification.name isEqualToString:EVENT_UP_LOGIN_FINISHED]) {
        [parameters setObject:@"com.soomla.profile.events.auth.LoginFinishedEvent" forKey:@"method"];
        id userProfile = [notification.userInfo objectForKey:DICT_ELEMENT_USER_PROFILE];
        [parameters setObject:[userProfile toDictionary] forKey:@"userProfile"];
    }
    else if ([notification.name isEqualToString:EVENT_UP_LOGIN_STARTED]) {
        [parameters setObject:@"com.soomla.profile.events.auth.LoginStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
    }
    else if ([notification.name isEqualToString:EVENT_UP_LOGOUT_FAILED]) {
        [parameters setObject:@"com.soomla.profile.events.auth.LogoutFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
    }
    else if ([notification.name isEqualToString:EVENT_UP_LOGOUT_FINISHED]) {
        [parameters setObject:@"com.soomla.profile.events.auth.LogoutFinishedEvent" forKey:@"method"];
        id userProfile = [notification.userInfo objectForKey:DICT_ELEMENT_USER_PROFILE];
        [parameters setObject:[userProfile toDictionary] forKey:@"userProfile"];
    }
    else if ([notification.name isEqualToString:EVENT_UP_LOGOUT_STARTED]) {
        [parameters setObject:@"com.soomla.profile.events.auth.LogoutStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_PROVIDER] forKey:@"provider"];
    }
    else if ([notification.name isEqualToString:EVENT_UP_GET_CONTACTS_FAILED]) {
        [parameters setObject:@"com.soomla.profile.events.social.GetContactsFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
    }
    else if ([notification.name isEqualToString:EVENT_UP_GET_CONTACTS_FINISHED]) {
        [parameters setObject:@"com.soomla.profile.events.social.GetContactsFinishedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        id contacts = [notification.userInfo objectForKey:DICT_ELEMENT_CONTACTS];
        [parameters setObject:[[DomainHelper sharedDomainHelper] getDictListFromDomains:contacts] forKey:@"contacts"];
    }
    else if ([notification.name isEqualToString:EVENT_UP_GET_CONTACTS_STARTED]) {
        [parameters setObject:@"com.soomla.profile.events.social.GetContactsStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
    }
    else if ([notification.name isEqualToString:EVENT_UP_SOCIAL_ACTION_FAILED]) {
        [parameters setObject:@"com.soomla.profile.events.social.GetContactsFailedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_MESSAGE] forKey:@"errorDescription"];
    }
    else if ([notification.name isEqualToString:EVENT_UP_SOCIAL_ACTION_FINISHED]) {
        [parameters setObject:@"com.soomla.profile.events.social.SocialActionFinishedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
    }
    else if ([notification.name isEqualToString:EVENT_UP_SOCIAL_ACTION_STARTED]) {
        [parameters setObject:@"com.soomla.profile.events.social.SocialActionStartedEvent" forKey:@"method"];
        [parameters setObject:[notification.userInfo objectForKey:DICT_ELEMENT_SOCIAL_ACTION_TYPE] forKey:@"socialActionType"];
    }
    else if ([notification.name isEqualToString:EVENT_BP_REWARD_GIVEN]) {
        [parameters setObject:@"com.soomla.profile.events.RewardGivenEvent" forKey:@"method"];
        Reward *reward = [notification.userInfo objectForKey:DICT_ELEMENT_REWARD];
        [parameters setObject:[reward toDictionary] forKey:@"reward"];
    }
    else if ([notification.name isEqualToString:EVENT_UP_USER_PROFILE_UPDATED]) {
        [parameters setObject:@"com.soomla.profile.events.UserProfileUpdatedEvent" forKey:@"method"];
        UserProfile *userProfile = [notification.userInfo objectForKey:DICT_ELEMENT_USER_PROFILE];
        [parameters setObject:[userProfile toDictionary] forKey:@"userProfile"];
    }
    else {
        LogError(TAG, ([NSString stringWithFormat:@"Unknown notification %@", notification.name]));
        return;
    }

    json_t *jsonPrms = NULL;

    if (parameters != nil) {
        NSError *error = nil;
        NSData *jsonData = [NSJSONSerialization
                dataWithJSONObject:parameters
                           options:NSJSONWritingPrettyPrinted
                             error:&error];

        if (error != nil)
            return;

        NSString *jsonPrmsString = [[NSString alloc] initWithData:jsonData
                                                         encoding:NSUTF8StringEncoding];

        json_error_t jerror;
        jsonPrms = json_loads([jsonPrmsString UTF8String], 0, &jerror);

        if (!jsonPrms) {
            fprintf(stderr, "error: at line #%d: %s\n", jerror.line, jerror.text);
            return;
        }

        [jsonPrmsString release];
    }

    soomla::CCProfileNdkBridgeIos::ndkCallback(jsonPrms);
    if (jsonPrms) {
        json_decref(jsonPrms);
    }
}

@end
