//
//  JKCameraModel.h
//  demo
//
//  Created by mac on 2021/9/6.
//  Copyright © 2021 mac. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <IOTCamera/Camera.h>
#import <IOTCamera/Monitor.h>
#import <IOTCamera/AVFRAMEINFO.h>

#import <IOTCamera/IOTCWakeUp.h>
#import <IOTCamera/TUTKGlobalAPIs.h>
#import <IOTCamera/IOTCAPIs.h>
#import <IOTCamera/RDTAPIs.h>
#import <IOTCamera/AVAPIs.h>

#import <IOTCamera/AVIOCTRLDEFs.h>
#import "AVIOCTRLDEFuserdefineds.h"
#import "JKCameraModel.h"
#import "JKAudioModel.h"
#import "JKWiFiModel.h"
#import "JKFeedModel.h"

#import "JKEventModel.h"
#import "JKLocalRecorder.h"


#define MAX_SOUND_LIST_COUNT 3
#define INVALID_ALIAS_STR       @"invalid"
#define INVALID_ALIAS_STR2      @""

#define DONE        1
#define NOTDONE     0
#define START_STRING        "Start"
#define MAX_BUF_SIZE        1024
#define RDT_WAIT_TIMEMS        30000

#define MAX_IMG_BUFFER_SIZE    (1920*1080*4)

///空的话返回1，反之返回0
#define JUDGED(a) (a.length == 0||a == nil)?YES:NO


#define TTY_CMD_0XFF                0xFF
#define TTY_CMD_SET_FEED            0x01
#define TTY_CMD_GET_FEED            0x02
#define TTY_CMD_FOOD_LAST           0x03
#define TTY_CMD_FEED_OVER           0x07
#define TTY_CMD_FOOD_AVERAGE        0x08
#define TTY_CMD_CLEAR_DEV           0x0b
#define TTY_CMD_DO_FEED


#define DEFAULT_DEVICE_NAME     @"webcam"
#define DEFAULT_CAMERA_PASSWORD @"123456"

typedef enum : NSUInteger {
    ENCRYPTION_FORMAT_NONE,//未知视频编码格式
    ENCRYPTION_FORMAT_H265,//H265
    ENCRYPTION_FORMAT_H264,//H264
} ENCRYPTION_FORMAT;


typedef enum : NSUInteger {
    ONLINE,
    OFFLINE,
    CONNECTING,
} DEVICE_CONNECT_STATUS;


typedef struct
{
    char type;
    char content[127];
} RDTCommandStruct;

typedef enum
{
    RDT_FILE_TOTAL          = 0x00,
    RDT_FILE_NAME           = 0x01,
    RDT_FILE_SIZE           = 0x02,
    RDT_FILE_TIMES          = 0x03,
    RDT_FILE_START          = 0x04,
    RDT_FILE_STOP           = 0x05,
    RDT_START               = 0x06,
    RDT_STOP                = 0x07,
    RDT_NEXT_FILE           = 0x08,
} ENUM_RDT_COMMAND;

@class JKCameraModel;
@protocol JKCameraModelDelegate <NSObject>

/// 设备在线状态
/// @param cameraModel caneraModel
/// @param status 状态
- (void)JKCameraModel:(JKCameraModel *)cameraModel didChangeSessionStatus:(NSInteger)status;

/// 通道连接状态
/// @param cameraModel cameraModel
/// @param channel channel
/// @param status status
- (void)JKCameraModel:(JKCameraModel *)cameraModel didChangeChannelStatus:(NSInteger)channel ChannelStatus:(NSInteger)status;

/// 请求设备状态相关回调
/// @param cameraModel cameraModel
/// @param type 命令号
/// @param data data
/// @param size size
- (void)JKCameraModel:(JKCameraModel *)cameraModel didReceiveIOCtrlWithType:(NSInteger)type Data:(const char*)data DataSize:(NSInteger)size;

- (void)JKCameraModel:(JKCameraModel *)camera didReceiveFrameInfoWithVideoWidth:(NSInteger)videoWidth VideoHeight:(NSInteger)videoHeight VideoFPS:(NSInteger)fps VideoBPS:(NSInteger)videoBps AudioBPS:(NSInteger)audioBps OnlineNm:(NSInteger)onlineNm FrameCount:(unsigned long)frameCount IncompleteFrameCount:(unsigned long)incompleteFrameCount;

