//  LQL1
//  Camera.h
//  IOTCamViewer
//
//  Created by Cloud Hsiao on 12/5/11.
//  Copyright (c) 2011 TUTK. All rights reserved.
//

#define CHANNEL_VIDEO_FPS 110
#define CHANNEL_VIDEO_BPS 111
#define CHANNEL_VIDEO_FRAMECOUNT 112
#define CHANNEL_VIDEO_INCOMPLETE_FRAMECOUNT 113
#define CHANNEL_VIDEO_ONLINENM 114

#define CONNECTION_MODE_NONE -1
#define CONNECTION_MODE_P2P 0
#define CONNECTION_MODE_RELAY 1
#define CONNECTION_MODE_LAN 2

/* used for display status */
#define CONNECTION_STATE_NONE 0
#define CONNECTION_STATE_CONNECTING 1
#define CONNECTION_STATE_CONNECTED 2
#define CONNECTION_STATE_DISCONNECTED 3
#define CONNECTION_STATE_UNKNOWN_DEVICE 4
#define CONNECTION_STATE_WRONG_PASSWORD 5
#define CONNECTION_STATE_TIMEOUT 6 //有时候start会返回连接超过AV最大数，如果不做处理，会一直回调，也返回连接超时
#define CONNECTION_STATE_UNSUPPORTED 7
#define CONNECTION_STATE_CONNECT_FAILED 8

#define RECV_VIDEO_BUFFER_SIZE  1920*1080*4//1280 * 720 * 4
#define RECV_AUDIO_BUFFER_SIZE  1280
#define RECV_AUDIO_BUFFER_SIZE2 1280*4

#define CONNECT_TIMEOUT_MSEC    20*1000;

#ifndef SUPPORT_15W
#define SUPPORT_15W
#endif


struct LAN_SEARCH
{
    char UID[21];
    char IP[17];
    unsigned short port;
    char DeviceName[24];
    char DevicePWD[24];
};
typedef struct LAN_SEARCH LanSearch_t;

LanSearch_t *SA(int *num, long x);

struct SUB_STREAM
{
    int index;
    int channel;
};
typedef struct SUB_STREAM SubStream_t;

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>

#import "AVFRAMEINFO.h"


/////汪总的设备，视频回放采用软解码，其余的设备回放和直播都是硬解！！！
//#ifndef WZ_DEVICE
//#define WZ_DEVICE
//#endif

@protocol CameraDelegate;

@interface Camera : NSObject {
}


#if defined(WZ_DEVICE)
///视频回放
@property (nonatomic, assign) BOOL playBack;;
#endif



@property (strong) NSString *name;
@property (strong, readonly) NSString *uid;
@property (readonly) NSInteger sessionID;
@property (readonly) NSInteger sessionMode;
@property (readonly) NSInteger sessionState;
@property (nonatomic, weak) id<CameraDelegate> delegate;

/*
 获取当前SDK版本号
 该SDK基于TUTK IOTCAPIs V3.1.10.9 版本进行优化处理
 在之前做的诸多优化没做版本记录，现在统一说明：
 1、优化频繁重连断开可能导致崩溃的问题
 2、优化双向语音开启后，关闭讲话时听筒没有声音的问题
 3、优化解码崩溃
 4、优化视频延迟的问题：关闭视频时清除视频缓存，该动作可能会导致清除其它IO与视频相关的命令，可在执行stopShow后延迟获取状态。之前考虑放在视频播放前startShow做清除视频缓存操作，不够理想，故放在停止视频播放时清除
 5、优化H265接收数据不完整导致花屏的问题
 6、H264统一采用硬解码
 7、H265统一采用软解码
 8、其它一些优化
 有其它问题请联系：vx  li15050162795
 
 基于以上修改后该SDK版本迭代详情记录
 3.3.0.1    |LiQiaolong   |2022-06-17  |版本1.0
 */
+ (NSString *)getMySDKVersion;

+ (void)initIOTC;
+ (void)uninitIOTC;
+ (NSString *)getIOTCAPIsVerion;
+ (NSString *)getAVAPIsVersion;
+ (LanSearch_t *)LanSearch:(int *)num;

- (id)initWithName:(NSString *)name;
- (void)connect:(NSString *)uid;
- (void)connect:(NSString *)uid AesKey:(NSString *)aesKey;
- (void)connect:(NSString *)uid timeOut:(NSInteger)connectTimeOutMillisecond;
- (void)connect2:(NSString *)uid;
- (void)connect2:(NSString *)uid timeOut:(NSInteger)connectTimeOutMillisecond;
- (void)disconnect;
- (void)start:(NSInteger)channel viewAccount:(NSString *)viewAccount viewPassword:(NSString *)viewPassword;
- (void)stop:(NSInteger)channel;
- (Boolean)isStarting:(NSInteger)channel;
- (void)startShow:(NSInteger)channel;

