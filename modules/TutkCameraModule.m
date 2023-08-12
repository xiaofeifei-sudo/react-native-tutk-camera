//
//  TutkCameraModule.m
//  react-native-tutk-camera
//
//  Created by NING on 2023/8/7.
//

#import <Foundation/Foundation.h>

#import "TutkCameraModule.h"
#import "TutkCameraViewManager.h"

@implementation TutkCameraModule

RCT_EXPORT_MODULE(TutkCameraModule)


RCT_EXPORT_METHOD(connectDevice){
    NSLog(@"连接设备");
}

@end