- (void)JKCameraModel:(JKCameraModel *)camera didReceiveRawDataFrame:(const char *)imgData VideoWidth:(NSInteger)width VideoHeight:(NSInteger)height;

- (void)JKCameraModel:(JKCameraModel *)camera didReceiveAudioBytesWithDataBuffer:(unsigned char *)dataBuffer withLength: (unsigned int)aLength;

- (void)JKCameraModel:(JKCameraModel *)camera didReceiveVideoBytesWithDataBuffer:(unsigned char *)dataBuffer withLength:(unsigned int)aLength;

- (void)JKCameraModel:(JKCameraModel *)camera didReceiveVideoBytesWithDataBuffer:(unsigned char *)dataBuffer withLength:(unsigned int)aLength withTimestamp:(unsigned long)timestamp;

/// 文件写入回调
/// @param cameraModel cameraModel
/// @param status YES 成功 NO失败
- (void)JKCameraModel:(JKCameraModel *)cameraModel fileWrittenSuccessfully:(BOOL)status;

/// 文件写入进度
/// @param cameraModel cameraModel
/// @param progress progress
- (void)JKCameraModel:(JKCameraModel *)cameraModel fileWritingProgress:(CGFloat)progress;

@end

@interface JKCameraModel : Camera {
    
    
    
}

@property (nonatomic,weak) id <JKCameraModelDelegate> cameraDelegate;

