//
// Created by Fedor Shubin on 6/12/14.
//

#import "ProfileService.h"


@implementation ProfileService {

}

+ (id)sharedProfileService {
    static ProfileService *sharedProfileService = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedProfileService = [self alloc];
    });
    return sharedProfileService;
}

@end