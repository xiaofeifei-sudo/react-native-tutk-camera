//
//  LZXAppDelegate.m
//  JKLocalRecorderDemo
//
//  Created by x on 13-7-25.
//  Copyright (c) 2013年 . All rights reserved.
//

#import "JKLocalRecorder.h"

#define recordFPS 1.0f/11.0f
#define frameBuffer 10
#define MainFrame [[UIScreen mainScreen] applicationFrame]
#define MainFrameLandscape CGRectMake(0.0f, 0.0f, MainFrame.size.height, MainFrame.size.width)

UInt32 framesAlreadyWritten = 0;

@interface JKLocalRecorder ()

-(void)readyInit;

@end

@implementation JKLocalRecorder

@synthesize directoryPath;
@synthesize startRecordFlag;

- (id)init
{
    if (self = [super init])
    {
        startRecordFlag = NO;
        isVideo = YES;
        [self readyInit];
    }
    return self;
}



- (void)startRecordImage:(UIImage *)img {
    [imageArr addObject:img];
}

-(void)startRecordRawAndAudio:(NSString *)fileName VideoWidth:(NSInteger)width VideoHeight:(NSInteger)height AudioSampleRate:(NSInteger)sampleRate AudioChannel:(NSInteger)channel AudioBitRate:(NSInteger)bitRate
{
    
    NSString *recordFileName = [NSString stringWithFormat:@"%@.mp4", fileName];
    NSString *recordPath = [self.directoryPath stringByAppendingPathComponent:recordFileName];
    
    if (self.startRecordFlag) {

    }
    
    self.startRecordFlag = YES;
    
    isVideo = YES;
    
    if([[NSFileManager defaultManager] fileExistsAtPath:recordPath])
    {
        //remove the old one
        [[NSFileManager defaultManager] removeItemAtPath:recordPath error:nil];
    }
    
    //for clearing all image
    [imageArr removeAllObjects];
    
    //for clearing all audio
    [audioArr removeAllObjects];
    
    if (isVideo == YES)
    {

        NSError *error = nil;
        
        unlink([recordPath UTF8String]);
        AVAssetWriter *videoWriter = [[AVAssetWriter alloc] initWithURL:[NSURL fileURLWithPath:recordPath] fileType:AVFileTypeQuickTimeMovie error:&error];

        NSParameterAssert(videoWriter);
        if(error) {

        }
        
        NSDictionary *videoSettings = [NSDictionary dictionaryWithObjectsAndKeys:AVVideoCodecH264, AVVideoCodecKey,
                                       [NSNumber numberWithInt:width], AVVideoWidthKey,
                                       [NSNumber numberWithInt:height], AVVideoHeightKey,
                                       [NSNumber numberWithInt:height], AVVideoHeightKey, nil];
        AVAssetWriterInput *writerInput = [AVAssetWriterInput assetWriterInputWithMediaType:AVMediaTypeVideo outputSettings:videoSettings];
        
        writerInput.transform = CGAffineTransformMakeRotation(M_PI/2.0);
        
        NSDictionary *sourcePixelBufferAttributesDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithInt:kCVPixelFormatType_32ARGB], kCVPixelBufferPixelFormatTypeKey, nil];
        
        AVAssetWriterInputPixelBufferAdaptor *adaptor = [AVAssetWriterInputPixelBufferAdaptor assetWriterInputPixelBufferAdaptorWithAssetWriterInput:writerInput sourcePixelBufferAttributes:sourcePixelBufferAttributesDictionary];
        
        // 解决APP进后台后重新打开后，录像时遇到 writerInput requestMediaDataWhenReadyOnQueue:dispatchQueue usingBlock:^ 重复调用问题
        writerInput.expectsMediaDataInRealTime = YES;
        
        NSParameterAssert(writerInput);
        NSParameterAssert([videoWriter canAddInput:writerInput]);
        
        if ([videoWriter canAddInput:writerInput]) {
 
        }else {

        }
        [videoWriter addInput:writerInput];
        
        // 音频设置
        NSDictionary *audioCompressionSettings = @{ AVFormatIDKey : @(kAudioFormatLinearPCM),
                                                    AVLinearPCMIsBigEndianKey : @(NO),
                                                    AVLinearPCMIsFloatKey : @(NO),
                                                    AVLinearPCMIsNonInterleaved : @(NO),
                                                    AVLinearPCMBitDepthKey : @(bitRate),
                                                    AVNumberOfChannelsKey : @(channel),
                                                    AVSampleRateKey : @(sampleRate) };