///移动侦测代理
@property (nonatomic,weak) id <JKCameraModelDelegate> detectDelegate;
///下标，用于刷新tableView
@property (nonatomic,assign) NSInteger index;
///是否分享 own代表自己的设备 shared代表分享的设备
@property (nonatomic,strong) NSString *authority;
///设备名称
@property (nonatomic,strong) NSString *deviceName;
///设备id
@property (nonatomic,strong) NSString *devid;
///设备密码
@property (nonatomic,strong) NSString *devPassword;
///通道
@property (nonatomic,assign) NSInteger lastChannel;
///密码错误
@property (nonatomic,assign) BOOL wrongPassword;
///推送开关
@property (nonatomic,assign) BOOL isPushMode;
///App在前台移动侦测安静模式&声音模式 YES声音模式
@property (nonatomic,assign) BOOL motionDetectionRingMode;
///消息事件计数器
@property (nonatomic,assign) int eventCount;
///设备类型
@property (nonatomic,strong) NSString *unitTypeStr;
@property (nonatomic,strong) NSMutableArray *arrayStreamChannel;
///支持流，这个协议没有拿到值时是无法视频播放
@property (nonatomic,assign) BOOL getSupportStream;
///音频格式，这个协议没有拿到值时是不能通话
@property (nonatomic,assign) BOOL getRecvAudioFormat;
///获取时区成功
@property (nonatomic,assign) BOOL getTimeZoneSuccessful;
///与零时区相差的秒数
@property (nonatomic,assign) NSInteger secondsnGMTDiff;
///获取视频质量成功
@property (assign, nonatomic) BOOL getCurrenQualitySuccessful;
///视频质量 1最高  5最低
@property (nonatomic,assign) NSInteger currenQuality;
///获取视频翻转成功
@property (assign, nonatomic) BOOL getMirroringSuccessful;
///视频翻转
@property (assign, nonatomic) NSInteger mirroring;
///夜视模式(开启、关闭、自动)
@property (assign, nonatomic) NSInteger irLedLevel;
///isAuto; // 如果是0 ，irLedLevel 有效。 如果是1，则是自动
@property (assign, nonatomic) NSInteger irLedAuto;
///获取指示灯开关成功
@property (assign, nonatomic) BOOL getPilotLampSuccessful;
///指示灯开关
@property (assign, nonatomic) NSInteger pilotLamp;
///获取推送地址
@property (assign, nonatomic) BOOL getPushAddressSuccessful;
@property (strong, nonatomic) NSString * pushIP;
@property (assign, nonatomic) NSInteger pushPort;
@property (strong, nonatomic) NSString *pushServer;
///设置推送地址
@property (assign, nonatomic) BOOL setPushAddressSuccessful;
///获取设备录音列表成功
@property (nonatomic,assign) BOOL getdeviceSoundListSuccessful;
///设备录音列表，视频款使用
@property (nonatomic,retain) NSMutableArray *soundList;
///获取设备所处城市成功
@property (nonatomic,assign) BOOL getdeviceCitySuccessful;
///设备录音列表，视频款使用
@property (nonatomic,retain) NSString *cityName;
///获取设备Alexa开关成功
@property (nonatomic,assign) BOOL getAlexaSuccessful;
///alexa开关 0关，1开
@property (nonatomic,assign) NSInteger alexaSwitch;
///获取设备犬吠侦测开关成功
@property (nonatomic,assign) BOOL getDogBarkingSuccessful;
///犬吠侦测开关 0关，1开
@property (nonatomic,assign) NSInteger dogBarkingSwitch;
///获取设备移动侦测灵明度成功
@property (nonatomic,assign) BOOL getLuminositySuccessful;
///移动侦测灵明度
@property (nonatomic,assign) NSInteger sensitivity;
///获取录像模式
@property (nonatomic,assign) BOOL getRecordModeSuccessful;
///录像模式
@property (nonatomic,assign) NSInteger recordMode;
///录像时常
@property (nonatomic,assign) short record_time_minite;
///设备信息 SD卡
@property (nonatomic,assign) BOOL getDeviceInfoSuccessful;
///SD卡总空间
@property (nonatomic,assign) NSInteger totalSize;
///SD卡剩余空间
@property (nonatomic,assign) NSInteger freeSize;
///设备连接的WiFi信息
@property (nonatomic,assign) BOOL getDeviceWiFiInfoSuccessful;
///连接的SSID
@property (nonatomic,strong) NSString *deviceWiFiSSID;
///连接的Password
@property (nonatomic,strong) NSString *deviceWiFiPassword;
///设备扫描到的wifi列表
@property (nonatomic,assign) BOOL getDeviceWiFiListSuccessful;
///wifi列表
@property (nonatomic,strong) NSMutableArray *wifiList;
///设备版本号
@property (nonatomic,assign) BOOL getDeviceVersionSuccessful;
///当前版本
@property (nonatomic,strong) NSString *currentVersion;
///最新版本
@property (nonatomic,strong) NSString *lastVersion;
///获取设备音量
@property (nonatomic,assign) BOOL getVolumeSuccessful;
///音量
@property (nonatomic,assign) NSInteger volumeValue;
///获取童锁状态成功
@property (nonatomic,assign) BOOL getChildrenLockSuccessful;
///获取童锁
@property (nonatomic,assign) NSInteger childrenLock;
///获取osd状态成功
@property (nonatomic,assign) BOOL getShowOSDSuccessful;
///显示osd
@property (nonatomic,assign) BOOL showOSD;
///获取设备选择的录音（T980支持自定义录音版本）
@property (nonatomic,assign) BOOL getRecordSuccessful;
///选择的录音下标
@property (nonatomic,assign) NSInteger recordIndex;
///D01逗狗机有如下属性
///获取设备能力值成功
@property (nonatomic,assign) BOOL getdeviceIdOrigSuccessful;
///产品编号,0-不确定产品类型。refrace ENUM_PRODUCT_TYPE_NUM
@property unsigned short abilityProductTypeNum;
///接下来ability_list数组的长度，长度是可变的，根据功能需要扩展
@property unsigned short abilityContentLength;
///能力值
@property unsigned int abilityList;
///获取设备喂食计划列表成功
@property (nonatomic,assign) BOOL getdeviceFeedListSuccessful;
///设备喂食计划列表
@property (nonatomic,retain) NSMutableArray *feedPlanList;
///渲染图层，只用将该控件添加到View上即可
@property (nonatomic,retain) Monitor *videoMonitor;
///解码方式
@property (assign, nonatomic) ENCRYPTION_FORMAT encryptionFormat;
/// 录像中
@property (assign, nonatomic) BOOL recording;
/// 监听中
@property (assign, nonatomic) BOOL listening;
/// 讲话中
@property (assign, nonatomic) BOOL talking;
/// 播放中
@property (assign, nonatomic) BOOL playing;
/// 是否支持双向开关
@property (assign, nonatomic) BOOL twoWayVoice;
/// 配网中，不用去获取状态
@property (assign, nonatomic) BOOL setNetWorking;

