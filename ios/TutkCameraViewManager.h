#import <React/RCTViewManager.h>
#import <Foundation/Foundation.h>

#import "JKCameraModel.h"
#import <React/RCTComponent.h>

#if __has_include(<React/RCTBridgeModule.h>)
#import <React/RCTBridgeModule.h>
#else
#import "RCTBridgeModule.h"
#endif


@class RCTBridge;

@interface TutkCameraViewManager : RCTViewManager <RCTBridgeModule,JKCameraModelDelegate>
    
#pragma mark - Data

+ (void)connectDevice;	


#pragma mark - Block


@end
