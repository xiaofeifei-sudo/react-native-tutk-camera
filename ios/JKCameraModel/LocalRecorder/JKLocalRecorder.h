//
//  LZXAppDelegate.m
//  JKLocalRecorderDemo
//
//  Created by x on 13-7-25.
//  Copyright (c) 2013年 . All rights reserved.
//
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

//#import "iToast.h"

@protocol JKLocalRecorderDelegate <NSObject>

-(void)recordRunning;
-(void)recordCompleted;
#if defined(LOCAL_SOURCE2)
- (void)recordCompleted2;
#endif

@end

@interface JKLocalRecorder : NSObject
{

    NSMutableArray *imageArr;

    BOOL isVideo;
    CFAbsoluteTime startTime;

    NSDictionary *options;
    NSMutableArray *audioArr;
}

@property (nonatomic, retain)NSString *directoryPath;

-(void)stopRecord;

@property (nonatomic, assign) BOOL startRecordFlag;


-(void)startRecordRawAndAudio:(NSString *)fileName VideoWidth:(NSInteger)width VideoHeight:(NSInteger)height AudioSampleRate:(NSInteger)sampleRate AudioChannel:(NSInteger)channel AudioBitRate:(NSInteger)bitRate;

- (void)setAudioData:(unsigned char *)data length:(int)length;

- (void)startRecordImage:(UIImage *)img;

@end