- (void)stopShow:(NSInteger)channel;
- (void)startSoundToPhone:(NSInteger)channel;
- (void)startSoundToPhoneForEcho:(NSInteger)channel;
- (void)startSoundToPhoneForOnlyRecv:(NSInteger)channel;
- (void)startSoundToPhoneForEchoForOnlyRecv:(NSInteger)channel;
- (void)stopSoundToPhone:(NSInteger)channel;
- (void)stopSoundToPhoneForOnlyRecv:(NSInteger)channel;
- (void)stopSoundToPhoneForEchoForOnlyRecv:(NSInteger)channel;
- (void)startSoundToDevice:(NSInteger)channel;
- (void)startSoundToDeviceForEcho:(NSInteger)channel;
- (void)stopSoundToDevice:(NSInteger)channel;
- (void)sendIOCtrlToChannel:(NSInteger)channel Type:(NSInteger)type Data:(char *)buff DataSize:(NSInteger)size;
- (void)sendIOCtrlDirectToChannel:(NSInteger)channel Type:(NSInteger)type Data:(char *)buff DataSize:(NSInteger)buffer_size;
- (void)sendIOCtrlSpeedToChannel:(NSInteger)channel Type:(NSInteger)type Data:(char *)buff DataSize:(NSInteger)buffer_size;
- (void)clearSendIOCtrlToChannel:(NSInteger)channel;
- (void)clearSendIOCtrlQueueToChannel:(NSInteger)channel;
- (void)clearSendIOCtrlSpeedQueueToChannel:(NSInteger)channel;
- (unsigned int)getChannel:(NSInteger)channel Snapshot:(char *)imgData dataSize:(unsigned long)size WithImageWidth:(unsigned int *)width ImageHeight:(unsigned int *)height;
- (unsigned int)getChannel:(NSInteger)channel Snapshot:(char *)imgData DataSize:(unsigned long)size ImageType:(unsigned int*)codec_id WithImageWidth:(unsigned int *)width ImageHeight:(unsigned int *)height;
- (CVPixelBufferRef)getChannelSnapshot:(NSInteger)channel ImageType:(unsigned int*)codec_id WithImageWidth:(unsigned int *)width ImageHeight:(unsigned int *)height;

- (NSString *)getViewAccountOfChannel:(NSInteger)channel;
- (NSString *)getViewPasswordOfChannel:(NSInteger)channel;
- (unsigned long)getServiceTypeOfChannel:(NSInteger)channel;
- (int)getConnectionStateOfChannel:(NSInteger)channel;
@end

@protocol CameraDelegate <NSObject>
@optional


- (void)camera:(Camera *)camera didReceiveJPEGDataFrame:(const char *)imgData DataSize:(NSInteger)size;
- (void)camera:(Camera *)camera didReceiveJPEGDataFrame2:(NSData *)imgData;
- (void)camera:(Camera *)camera didReceiveFrameInfoWithVideoWidth:(NSInteger)videoWidth VideoHeight:(NSInteger)videoHeight VideoFPS:(NSInteger)fps VideoBPS:(NSInteger)videoBps AudioBPS:(NSInteger)audioBps OnlineNm:(NSInteger)onlineNm FrameCount:(unsigned long)frameCount IncompleteFrameCount:(unsigned long)incompleteFrameCount;
- (void)camera:(Camera *)camera didChangeSessionStatus:(NSInteger)status;
- (void)camera:(Camera *)camera didChangeChannelStatus:(NSInteger)channel ChannelStatus:(NSInteger)status;
- (void)camera:(Camera *)camera didReceiveIOCtrlWithType:(NSInteger)type Data:(const char*)data DataSize:(NSInteger)size;

- (void)camera:(Camera *)camera didReceiveAudioBytesWithDataBuffer:(unsigned char *)dataBuffer withLength: (unsigned int)aLength;

/// 音频输入数据（讲话时会有回调）
/// @param camera camera
/// @param dataBuffer dataBuffer
/// @param codec codec
/// @param aLength aLength
- (void)camera:(Camera *)camera didReceiveInputAudioBytesWithCodec:(NSInteger)codec DataBuffer:(unsigned char *)dataBuffer withLength: (unsigned int)aLength;
/// 裸流视频数据
/// @param camera camera
/// @param dataBuffer dataBuffer
/// @param aLength aLength
- (void)camera:(Camera *)camera didReceiveVideoBytesWithDataBuffer:(unsigned char *)dataBuffer withLength:(unsigned int)aLength;

#ifdef ADD_TIMESTAMP
- (void)camera:(Camera *)camera didReceiveVideoBytesWithDataBuffer:(unsigned char *)dataBuffer withLength:(unsigned int)aLength withTimestamp:(unsigned long)timestamp;
#endif

/// 裸流视频数据
/// @param camera camera
/// @param dataBuffer dataBuffer
/// @param aLength aLength
/// @param codecID codecID
- (void)camera:(Camera *)camera didReceiveVideoBytesWithDataBuffer:(unsigned char *)dataBuffer withLength:(unsigned int)aLength videoCodecID:(NSInteger)codecID;

/// H264硬解码
/// @param camera camera
/// @param imageBufferRef imageBufferRef
- (void)camera:(Camera *)camera didReceiveVideoBytesWithHW264ImageBufferRef:(CVImageBufferRef)imageBufferRef;


///这两个方法已经失效，不再通过该代理回调视频数据
- (void)camera:(Camera *)camera didReceiveRawDataFrame:(const char *)imgData VideoWidth:(NSInteger)width VideoHeight:(NSInteger)height;
- (void)cameraHW:(Camera *)camera didReceiveRawDataFrame:(CVPixelBufferRef)imageBuffer VideoWidth:(NSInteger)width VideoHeight:(NSInteger)height;

@end