//            AVFormatIDKey : kAudioFormatLinearPCM,    // 音频格式
//            AVSampleRateKey : 8000.0,    // 采样率
//            AVNumberOfChannelsKey : 2,    // 通道数 1 || 2
//            AVChannelLayoutKey : Data.init(bytes: &channelLayout, count: MemoryLayout<AudioChannelLayout>.size),  // 声音效果（立体声）
//            AVLinearPCMBitDepthKey : 16,  // 音频的每个样点的位数
//            AVLinearPCMIsNonInterleaved : false,  // 音频采样是否非交错
//            AVLinearPCMIsFloatKey : false,    // 采样信号是否浮点数
//            AVLinearPCMIsBigEndianKey : false // 音频采用高位优先的记录格式

        AVAssetWriterInput *assetWriterAudioInput = [AVAssetWriterInput assetWriterInputWithMediaType:AVMediaTypeAudio outputSettings:audioCompressionSettings];
        NSParameterAssert(assetWriterAudioInput);
        NSParameterAssert([videoWriter canAddInput:assetWriterAudioInput]);
        if ([videoWriter canAddInput:assetWriterAudioInput]) {
       
        }else {
        }
        [videoWriter addInput:assetWriterAudioInput];
        [videoWriter startWriting];
        [videoWriter startSessionAtSourceTime:kCMTimeZero];
        
        dispatch_queue_t dispatchQueue = dispatch_queue_create("mediaInputQueue", NULL);
        int __block frame = 0;
        
        startTime = CFAbsoluteTimeGetCurrent();
        
        [writerInput requestMediaDataWhenReadyOnQueue:dispatchQueue usingBlock:^{

            
            CVPixelBufferRef buffer = NULL;
            while ([writerInput isReadyForMoreMediaData])
            {

                if([imageArr count] == 0 && isVideo == NO)
                {
                    isVideo = YES;
                    [writerInput markAsFinished];

                    // 需要结束音频写入
                    [assetWriterAudioInput markAsFinished];

                    [videoWriter finishWritingWithCompletionHandler:^{
                        [videoWriter release];

                    }];

                    if (buffer)
                    {
                        CFRelease(buffer);
                        buffer = NULL;
                    }
                
                    break;
                }
                
                if ([imageArr count] == 0 && isVideo == YES)
                {
                    //[self captureImage];
                }
                else
                {
                    
                    if (buffer==NULL)
                    {
                        UIImage *image = (UIImage *)[imageArr objectAtIndex:0];
                        if (image) {
                            CGImageRef cgImageRef = [image CGImage];
                            buffer = [self pixelBufferFromCGImage2:cgImageRef VideoWidth:width VideoHeight:height];
                        }
        
                    }
                    
                    if (buffer)
                    {
                        CFAbsoluteTime interval = (CFAbsoluteTimeGetCurrent() - startTime) * 1000;
                        CMTime currentSampleTime = CMTimeMake((int)interval, 1000);
                        
                        //if(![adaptor appendPixelBuffer:buffer withPresentationTime:CMTimeMake(frame, 25)])
                        if(![adaptor appendPixelBuffer:buffer withPresentationTime:currentSampleTime]){
                            
                        }else {
                            
                            ++frame;
                            
                            if (imageArr.count > 0) {

                                [imageArr removeObjectAtIndex:0];
                            }
                            
                            CFRelease(buffer);
                            buffer = NULL;

                        }
                    }
                    
                }
                
                usleep(10*1000);
            }
        }];

        
        dispatch_queue_t dispatchQueueAudio = dispatch_queue_create("mediaInputQueueAudio", NULL);

        [assetWriterAudioInput requestMediaDataWhenReadyOnQueue:dispatchQueueAudio usingBlock:^{

            CMSampleBufferRef audioBuffer = NULL;
            while ([assetWriterAudioInput isReadyForMoreMediaData])
            {

                if([audioArr count] == 0 && isVideo == NO)
                {
                    [assetWriterAudioInput markAsFinished];
          
                    if (audioBuffer)
                    {
                        CFRelease(audioBuffer);
                        audioBuffer = NULL;
                    }
                
                    break;
                }
                
                if ([audioArr count] == 0 && isVideo == YES)
                {
                    
                }
                else
                {
                    
                    if (audioBuffer==NULL)
                    {
                        NSData *audioData = (NSData *)[audioArr objectAtIndex:0];
                        
                        AudioStreamBasicDescription formatAudio;
                        formatAudio.mSampleRate = sampleRate;
                        formatAudio.mFormatID = kAudioFormatLinearPCM;
                        formatAudio.mFormatFlags = kLinearPCMFormatFlagIsPacked | kLinearPCMFormatFlagIsSignedInteger;
                        formatAudio.mBytesPerPacket = bitRate/8 *channel;
                        formatAudio.mFramesPerPacket = 1;
                        formatAudio.mBytesPerFrame = bitRate/8 *channel;
                        formatAudio.mChannelsPerFrame = channel;
                        formatAudio.mBitsPerChannel = bitRate;
                        formatAudio.mReserved = 0;

                        AudioBufferList audioBufferList;
                        audioBufferList.mNumberBuffers = 1;
                        audioBufferList.mBuffers[0].mNumberChannels = channel;
                        audioBufferList.mBuffers[0].mDataByteSize = (int)audioData.length;
                        audioBufferList.mBuffers[0].mData = (unsigned char *)[audioData bytes];
                        
                        AudioStreamBasicDescription asbd = formatAudio;
                        
                        static CMFormatDescriptionRef format = NULL;
                        
                        CMTime time = CMTimeMake(audioData.length/(bitRate/8) , sampleRate);
                        CMSampleTimingInfo timing = {CMTimeMake(1,sampleRate), time, kCMTimeInvalid };
                        
                        OSStatus error = 0;
                        if(format == NULL)
                            error = CMAudioFormatDescriptionCreate(kCFAllocatorDefault, &asbd, 0, NULL, 0, NULL, NULL, &format);
                        
                        error = CMSampleBufferCreate(kCFAllocatorDefault, NULL, false, NULL, NULL, format, audioData.length/((bitRate/8)*channel), 1, &timing, 0, NULL, &audioBuffer);
                        if ( error ) {
                            
                            break;
                        }
                        
                        error = CMSampleBufferSetDataBufferFromAudioBufferList(audioBuffer, kCFAllocatorDefault, kCFAllocatorDefault, 0, &audioBufferList);
                        if( error )
                        {
                          
                            break;
                        }
                        

                    }
                    
                    if (audioBuffer)
                    {
                        if ([assetWriterAudioInput isReadyForMoreMediaData]) {
                            if(![assetWriterAudioInput appendSampleBuffer:audioBuffer]){
                               
                            }else {
                                
                                
                                if (audioArr.count > 0) {
                                    [audioArr removeObjectAtIndex:0];
                                }
                                
                                CFRelease(audioBuffer);
                                audioBuffer = NULL;
                                
                            }
                        }

                    }
                    
                }
                usleep(10*1000);
            }
        }];

    }
}

