//
//  Monitor.h
//  IOTCamViewer
//
//  Created by Cloud Hsiao on 1/18/12.
//  Copyright (c) 2012 TUTK. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Camera.h"

typedef enum 
{
    DirectionNone = 0,
    DirectionTiltUp = 1,
    DirectionTiltDown = 2,
    DirectionPanLeft = 3,
    DirectionPanRight = 4,
} Direction;

@protocol MonitorTouchDelegate;

@interface Monitor : UIImageView {}

@property (nonatomic, assign) IBOutlet id<MonitorTouchDelegate> delegate;

- (void)setMinimumGestureLength:(NSInteger)length MaximumVariance:(NSInteger)variance;
- (void)attachCamera:(Camera *)camera;
- (void)attachCamera:(Camera *)cam  isH264HWDecodeMode:(BOOL)isH264HW;
- (void)deattachCamera;

- (void)updateShowFrame;

@end

@protocol MonitorTouchDelegate <NSObject>
@optional
- (void)monitor:(Monitor *)monitor gestureSwiped:(Direction)direction;
- (void)monitor:(Monitor *)monitor gestureSwiped:(Direction)direction xLength:(CGFloat)deltaX yLength:(CGFloat)deltaY;
- (void)monitor:(Monitor *)monitor gesturePinched:(CGFloat)scale;
@end