/// 初始化设备
/// @param name 设备名称
/// @param password 设备密码
- (instancetype)initWithName:(NSString *)name Password:(NSString *)password;

/// 设备连接
- (void)connectStatus;

/// 断开连接
- (void)myDisconnect;

/// 获取设备当前连接状态
- (NSInteger)getConnectStatus;

/// 开始连接默认通道
- (void)start;

/// 开始连接指定通道
/// @param channel channel(TF卡回放可以调用这个方法连接设备回放的通道)
- (void)start:(NSInteger)channel;

/// 获取设备状态，时区、经纬度、录音列表等
- (void)getDeviceStatus;
/// 开始显示视频
- (void)startShowWithChannel:(NSInteger)channel;
/// 停止显示视频
- (void)stopShowWithChannel:(NSInteger)channel;
/// 开始监听 >= 0 正常播放，-1:视频通道未连接，-2:系统媒体使用失败，请重试
- (int)startListen;
/// 停止监听
- (BOOL)stopListen;
/// 开始讲话 >= 0 正常播放，-1:视频通道未连接，-2:系统媒体使用失败，请重试
- (int)startTalk;
/// 停止讲话
- (BOOL)stopTalk;
/// 开始录像
/// @param filePath 文件路径
- (BOOL)startRecordWithPath:(NSString *)filePath;
/// 停止录像 返回文件名
- (NSString *)stopRecord;
/// 截图返回image
- (UIImage *)screenshot;
/// 写入音频
/// @param audioModel audioModel
/// @param path 文件路径
- (void)startWriteAudioFileWithModel:(JKAudioModel *)audioModel andFilePath:(NSString *)path;
/// 停止写入
- (void)stopWrite;

#pragma mark ===============发送相关协议的方法===============
/// 获取设备推送地址
- (void)getDevicePushAddress;
/// 获取设备时区
- (void)getDeviceTimeZone;
/// 获取移动侦测状态
- (void)getDeviceMotionDetect;
/// 获取设备TF录像模式
- (void)getDeviceTFRecordModel;
/// 获取设备TF信息（是否存在TF卡、卡容量）
- (void)getDeviceTFInfo;
/// 获取设备搜索到的wifi列表
- (void)getDeviceSearchWiFiList;
/// 获取设备当前连接的wifi信息
- (void)getDeviceCurrentConnectWiFiInfo;
/// 获取指示灯状态
- (void)getDeviceIndicatorLightStatus;
/// 获取夜视状态
- (void)getDeviceLedStatus;
/// 获取设备固件版本
- (void)getDeviceUpgrade;
/// 获取设备喂食计划列表
/// @param newMethod 新方法获取？
- (void)getDeviceFeedPlanListIsNewMethod:(BOOL)newMethod;
/// 获取设备城市
- (void)getDeviceCurrentCity;
/// 获取设备音频列表
- (void)getDeviceSoundList;
/// 获取视频质量
- (void)getDeviceVideoQuality;
/// 获取视频翻转情况
- (void)getDeviceVideoFlip;
/// 获取童锁状态
- (void)getDeviceChildrenLockStatus;
/// 获取OSD状态
- (void)getDeviceOSDStatus;
/// 获取信号强度
- (void)getDeviceWiFiSignal;
/// 设置设备推送
/// @param pushIP ip地址
/// @param pushPort 端口号
/// @param pushServer 服务器地址
- (void)sendPushAddressWithIP:(NSString *)pushIP PushPort:(NSString *)pushPort PushServer:(NSString *)pushServer;

/// 设置wifi
/// @param ssid ssid
/// @param password password
- (void)sendWiFiInfoWithSSID:(NSString *)ssid Password:(NSString *)password;

/// 设置设备连接密码
/// @param newPwd 新设置的密码
/// @param oldPwd 旧密码
- (void)sendConnectNewPassword:(NSString *)newPwd OldPassword:(NSString *)oldPwd;