- (void)setAudioData:(unsigned char *)data length:(int)length {
    
    [audioArr addObject:[NSData dataWithBytes:data length:length]];

}


-(CVPixelBufferRef)pixelBufferFromCGImage2:(CGImageRef)image VideoWidth:(NSInteger)width VideoHeight:(NSInteger)height
{
    CVPixelBufferRef pxbuffer = NULL;
    CVReturn status = CVPixelBufferCreate(kCFAllocatorDefault, width, height, kCVPixelFormatType_32ARGB, (CFDictionaryRef) options, &pxbuffer);
    
    NSParameterAssert(status == kCVReturnSuccess && pxbuffer != NULL);
    
    CVPixelBufferLockBaseAddress(pxbuffer, 0);
    void *pxdata = CVPixelBufferGetBaseAddress(pxbuffer);
    NSParameterAssert(pxdata != NULL);
    
    CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(pxdata, width, height, 8, 4*width, rgbColorSpace, kCGImageAlphaPremultipliedFirst);

    NSParameterAssert(context);

    CGContextDrawImage(context, CGRectMake(0, 0, CGImageGetWidth(image), CGImageGetHeight(image)), image);
    
    CGColorSpaceRelease(rgbColorSpace);
    CGContextRelease(context);
    CVPixelBufferUnlockBaseAddress(pxbuffer, 0);
    return pxbuffer;
}

-(void)stopRecord
{
    isVideo = NO;
}

-(void)readyInit
{
    imageArr = [[NSMutableArray alloc] init];
    audioArr = [[NSMutableArray alloc] init];

}

-(void)dealloc
{
    self.startRecordFlag = NO;
    [imageArr release];
    [audioArr release];
    [options release];
    [super dealloc];
}






@end
