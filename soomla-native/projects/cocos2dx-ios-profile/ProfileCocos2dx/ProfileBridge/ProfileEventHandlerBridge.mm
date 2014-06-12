//
//  ProfileEventHandlerBridge.m
//  Trying
//
//  Created by Refael Dakar on 12/03/13.
//
//

#import "ProfileEventHandlerBridge.h"
#import "EventHandling.h"
#import "ProfileNdkGlue.h"

@implementation ProfileEventHandlerBridge

+ (ProfileEventHandlerBridge *)sharedInstance {
    static ProfileEventHandlerBridge * instance = nil;
    if (!instance) {
        instance = [[ProfileEventHandlerBridge alloc] init];
    }
    return instance;
}


- (id) init {
    if (self = [super init]) {
        [EventHandling observeAllEventsWithObserver:self withSelector:@selector(eventFired:)];
    }
    
    return self;
}

- (void)eventFired:(NSNotification*)notification{
    [ProfileNdkGlue dispatchNDKCallback:notification];
}


@end