/// 设置夜视状态
/// @param ledAuto 1:自动 ledLevel无效  0:关闭自动，ledLevel有效
/// @param ledLevel 1:开启夜视  0:关闭夜视
- (void)sendLedStatusWithAuto:(BOOL)ledAuto LedLevel:(BOOL)ledLevel;

/// 格式化TF卡
- (void)sendFormatExtStorage;

/// 设置当前时间
- (void)sendCurrentTime;

/// 设置指示灯状态
/// @param status 1:开启  0:关闭
- (void)sendIndicatorLightStatus:(int)status;

/// 设置视频质量
/// @param quality 质量
- (void)sendDeviceVideoQuality:(AV_DASA_LEVEL)quality;

/// 设置视频翻转
/// @param flip flip
- (void)sendDeviceVideoFlip:(int)flip;

/// 手动喂食
/// @param weight 重量
- (void)sendManualFeedingWithWeight:(unsigned int)weight;

/// 修改自动喂食
/// @param feedArray 新的喂食数组
- (BOOL)sendAutoFeedingIsNewMethod:(NSArray *)feedArray;

/// 设置童锁状态
/// @param status 1开启 0关闭
- (void)sendChildrenLockStatus:(int)status;

/// 设置OSD状态
/// @param showOSD 1开启 0关闭
- (void)sendShowOSD:(BOOL)showOSD;


/// 升级固件
/// @param type <#type description#>
- (void)sendUpgrade:(enum_upgrade_type)type;

/// 播放TF回放
/// @param model evnetModel
- (void)sendStartPlayTFRecordWithEventModel:(JKEventModel *)model;

/// 暂停播放TF回放
/// @param model evnetModel
- (void)sendStopPlayTFRecordWithEventModel:(JKEventModel *)model;

/// 停止播放TF回放
/// @param model evnetModel
- (void)sendPauseStopTFRecordWithEventModel:(JKEventModel *)model;

/// 播放TF回放指定播放时间位置
/// @param model evnetModel
/// @param time 跳到的时间位置
- (void)sendPlayTFRecordWithEventModel:(JKEventModel *)model SeekTime:(unsigned int)time;

+ (void)IOTC_Setup_Session_Alive_Timeout_ForJKCamera:(NSUInteger)timeout;


#pragma mark ===============以下协议是根据tutk文档来判断设备的支持功能===============
- (NSArray *)getSupportedStreams;
- (BOOL)getAudioInSupportOfChannel:(NSInteger)channel;
- (BOOL)getAudioOutSupportOfChannel:(NSInteger)channel;
- (BOOL)getPanTiltSupportOfChannel:(NSInteger)channel;
- (BOOL)getEventListSupportOfChannel:(NSInteger)channel;
- (BOOL)getPlaybackSupportOfChannel:(NSInteger)channel;
- (BOOL)getWiFiSettingSupportOfChannel:(NSInteger)channel;
- (BOOL)getMotionDetectionSettingSupportOfChannel:(NSInteger)channel;
- (BOOL)getRecordSettingSupportOfChannel:(NSInteger)channel;
- (BOOL)getFormatSDCardSupportOfChannel:(NSInteger)channel;
- (BOOL)getVideoFlipSupportOfChannel:(NSInteger)channel;
- (BOOL)getEnvironmentModeSupportOfChannel:(NSInteger)channel;
- (BOOL)getMultiStreamSupportOfChannel:(NSInteger)channel;
- (NSInteger)getAudioOutFormatOfChannel:(NSInteger)channel;
- (BOOL)getVideoQualitySettingSupportOfChannel:(NSInteger)channel;
- (BOOL)getDeviceInfoSupportOfChannel:(NSInteger)channel;
- (BOOL)getDeviceUpgradeOnlineSupportOfChannel:(NSInteger)channel;
- (BOOL)getDevicePTZSupportOfChannel:(NSInteger)channel;
- (BOOL)getDeviceRestorySupportOfChannel:(NSInteger)channel;
- (BOOL)getDeviceRebootSupportOfChannel:(NSInteger)channel;
- (BOOL)getDeviceIRCutSupportOfChannel:(NSInteger)channel;
- (BOOL)getPWDeviceLowProfileSupportOfChannel:(NSInteger)channel;

@end

