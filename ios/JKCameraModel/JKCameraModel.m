//
//  JKCameraModel.m
//  demo
//
//  Created by mac on 2021/9/6.
//  Copyright © 2021 mac. All rights reserved.
//

#import "JKCameraModel.h"
#import "JKFFmpegH265Decoder.h"


static NSString *const AddressOfMQTTServer      = @"s2.skymeesound.com";  // MQTT服务器地址 //华东:47.97.101.149:1883
static UInt16   const PortOfMQTTServer          = 1883;  // MQTT服务器端口
static UInt16   const PortOfMQTTServerWithSSL   = 1883;  // MQTT服务器端口
static UInt16   const DefaultDeviceAuthor       = 0x0000; // 设备默认授权码
#pragma mark - 项目相关主题
//topic
static NSString *const HeadTopic           = @"app2dev/";

@interface JKCameraModel ()<CameraDelegate, JKFFmpegH265DecoderDelegate>{
    JKLocalRecorder *myLocalRecorder;
    
}
///媒体输出方式 1、插线耳机 2、蓝牙耳机 其它为扬声器
@property (assign, nonatomic) NSInteger audioOutputMethod;

///录制录像的文件名
@property (strong, nonatomic) NSString *fileName;


@property (nonatomic, strong) NSThread *connectThread;
@property (nonatomic, strong) NSConditionLock *connectThreadLock;
@property (nonatomic, strong) NSString *filePath;
@property (assign, nonatomic) BOOL write;
///视频数据缓冲池
@property char *videoBuffer2;
///手机与0时区偏移毫秒数
@property (assign, nonatomic) long phoneZeroTimeZone;

@end

@implementation JKCameraModel

#pragma mark ===============初始化===============
- (instancetype)init
{
    self = [super init];
    if (self) {
        [self myInit];
    }
    self.delegate = self;
    return self;
}
#pragma mark ===============初始化设备名称、设备密码===============
- (instancetype)initWithName:(NSString *)name Password:(NSString *)password{
    self = [super initWithName:name];
    
    if (self) {
        [self myInit];
        self.deviceName = name;
        self.devPassword = password;
        dispatch_async(dispatch_get_main_queue(), ^{
            self.videoMonitor = [[Monitor alloc] init];
        });
    }
    self.delegate = self;
    
    return self;
}

- (void)myInit{
    
    self.authority = @"own";
    self.devid = @"";
    self.lastChannel = 0;
    self.isPushMode = YES;
    self.unitTypeStr = @"webcam";
    self.deviceName = DEFAULT_DEVICE_NAME;
    self.devPassword = DEFAULT_CAMERA_PASSWORD;
    self.getSupportStream = NO;
    self.getRecvAudioFormat = NO;
    self.getTimeZoneSuccessful = NO;
    self.secondsnGMTDiff = 0;
    self.getdeviceIdOrigSuccessful = NO;
    self.motionDetectionRingMode = 0;
    self.abilityProductTypeNum = 0;
    self.abilityContentLength = 0;
    self.abilityList = 0;
    self.getdeviceSoundListSuccessful = NO;
    self.soundList = [[NSMutableArray alloc] init];
    self.getdeviceCitySuccessful = NO;
    self.cityName = @"";
    self.getAlexaSuccessful = NO;
    self.alexaSwitch = 0;
    self.getDogBarkingSuccessful = NO;
    self.dogBarkingSwitch = 0;
    self.getLuminositySuccessful = NO;
    self.sensitivity = 0;
    self.getVolumeSuccessful = NO;
    self.volumeValue = 0;
    self.getRecordSuccessful = NO;
    self.recordIndex = 0;
    self.getdeviceFeedListSuccessful = NO;
    self.recordMode = -1;
    self.getRecordModeSuccessful = NO;
    self.feedPlanList = [[NSMutableArray alloc] init];
    self.arrayStreamChannel = [[NSMutableArray alloc] init];
    self.wifiList = [[NSMutableArray alloc] init];
    self.phoneZeroTimeZone = [[NSTimeZone localTimeZone] secondsFromGMT] *1000;
    self.videoMonitor.backgroundColor = [UIColor blackColor];

    self.pilotLamp = 1;
    
    self.twoWayVoice = NO;
    
    self.videoBuffer2 = (char *)malloc(MAX_IMG_BUFFER_SIZE);
}
#pragma mark ===============设备连接===============
- (void)connectStatus{

    if (JUDGED(self.devid)) {
        return ;
    }

    dispatch_async(dispatch_queue_create("connectStatus", NULL), ^{
        if (self.wrongPassword) {
            
        }else {
        
            if (self.sessionState == CONNECTION_STATE_CONNECTED && [self getConnectionStateOfChannel:self.lastChannel] == CONNECTION_STATE_CONNECTED) {///在线 不用处理
                if (!self.setNetWorking) {
                    [self getDeviceStatus];
                }
            }else {

                if (self.sessionState == CONNECTION_STATE_UNKNOWN_DEVICE ||
                    self.sessionState == CONNECTION_STATE_UNSUPPORTED ||
                    self.sessionState == CONNECTION_STATE_CONNECT_FAILED ||
                    self.sessionState == CONNECTION_STATE_CONNECTING) {///连接中和连接不上不用处理
                   

                }else {
                    if (self.sessionState == CONNECTION_STATE_CONNECTED  && ([self getConnectionStateOfChannel:self.lastChannel] == CONNECTION_STATE_CONNECTING || [self getConnectionStateOfChannel:self.lastChannel] == CONNECTION_STATE_NONE)) {///连接通道中
                       

                    }else {
                        
                        if (self.sessionState != CONNECTION_STATE_CONNECTED) {
                            [self connect:self.devid];
                            NSLog(@"111111111111");
                        }
                        
                        if ([self getConnectionStateOfChannel:self.lastChannel] != CONNECTION_STATE_CONNECTED) {
                            [self start:0];
//                            [self start:3];
                        }
                        if (!self.setNetWorking) {
                            [self getDeviceStatus];
                        }
                        
                    }
                }

            }
        }
    });
}

#pragma mark ================获取设备在线状态==============
- (NSInteger)getConnectStatus{
    
    if (self.sessionState == CONNECTION_STATE_CONNECTED  && [self getConnectionStateOfChannel:self.lastChannel] == CONNECTION_STATE_CONNECTED) {
        return ONLINE;
    }
    else if (self.sessionState == CONNECTION_STATE_CONNECTED  && ([self getConnectionStateOfChannel:self.lastChannel] == CONNECTION_STATE_CONNECTING || [self getConnectionStateOfChannel:self.lastChannel] == CONNECTION_STATE_NONE)) {
        return CONNECTING;
    }
    else {
        return OFFLINE;
    }
    
}

#pragma mark ===============断开连接===============
- (void)myDisconnect {
    self.getRecvAudioFormat = NO;
    self.getSupportStream = NO;
    [self disconnect];
}

#pragma mark ===============开始连接默认通道===============
- (void)start{
    [super start:self.lastChannel viewAccount:@"admin" viewPassword:self.devPassword];
    
}

#pragma mark ===============开始连接指定通道===============
- (void)start:(NSInteger)channel {
    [super start:channel viewAccount:@"admin" viewPassword:self.devPassword];
}

#pragma mark ===============获取设备状态===============
- (void)getDeviceStatus{
    if (!self.getSupportStream) {
        SMsgAVIoctrlGetSupportStreamReq *s = (SMsgAVIoctrlGetSupportStreamReq *)malloc(sizeof(SMsgAVIoctrlGetSupportStreamReq));
        [self sendIOCtrlToChannel:0
                             Type:IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_REQ
                             Data:(char *)s
                         DataSize:sizeof(SMsgAVIoctrlGetSupportStreamReq)];
        free(s);
    }

    if (!self.getRecvAudioFormat) {
        SMsgAVIoctrlGetAudioOutFormatReq *s = (SMsgAVIoctrlGetAudioOutFormatReq *)malloc(sizeof(SMsgAVIoctrlGetAudioOutFormatReq));
        s->channel = 0;
        [self sendIOCtrlToChannel:0
                             Type:IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_REQ
                             Data:(char *)s
                         DataSize:sizeof(SMsgAVIoctrlGetAudioOutFormatReq)];
        free(s);
    }

    
//    if (!self.getTimeZoneSuccessful){
//        ///获取设备时间
//        [self getDeviceTimeZone];
//    }
//    if (!self.getPushAddressSuccessful) {
//        ///获取设备推送地址
//        [self getDevicePushAddress];
//    }
//
//    if (!self.getdeviceSoundListSuccessful) {
//        ///获取设备音频列表
//        [self getDeviceSoundList];
//    }
//    if (self.getdeviceCitySuccessful) {
//        ///获取设备所在城市
//        [self getDeviceCurrentCity];
//    }
//
//    if (!self.getdeviceFeedListSuccessful){
//        ///获取设备喂食计划列表
//        [self getDeviceFeedPlanListIsNewMethod:YES];
//    }
//
//    if (!self.getLuminositySuccessful){
//        ///移动侦测状态
//        [self getDeviceMotionDetect];
//    }
//
//    if (!self.getRecordModeSuccessful){
//        ///录像模式
//        [self getDeviceTFRecordModel];
//    }
//
//    if (!self.getDeviceInfoSuccessful){
//        ///设备信息，有无SD卡
//        [self getDeviceTFInfo];
//    }
//
//    if (!self.getMirroringSuccessful){
//        ///视频翻转
//        [self getDeviceVideoFlip];
//    }
//
//    if (!self.getCurrenQualitySuccessful){
//        ///视频质量
//        [self getDeviceVideoQuality];
//    }
//
//    if (!self.getPilotLampSuccessful){
//        ///指示灯
//        [self getDeviceIndicatorLightStatus];
//    }
//
//    if (!self.getChildrenLockSuccessful){
//        ///童锁
//        [self getDeviceChildrenLockStatus];
//    }
//
//    if (!self.getShowOSDSuccessful) {
//        ///osd显示&隐藏
//        [self getDeviceOSDStatus];
//    }
//
//    if (!self.getDeviceWiFiInfoSuccessful){
//        ///获取设备连接的wifi信息
//        [self getDeviceCurrentConnectWiFiInfo];
//    }
//
//    if (!self.getDeviceWiFiListSuccessful){
//        ///获取设备搜索到的wifi列表
//        [self getDeviceSearchWiFiList];
//    }
//
//    [self setDevicePushAddress];
    
}
#pragma mark ===============设置推送地址===============
- (void)setDevicePushAddress {
    if (self.getPushAddressSuccessful && self.setPushAddressSuccessful == NO) {
        
//        NSUserDefaults * defaults = [NSUserDefaults standardUserDefaults];
//        NSString *push_ip = [defaults valueForKey:@"push_ip"];
//        NSString *push_port = [defaults valueForKey:@"push_port"];
//        NSString *push_server = [defaults valueForKey:@"push_server"];
        
        NSString *push_ip = @"71.132.59.31";
        NSString *push_port = @"9090";
        NSString *push_server = @"IMG_Server";
        
        if (push_ip.length != 0 && push_port != 0 && push_server.length != 0) {///给设备设置推送地址
            if ([self.pushIP isEqualToString:push_ip]&&[self.pushServer isEqualToString:push_server]&& self.pushPort == [push_port intValue]) {
                
                self.setPushAddressSuccessful = YES;
                
                NSLog(@"推送地址相同");
                
//                [self getDeviceUpgrade];
            }else {
                
                NSLog(@"推送地址不相同，获取到推送地址");
                [self sendPushAddressWithIP:push_ip PushPort:push_port PushServer:push_server];
            }
        }
    }
}

#pragma mark ===============开始显示===============
- (void)startShowWithChannel:(NSInteger)channel{
//    self.playBack = NO;
    H265DecoderManager.delegate = self;
    startH265Decode();
    [self startShow:channel];
}

- (void)stopShowWithChannel:(NSInteger)channel{
    
    self.playing = YES;
    if (self.listening) {
        [self stopListen];
    }
    
    if (self.talking) {
        [self stopTalk];
    }
    
    if (self.recording) {
        [self stopRecord];
    }
    self.playing = NO;

    H265DecoderManager.delegate = nil;
    stopH265Decode();
    
    [self stopShow:channel];
}

#pragma mark ===============监听===============
- (int)startListen{
    if (!self.playing) {
        ///设备离线
        return -1;
    }
    
    if (self.twoWayVoice) {
        if (!self.talking) {
            int res = [self setAudioSessionActive:YES];
            if (!self.listening) {
                if (res == 1) {
                    [self startSoundToPhoneForEcho:self.lastChannel];
                }else if(res == 0){
                    [self startSoundToPhone:self.lastChannel];
                }else {
                    return -2;
                }
            }
        }else {
            if (!self.listening) {
                [self startSoundToPhoneForEcho:self.lastChannel];
            }
        }
    }else {
        
        if (self.talking) {///关闭对讲
            self.talking = NO;
            [self stopSoundToDevice:self.lastChannel];
        }
        ///关闭防止由于一直在录像过程中关闭监听，导致startSoundToPhone未停止，线程一直在占用，无法开启新的监听
        [self stopSoundToPhone:self.lastChannel];
        
        if (!self.listening) {///开启监听
            int res = [self setAudioSessionActive:YES];
            if (res == -1) {
                return -2;
            }else {
                [self startSoundToPhone:self.lastChannel];
            }
        }
    }
    self.listening = YES;

    return YES;
}
- (BOOL)stopListen{
    if (!self.playing) {
        ///设备离线
        return NO;
    }
    if (self.twoWayVoice) {
        
        if (self.recording) {
            [self stopSoundToPhoneForOnlyRecv:self.lastChannel];
        } else {
            [self stopSoundToPhone:self.lastChannel];
        }
        
        if (!self.talking && !self.recording) {
            [self setAudioSessionActive:NO];
        }
    }else {
        if (self.recording) {
            [self stopSoundToPhoneForOnlyRecv:self.lastChannel];
        } else {
            [self stopSoundToPhone:self.lastChannel];
            [self setAudioSessionActive:NO];
        }
    }
    self.listening = NO;
    return YES;
    
}
#pragma mark ===============对讲===============
- (int)startTalk{
    if (!self.playing) {
        ///设备离线
        return -1;
    }
    if (self.twoWayVoice) {
        int res = [self setAudioSessionActive:YES];
        
        if (!self.talking) {
            if (res == 1) {
                [self startSoundToDeviceForEcho:self.lastChannel];
            }else if (res == 0){
                [self startSoundToDevice:self.lastChannel];
            }else {
                return -2;
            }
        }
        
    }else {
        if (self.listening) {///关闭监听
            self.listening = NO;
            if (self.recording) {
                [self stopSoundToPhoneForOnlyRecv:self.lastChannel];
            } else {
                [self stopSoundToPhone:self.lastChannel];
            }
        }
        
        if (!self.talking) {///开启对讲
            int res = [self setAudioSessionActive:YES];
            if (res == -1) {
                return -2;
            }else {
                [self startSoundToDevice:self.lastChannel];
            }
        }
    }
    self.talking = YES;
    return YES;
}
- (BOOL)stopTalk{

    if (self.twoWayVoice) {

        [self stopSoundToDevice:self.lastChannel];

        if (!self.listening) {
            [self setAudioSessionActive:NO];
        }
    }else {
        [self stopSoundToDevice:self.lastChannel];
        if (!self.recording) {
            [self setAudioSessionActive:NO];
        }
    }
    self.talking = NO;
    return YES;
        
}
    
/// 设置音频会话活跃状态 返回是否需要开启消回音
/// @param active active
- (BOOL)setAudioSessionActive:(BOOL)active{
    NSError *error = nil;
    NSError *nserror = nil;
    int result = 0;
    
    AVAudioSession* session = [AVAudioSession sharedInstance];
    [session setActive:active error:&error];
    if (active) {
        if (self.audioOutputMethod == 2){
            [session setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionAllowBluetooth error:&nserror];
            result = 0;
        }else if (self.audioOutputMethod == 1) {
            [session setCategory:AVAudioSessionCategoryPlayAndRecord error:&nserror];
            result = 0;
        }else {
            [session setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionDefaultToSpeaker error:&nserror];
            result = 1;
        }
    }else {
        ///设置为扬声器模式
        AVAudioSession *audioSession = [AVAudioSession sharedInstance];
        //设置为播放
        [audioSession setCategory:AVAudioSessionCategoryPlayback error:nil];
    }
    if (error||nserror) {
        result = -1;
    }
    return result;
}

#pragma mark ===============开始录像===============
- (BOOL)startRecordWithPath:(NSString *)filePath{
    
    if (!self.playing) {
        return NO;
    }
    
    if (!myLocalRecorder) {
        myLocalRecorder = [[JKLocalRecorder alloc] init];
        myLocalRecorder.directoryPath = filePath;
    }
    [myLocalRecorder setStartRecordFlag:NO];

    self.recording = YES;
    self.fileName = @"";
    if (!self.listening) {
        [self startSoundToPhoneForEchoForOnlyRecv:self.lastChannel];
    }
    
    
    return YES;
}
- (NSString *)stopRecord{
    if (self.recording) {
        if (!self.listening) {
            [self stopSoundToPhone:self.lastChannel];
        }
        
        self.recording = NO;

        if(myLocalRecorder){
            dispatch_async(dispatch_get_main_queue(), ^{
                [self->myLocalRecorder performSelectorOnMainThread:@selector(stopRecord) withObject:nil waitUntilDone:YES];
            });
        }
    }
    
    return self.fileName;
}
#pragma mark ===============拍照===============
- (UIImage *)screenshot{
    if (self.encryptionFormat == ENCRYPTION_FORMAT_H264) {
        if (self.videoMonitor.image != nil) {
            return self.videoMonitor.image;
        }
        return nil;
    }else {
        if (self.videoMonitor.image != nil) {
            return self.videoMonitor.image;
        }
        return nil;
    }
}

#pragma mark ===============写入文件===============
- (void)startWriteAudioFileWithModel:(JKAudioModel *)audioModel andFilePath:(NSString *)path{
    if (!audioModel||!path) {
        return;
    }
    
    self.filePath = path;
    
    SmsgAVIoctrlTranferFileReq *s = (SmsgAVIoctrlTranferFileReq *)malloc(sizeof(SmsgAVIoctrlTranferFileReq));
    memset(s, 0, sizeof(SmsgAVIoctrlTranferFileReq));
    
    s->type = 0;
    
    memcpy(s->sound_info.sound_name, [audioModel.fileName UTF8String], sizeof(s->sound_info.sound_name));
    memcpy(s->sound_info.sound_aliase, [audioModel.fileName UTF8String], sizeof(s->sound_info.sound_aliase));

    s->sound_info.play_time = (int)audioModel.playTime;
    s->sound_info.creat_time = (int)audioModel.createTime;
    
    [self sendIOCtrlToChannel:0
                           Type:IOTYPE_USER_IPCAM_PETS_AUDIO_FILE_SEND_REQ
                           Data:(char *)s
                       DataSize:sizeof(SmsgAVIoctrlTranferFileReq)];
    free(s);
    
    self.write = YES;
    ///构建线程锁传输文件
    self.connectThreadLock = nil;
    self.connectThread = nil;

    self.connectThreadLock = [[NSConditionLock alloc] initWithCondition:NOTDONE];
    self.connectThread = [[NSThread alloc] initWithTarget:self selector:@selector(doLoopConnect) object:nil];
    [self.connectThread start];
    
}

- (void)stopWrite{
    self.write = NO;
    if (self.connectThread) {
        [self.connectThreadLock lockWhenCondition:DONE];
        [self.connectThreadLock unlock];
        self.connectThreadLock = nil;
        self.connectThread = nil;
    }
}


- (void)doLoopConnect{
    [self.connectThreadLock lock];

    int SID = (int)self.sessionID;
    //NSLog(@"SID:%d", SID);
    if (SID < 0) {
    } else {
        int ret = [self threadSend:SID];
        //NSLog(@"threadSend ret:%d", ret);
        if (ret < 0) {
            dispatch_async(dispatch_get_main_queue(), ^{
  
                if (self.cameraDelegate && [self.cameraDelegate respondsToSelector:@selector(JKCameraModel:fileWrittenSuccessfully:)]) {
                    [self.cameraDelegate JKCameraModel:self fileWrittenSuccessfully:NO];
                }
            });

        } else {
            
            dispatch_async(dispatch_get_main_queue(), ^{
                if (self.cameraDelegate && [self.cameraDelegate respondsToSelector:@selector(JKCameraModel:fileWrittenSuccessfully:)]) {
                    [self.cameraDelegate JKCameraModel:self fileWrittenSuccessfully:YES];
                }
                
            });
            
        }
    }

    [self stopWrite];
}

- (int)threadSend:(int)SID {
    int ret = 0;
    char gFn[128];
    
    struct st_SInfo sInfo;
    IOTC_Session_Check(SID, &sInfo);

    char buf[MAX_BUF_SIZE];
    int RDT_ID = RDT_Create(SID, RDT_WAIT_TIMEMS, 3);
    if(RDT_ID < 0)
    {
        return -1;
    }

    RDTCommandStruct *recvRDTCommandStruct;
    RDTCommandStruct sendRDTCommandStruct;
    int i = 0;
    
    for(i=0; ; i++)
    {
        memset(gFn, 0, sizeof(gFn));
        
        // recv file name
        memset(buf, 0, sizeof(buf));
        ret = RDT_Read(RDT_ID, buf, 1024, RDT_WAIT_TIMEMS);
        if(ret < 0)
        {
            ret = -200;
  
            goto rdtend;
        }
        
        recvRDTCommandStruct = (RDTCommandStruct *)buf;
        if(recvRDTCommandStruct->type != RDT_FILE_NAME)
        {
          
            if(recvRDTCommandStruct->type == RDT_STOP)
            {
               
                break;
            } else {
                
                ret = -201;
                goto rdtend;
            }
        }

        strcpy(gFn, recvRDTCommandStruct->content);
        
       
        NSString *sendFilePath = [self wavFileSyncToDevicePlayOK:self.filePath];

        if (nil == sendFilePath ||
            [sendFilePath isEqualToString:@""]) {
            return -1;
        }

        memset(buf, 0, sizeof(buf));
        FILE *fp = fopen([sendFilePath UTF8String], "rb");
        if(fp == NULL)
        {
            break;
        }
        long filesize = 0;
        long hasSendSize = 0;
        fseek(fp, 0, SEEK_END);
        filesize = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        memset(&sendRDTCommandStruct, 0, sizeof(sendRDTCommandStruct));
        sendRDTCommandStruct.type = RDT_FILE_SIZE;
        sprintf(sendRDTCommandStruct.content, "%lu", filesize);
    
        ret =  RDT_Write(RDT_ID, (const char*)&sendRDTCommandStruct, sizeof(sendRDTCommandStruct));
        if(ret < 0)
        {
            ret = -202;
            goto rdtend;
        }
        memset(buf, 0, sizeof(buf));
        ret = RDT_Read(RDT_ID, buf, 1024, RDT_WAIT_TIMEMS);
        if(ret < 0 && (strcmp(buf, START_STRING) != 0))
        {
            ret = -203;
            goto rdtend;
        }
        recvRDTCommandStruct = (RDTCommandStruct *)buf;
        if(recvRDTCommandStruct->type != RDT_FILE_START)
        {
            ret = -204;
            goto rdtend;
        }
        memset(buf, 0, sizeof(buf));
        struct st_RDT_Status rdtStatus;
        while(self.write)
        {
            memset(buf, 0, sizeof(buf));
            ret = fread(buf, 1, MAX_BUF_SIZE, fp);
            hasSendSize += ret;
        
            if(ret <= 0) break;
            ret = RDT_Write(RDT_ID, buf, ret);
            //NSLog(@"while buf=%s\n", buf);
            if(ret < 0)
            {
                ret = -205;
                goto rdtend;
            }
            if((ret = RDT_Status_Check(RDT_ID, &rdtStatus)) == RDT_ER_NoERROR)
            {

                dispatch_async(dispatch_get_main_queue(), ^{
      
                    if (self.cameraDelegate && [self.cameraDelegate respondsToSelector:@selector(JKCameraModel:fileWrittenSuccessfully:)]) {
                        [self.cameraDelegate JKCameraModel:self fileWritingProgress:hasSendSize/filesize];
                    }
                });
                if(sInfo.Mode == 2)
                {
                    if(rdtStatus.BufSizeInSendQueue > 1024000)
                        usleep(50000);
                }
                else
                {
                    if(rdtStatus.BufSizeInSendQueue > 1024000)
                        sleep(1);
                }
            }
            else
            {
                ret = -206;
                goto rdtend;
            }
        }
       
        fclose(fp);
    }
rdtend:
    RDT_Destroy(RDT_ID);
    return ret;
}

- (NSString *)wavFileSyncToDevicePlayOK:(NSString *)wavFilePath {
    BOOL isSyncFile = NO;
    int ret = 0;
    char buf[MAX_BUF_SIZE];
    memset(buf, 0, sizeof(buf));
    NSString *wavBakFilePath = [NSString stringWithFormat:@"%@.bak", wavFilePath];

    int fileLen = 0;
    NSFileManager* manager = [NSFileManager defaultManager];
    if ([manager fileExistsAtPath:wavFilePath]){
        fileLen = (int)[[manager attributesOfItemAtPath:wavFilePath error:nil] fileSize];
    }
    FILE *fp = fopen([wavFilePath  UTF8String], "r");
    if(fp == NULL)
    {
        return nil;
    }
    FILE *fpW = fopen([wavBakFilePath  UTF8String], "w+");
    if(fpW == NULL)
    {
        return nil;
    }
    while(1)
    {
        ret = fread(buf, 1, MAX_BUF_SIZE, fp);
        if(ret <= 0 )
        {
            break;
        }
        if (isSyncFile) {
        } else {
            int wave = 0;
            int fmt = 0;
            while(wave < ret)
            {
                if (buf[wave++] == 'W' &&
                    buf[wave++] == 'A' &&
                    buf[wave++] == 'V' &&
                    buf[wave++] == 'E') {
                    
                    fmt = wave;
                    while(fmt < ret)
                    {
                        if (buf[fmt++] == 'f' &&
                            buf[fmt++] == 'm' &&
                            buf[fmt++] == 't' &&
                            buf[fmt++] == ' ') {
                            break;
                        } else {
                        }
                    }
                    break;
                } else {
                 
                }
            }
         
            if (wave != 0 &&
                fmt != 0 &&
                wave+4 != fmt) {
                char buffer[MAX_BUF_SIZE];
                memset(buffer, 0, sizeof(buffer));
                memcpy(buffer, buf, wave);
                memcpy(buffer+wave, buf+fmt-4, ret-(fmt-4));
                memset(buf, 0, sizeof(buf));
                memcpy(buf, buffer, sizeof(buffer));
                int fileNewLen = fileLen - (fmt-wave-4);

                buf[4] = (char) ((fileNewLen-8) & 0xff);
                buf[5] = (char) (((fileNewLen-8) >> 8) & 0xff);
                buf[6] = (char) (((fileNewLen-8) >> 16) & 0xff);
                buf[7] = (char) (((fileNewLen-8) >> 24) & 0xff);
            }
            isSyncFile = YES;
        }
        fwrite(buf, 1, ret, fpW);
        fflush(fpW);
        memset(buf, 0, sizeof(buf));
    }
    fclose(fpW);
    fclose(fp);
    return wavBakFilePath;
}
#pragma mark ===============以下为与设备交互发送协议的方法(获取设备的状态)===============
#pragma mark ===============获取设备推送地址===============
- (void)getDevicePushAddress {
    ///获取推送地址
    SMsgAVIoctrlPushserverAddrReq *s = (SMsgAVIoctrlPushserverAddrReq *)malloc(sizeof(SMsgAVIoctrlPushserverAddrReq));
    memset(s, 0, sizeof(SMsgAVIoctrlPushserverAddrReq));
    s->command_type = 0;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_PUSHSERVER_ADDR_SETTING_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlPushserverAddrReq)];
    free(s);
}
#pragma mark ===============获取设备时区===============
- (void)getDeviceTimeZone {
    
    SMsgAVIoctrlTimeZone *s = (SMsgAVIoctrlTimeZone *)malloc(sizeof(SMsgAVIoctrlTimeZone));
    memset(s, 0, sizeof(SMsgAVIoctrlTimeZone));
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_GET_TIMEZONE_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlTimeZone)];
    free(s);
    
}
#pragma mark ===============获取设备移动侦测状态===============
- (void)getDeviceMotionDetect {
    SMsgAVIoctrlGetMotionDetectReq *s = (SMsgAVIoctrlGetMotionDetectReq *)malloc(sizeof(SMsgAVIoctrlGetMotionDetectReq));
    memset(s, 0, sizeof(SMsgAVIoctrlGetMotionDetectReq));
    s->channel = 0;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_GETMOTIONDETECT_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlGetMotionDetectReq)];
    free(s);
}
#pragma mark ===============获取设备TF录像模式===============
- (void)getDeviceTFRecordModel {
    SMsgAVIoctrlGetRecordReq *s = (SMsgAVIoctrlGetRecordReq *)malloc(sizeof(SMsgAVIoctrlGetRecordReq));
    memset(s, 0, sizeof(SMsgAVIoctrlGetRecordReq));
    s->channel = 0;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_GETRECORD_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlGetRecordReq)];
    free(s);
}
#pragma mark ===============获取设备TF信息（是否存在TF卡、卡容量、固件版本）===============
- (void)getDeviceTFInfo {
    SMsgAVIoctrlDeviceInfoReq *s = (SMsgAVIoctrlDeviceInfoReq *)malloc(sizeof(SMsgAVIoctrlDeviceInfoReq));
    memset(s, 0, sizeof(SMsgAVIoctrlDeviceInfoReq));
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_DEVINFO_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlDeviceInfoReq)];
    free(s);
}
#pragma mark ===============获取设备搜索到的wifi列表===============
- (void)getDeviceSearchWiFiList {
    ///获取设备搜索到的wifi列表
    SMsgAVIoctrlListWifiApReq *s = (SMsgAVIoctrlListWifiApReq *)malloc(sizeof(SMsgAVIoctrlListWifiApReq));
    memset(s, 0, sizeof(SMsgAVIoctrlListWifiApReq));
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_LISTWIFIAP_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlListWifiApReq)];
    free(s);
}
#pragma mark ===============获取设备当前连接的wifi信息===============
- (void)getDeviceCurrentConnectWiFiInfo {
    SMsgAVIoctrlGetWifiReq *s = (SMsgAVIoctrlGetWifiReq *)malloc(sizeof(SMsgAVIoctrlGetWifiReq));
    memset(s, 0, sizeof(SMsgAVIoctrlGetWifiReq));
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_GETWIFI_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlDeviceInfoReq)];
    free(s);
}
#pragma mark ===============获取指示灯状态===============
- (void)getDeviceIndicatorLightStatus {
    SMsgAVIoctrlThirdpartReq *s = (SMsgAVIoctrlThirdpartReq *)malloc(sizeof(SMsgAVIoctrlThirdpartReq));
    memset(s, 0, sizeof(SMsgAVIoctrlThirdpartReq));
    s->command_types_ = THIRD_PART_GET_LED_STATUS;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_THIRDPART_SETTING_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlThirdpartReq)];
    free(s);
}
#pragma mark ===============获取夜视状态===============
- (void)getDeviceLedStatus{
    SIRLedCtrl *s = (SIRLedCtrl *)malloc(sizeof(SIRLedCtrl));
    memset(s, 0, sizeof(SIRLedCtrl));
    s->cmdDir = 0;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_SET_IRLED_REQ
                         Data:(char *)s
                     DataSize:sizeof(SIRLedCtrl)];
    free(s);
}
#pragma mark ===============获取设备固件版本===============
- (void)getDeviceUpgrade {
    SMsgAVIoctrlSetUpgradeOnlineReq *s = (SMsgAVIoctrlSetUpgradeOnlineReq *)malloc(sizeof(SMsgAVIoctrlSetUpgradeOnlineReq));
    memset(s, 0, sizeof(SMsgAVIoctrlSetUpgradeOnlineReq));
    s->type = UPGRADE_ONLINE_TYPE_CHECK;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_SET_UPGRDEONLIN_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlSetUpgradeOnlineReq)];
    free(s);
}
#pragma mark ===============获取喂食计划列表===============
- (void)getDeviceFeedPlanListIsNewMethod:(BOOL)newMethod {
    
    NSLog(@"获取喂食计划：%d", (int)newMethod);
    
    if (newMethod) {
        SmsgAVIoctrlGetMeaListReq *s = (SmsgAVIoctrlGetMeaListReq *)malloc(sizeof(SmsgAVIoctrlGetMeaListReq));
        memset(s, 0, sizeof(SmsgAVIoctrlGetMeaListReq));
        s->cmd_type = 0;
        [self sendIOCtrlToChannel:0
                             Type:IOTYPE_USER_IPCAM_PETS_SET_SIXED_MEAL_LIST_REQ
                             Data:(char *)s
                         DataSize:sizeof(SmsgAVIoctrlGetMeaListReq)];
        free(s);
    }else {
        char data1[28];
        memset(data1, 0x0, sizeof(data1));
        data1[0] = TTY_CMD_0XFF;
        data1[1] = TTY_CMD_0XFF;
        data1[2] = TTY_CMD_GET_FEED;
        data1[3] = 1;
        data1[4] = 0;
        SmsgAVIoctrlTtyDataReq *s1 = (SmsgAVIoctrlTtyDataReq *)malloc(sizeof(SmsgAVIoctrlTtyDataReq));
        memset(s1, 0, sizeof(SmsgAVIoctrlTtyDataReq));
        s1->type = TTY_CMD_GET_FEED;
        s1->length = 5;
        memcpy(s1->data, data1, s1->length);
        [self sendIOCtrlToChannel:0
                             Type:IOTYPE_USER_IPCAM_TRANSFER_TTY_DATA_REQ
                             Data:(char *)s1
                         DataSize:sizeof(SmsgAVIoctrlTtyDataReq)];
        free(s1);
    }

}
#pragma mark ===============获取设备城市===============
- (void)getDeviceCurrentCity {
    SmsgAVIoctrlSetLocationReq *s = (SmsgAVIoctrlSetLocationReq *)malloc(sizeof(SmsgAVIoctrlSetLocationReq));
    memset(s, 0, sizeof(SmsgAVIoctrlSetLocationReq));
    s->type = 0;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_PETS_GET_LOCALTION_REQ
                         Data:(char *)s
                     DataSize:sizeof(SmsgAVIoctrlSetLocationReq)];
    free(s);
}
#pragma mark ===============获取设备音频列表===============
- (void)getDeviceSoundList {
    SmsgAVIoctrlGetPlayDogSoundListReq *s = (SmsgAVIoctrlGetPlayDogSoundListReq *)malloc(sizeof(SmsgAVIoctrlGetPlayDogSoundListReq));
    memset(s, 0, sizeof(SmsgAVIoctrlGetPlayDogSoundListReq));
    s->cmd_type = 0;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_PETS_GET_PLAY_DOG_SOUND_LIST_REQ
                         Data:(char *)s
                     DataSize:sizeof(SmsgAVIoctrlGetPlayDogSoundListReq)];
    free(s);
}
#pragma mark ===============获取视频质量===============
- (void)getDeviceVideoQuality {
    SMsgAVIoctrlGetStreamCtrlReq *s = (SMsgAVIoctrlGetStreamCtrlReq *)malloc(sizeof(SMsgAVIoctrlGetStreamCtrlReq));
    memset(s, 0, sizeof(SMsgAVIoctrlGetStreamCtrlReq));
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_GETSTREAMCTRL_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlGetStreamCtrlReq)];
    free(s);
}
#pragma mark ===============获取视频翻转情况===============
- (void)getDeviceVideoFlip {
    SMsgAVIoctrlGetVideoModeReq *s = (SMsgAVIoctrlGetVideoModeReq *)malloc(sizeof(SMsgAVIoctrlGetVideoModeReq));
    memset(s, 0, sizeof(SMsgAVIoctrlGetVideoModeReq));
    s->channel = (unsigned int)self.lastChannel;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_GET_VIDEOMODE_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlGetVideoModeReq)];
    free(s);
}
#pragma mark ===============获取童锁状态===============
- (void)getDeviceChildrenLockStatus {
    SMsgAVIoctrlGetLockReq *s = (SMsgAVIoctrlGetLockReq *)malloc(sizeof(SMsgAVIoctrlGetLockReq));
    memset(s, 0, sizeof(SMsgAVIoctrlGetLockReq));
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_GET_CHILDREN_LOCK_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlGetLockReq)];
    free(s);
}
#pragma mark ===============获取OSD状态===============
- (void)getDeviceOSDStatus {
    SMsgAVIoctrlGetVideoOSDReq *s = (SMsgAVIoctrlGetVideoOSDReq *)malloc(sizeof(SMsgAVIoctrlGetVideoOSDReq));
    memset(s, 0, sizeof(SMsgAVIoctrlGetVideoOSDReq));
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_GET_VIDEOOSD_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlGetVideoOSDReq)];
    free(s);
}

#pragma mark ===============获取Wi-Fi信号强度===============
- (void)getDeviceWiFiSignal {
    ///获取信号强度
    SmsgAVIoctrlGetWiFiSignalReq *s = (SmsgAVIoctrlGetWiFiSignalReq *)malloc(sizeof(SmsgAVIoctrlGetWiFiSignalReq));
    memset(s, 0, sizeof(SmsgAVIoctrlGetWiFiSignalReq));
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_GET_WIFI_SIGNAL_REQ
                         Data:(char *)s
                     DataSize:sizeof(SmsgAVIoctrlGetWiFiSignalReq)];
    free(s);
}

#pragma mark ===============以下为与设备交互发送协议的方法(设置设备的状态)===============
#pragma mark ===============设置设备推送地址===============
- (void)sendPushAddressWithIP:(NSString *)pushIP PushPort:(NSString *)pushPort PushServer:(NSString *)pushServer {
    SMsgAVIoctrlPushserverAddrReq *s = (SMsgAVIoctrlPushserverAddrReq *)malloc(sizeof(SMsgAVIoctrlPushserverAddrReq));
    memset(s, 0, sizeof(SMsgAVIoctrlPushserverAddrReq));
    s->command_type = 1;
    memcpy(s->ip_addrs, [pushIP UTF8String], sizeof(s->ip_addrs));
    s->ip_port = (unsigned int)[pushPort intValue];
    memcpy(s->server_push_path, [pushServer UTF8String], sizeof(s->server_push_path));
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_PUSHSERVER_ADDR_SETTING_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlPushserverAddrReq)];
    free(s);
}
#pragma mark ===============设置wifi信息===============
- (void)sendWiFiInfoWithSSID:(NSString *)ssid Password:(NSString *)password {
    SMsgAVIoctrlSetWifiReq *s = (SMsgAVIoctrlSetWifiReq *)malloc(sizeof(SMsgAVIoctrlSetWifiReq));
    memcpy(s->ssid, [ssid UTF8String], 32);
    memcpy(s->password, [password UTF8String], 32);
    s->enctype = (password == nil || [password isEqualToString:@""]) ? AVIOTC_WIFIAPENC_NONE : AVIOTC_WIFIAPENC_WPA2_AES;
    s->mode = AVIOTC_WIFIAPMODE_NULL;
    s->reserved[0] = 99;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_SETWIFI_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlSetWifiReq)];
    free(s);
}
#pragma mark ===============设置设备连接密码===============
- (void)sendConnectNewPassword:(NSString *)newPwd OldPassword:(NSString *)oldPwd {
    SMsgAVIoctrlSetPasswdReq *s = (SMsgAVIoctrlSetPasswdReq *)malloc(sizeof(SMsgAVIoctrlSetPasswdReq));
    memset(s, 0, sizeof(SMsgAVIoctrlSetPasswdReq));
    memcpy(s->oldpasswd, [oldPwd UTF8String], [oldPwd length]);
    memcpy(s->newpasswd, [newPwd UTF8String], [newPwd length]);
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_SETPASSWORD_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlSetPasswdReq)];
    free(s);
}
#pragma mark ===============设置当前时间===============
- (void)sendCurrentTime {
    SMsgAVIoctrlSetTimeReq *s = (SMsgAVIoctrlSetTimeReq *)malloc(sizeof(SMsgAVIoctrlSetTimeReq));
    s->time_second_0zone_ = [[NSDate date] timeIntervalSince1970];
    s->diff_zone_minites_ = [[NSTimeZone localTimeZone] secondsFromGMT] / 60;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_SET_TIME_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlSetTimeReq)];
    free(s);
}
#pragma mark ===============设置指示灯状态===============
- (void)sendIndicatorLightStatus:(int)status {
    /*
     0、关闭
     1、开启
     */
    SMsgAVIoctrlThirdpartReq *s = (SMsgAVIoctrlThirdpartReq *)malloc(sizeof(SMsgAVIoctrlThirdpartReq));
    memset(s, 0, sizeof(SMsgAVIoctrlThirdpartReq));
    s->command_types_ = THIRD_PART_SET_LED_STATUS;
    s->value1_ = status;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_THIRDPART_SETTING_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlThirdpartReq)];
    free(s);
}
#pragma mark ===============设置夜视状态===============
- (void)sendLedStatusWithAuto:(BOOL)ledAuto LedLevel:(BOOL)ledLevel {
    SIRLedCtrl *s = (SIRLedCtrl *)malloc(sizeof(SIRLedCtrl));
    memset(s, 0, sizeof(SIRLedCtrl));
    s->cmdDir = 1;
    s->ledLevel = ledLevel;
    s->isAuto = ledAuto;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_SET_IRLED_REQ
                         Data:(char *)s
                     DataSize:sizeof(SIRLedCtrl)];
    free(s);
}

#pragma mark ===============格式化TF卡===============
- (void)sendFormatExtStorage {
    SMsgAVIoctrlFormatExtStorageReq *s = (SMsgAVIoctrlFormatExtStorageReq *)malloc(sizeof(SMsgAVIoctrlFormatExtStorageReq));
    memset(s, 0, sizeof(SMsgAVIoctrlFormatExtStorageReq));
    s->storage = 0;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_FORMATEXTSTORAGE_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlFormatExtStorageReq)];
    free(s);
}
#pragma mark ===============固件升级===============
- (void)sendUpgrade:(enum_upgrade_type)type {
    SMsgAVIoctrlSetUpgradeOnlineReq *s = (SMsgAVIoctrlSetUpgradeOnlineReq *)malloc(sizeof(SMsgAVIoctrlSetUpgradeOnlineReq));
    memset(s, 0, sizeof(SMsgAVIoctrlSetUpgradeOnlineReq));
    s->type = type;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_SET_UPGRDEONLIN_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlSetUpgradeOnlineReq)];
    free(s);
}
#pragma mark ===============设置质量质量===============
- (void)sendDeviceVideoQuality:(AV_DASA_LEVEL)quality {
    /*
     1、FHD
     2、HD
     5、LOW
     3~4、SD
    */
    SMsgAVIoctrlSetStreamCtrlReq *s = (SMsgAVIoctrlSetStreamCtrlReq *)malloc(sizeof(SMsgAVIoctrlSetStreamCtrlReq));
    memset(s, 0, sizeof(SMsgAVIoctrlSetStreamCtrlReq));
    s->channel = (unsigned int)self.lastChannel;
    s->quality = quality;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_SETSTREAMCTRL_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlSetStreamCtrlReq)];
    free(s);
}
#pragma mark ===============设置视频翻转===============
- (void)sendDeviceVideoFlip:(int)flip {
    
    NSLog(@"设置视频翻转：%d",flip);
    /*
     0:无翻转、无镜像，正常状态
     1、只上下翻转
     2、只左右镜像
     3、上下翻转并且左右镜像
    */
    SMsgAVIoctrlSetVideoModeReq *s = (SMsgAVIoctrlSetVideoModeReq *)malloc(sizeof(SMsgAVIoctrlSetVideoModeReq));
    memset(s, 0, sizeof(SMsgAVIoctrlSetVideoModeReq));
    s->channel = (unsigned int)self.lastChannel;
    s->mode = flip;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_SET_VIDEOMODE_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlSetVideoModeReq)];
    free(s);
}
#pragma mark ===============手动喂食===============
- (void)sendManualFeedingWithWeight:(unsigned int)weight {
    
    NSLog(@"喂食重量:%d",weight);
    
    NSDate *nowDate = [NSDate date];
    NSCalendar *calendar = [NSCalendar currentCalendar];
    NSUInteger unitFlags = NSCalendarUnitYear | //年
    NSCalendarUnitMonth | //月份
    NSCalendarUnitDay | //日
    NSCalendarUnitHour |  //小时
    NSCalendarUnitMinute;  //分钟

    NSDateComponents *dateComponent = [calendar components:unitFlags fromDate:nowDate];
    char data[28];
    memset(data, 0x0, sizeof(data));
    data[0] = TTY_CMD_0XFF;
    data[1] = TTY_CMD_0XFF;
    data[2] = TTY_CMD_SET_FEED;
    data[3] = 10;
    data[4] = [dateComponent year] - 1960;
    data[5] = [dateComponent month];
    data[6] = [dateComponent day];
    data[7] = [dateComponent hour];
    data[8] = [dateComponent minute];
    data[9] = weight;
    data[10] = (weight >> 8);
    data[11] = (0 << 4) | (0);
    data[12] = 0;
    data[13] = 10;
//
//    NSLog(@"data:");
//    for (int i=0; i<14; i++) {
//        printf("%x==", data[i]);
//    }
//    printf("\n");
//
    SmsgAVIoctrlTtyDataReq *s = (SmsgAVIoctrlTtyDataReq *)malloc(sizeof(SmsgAVIoctrlTtyDataReq));
    memset(s, 0, sizeof(SmsgAVIoctrlTtyDataReq));
    s->type = TTY_CMD_SET_FEED;
    s->length = 14;
    memcpy(s->data, data, s->length);
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_TRANSFER_TTY_DATA_REQ
                         Data:(char *)s
                     DataSize:sizeof(SmsgAVIoctrlTtyDataReq)];
    free(s);
}
#pragma mark ===============自动喂食===============
- (BOOL)sendAutoFeedingIsNewMethod:(NSArray *)feedArray {
    
    struct_multiy_meal_list_p2p struct_meal_list;
    memset(&struct_meal_list, 0, sizeof(struct_multiy_meal_list_p2p));
    struct_meal_list.num_ = 6;
    
    int listLen = (int)feedArray.count;
    if (listLen != struct_meal_list.num_) {
        NSLog(@"sendFeedSettingInfoListToTty listLen != struct_meal_list.num_    return");
        return NO;
    }
    
    for (int i=0; i<listLen; i++) {
        JKFeedModel * model = (JKFeedModel *)[feedArray objectAtIndex:i];

        char data[28];
        memset(data, 0x0, sizeof(data));
        
        data[0] = TTY_CMD_0XFF;
        data[1] = TTY_CMD_0XFF;
        
        data[2] = TTY_CMD_SET_FEED;
        
        data[3] = 10;
        
        data[4] = model.feedYear;
        data[5] = model.feedMonth;

        //为了兼容星期，固定设置0x7f
        data[6] = model.feedDay;

        data[7] = model.hour;
        data[8] = model.minute;
        
        data[9] = [model.feedweight intValue];
        data[10] = ([model.feedweight intValue] >> 8);
        
        data[11] = ([model.feedtype intValue] << 4) | ([model.gofeed intValue]);
        
        data[12] = [model.index intValue];
        
        data[13] = [model.audioindex intValue];
        
        (struct_meal_list.device_meal_list_[i]).meal_id_ = [model.index intValue];

        memcpy((struct_meal_list.device_meal_list_[i]).tty_meal_info, data, 14);

        (struct_meal_list.device_meal_list_[i]).one_meal_weight = [model.lattic intValue];
     
        (struct_meal_list.device_meal_list_[i]).is_meal_info_changed = model.isMealInfoChanged;
        
        memcpy((struct_meal_list.device_meal_list_[i]).meal_aliase_, [model.feedname UTF8String], sizeof((struct_meal_list.device_meal_list_[i]).meal_aliase_));
        
//        NSLog(@"(struct_meal_list.device_meal_list_[i]).meal_id_:%d", (struct_meal_list.device_meal_list_[i]).meal_id_);
//        NSLog(@"(struct_meal_list.device_meal_list_[i]).one_meal_weight:%d", (struct_meal_list.device_meal_list_[i]).one_meal_weight);
//        NSLog(@"(struct_meal_list.device_meal_list_[i]).is_meal_info_changed:%d", (struct_meal_list.device_meal_list_[i]).is_meal_info_changed);
//        NSLog(@"(struct_meal_list.device_meal_list_[i]).meal_aliase_:%s", (struct_meal_list.device_meal_list_[i]).meal_aliase_);
//
//        NSLog(@"data:");
//        for (int i=0; i<14; i++) {
//            printf("%x==", data[i]);
//        }
//        printf("\n");

    }
    
    SmsgAVIoctrlSetMeaListReq *s = malloc(sizeof(SmsgAVIoctrlSetMeaListReq));
    memset(s, 0, sizeof(SmsgAVIoctrlSetMeaListReq));
    s->cmd_type = 1;  //0-get, 1-set
    memcpy(&(s->meal_list_info), &struct_meal_list, sizeof(struct_multiy_meal_list_p2p));

    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_PETS_SET_SIXED_MEAL_LIST_REQ
                         Data:(char *)s
                     DataSize:sizeof(SmsgAVIoctrlSetMeaListReq)];

    free(s);
    
    return YES;

}

#pragma mark ===============设置童锁状态===============
- (void)sendChildrenLockStatus:(int)status {
    SMsgAVIoctrlSetLockReq *s = (SMsgAVIoctrlSetLockReq *)malloc(sizeof(SMsgAVIoctrlSetLockReq));
    memset(s, 0, sizeof(SMsgAVIoctrlSetLockReq));
    s->lockEnable = status;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_SET_CHILDREN_LOCK_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlSetLockReq)];
    free(s);
}
#pragma mark ===============显示&隐藏OSD===============
- (void)sendShowOSD:(BOOL)showOSD {
    SMsgAVIoctrlSetVideoOSDReq *s = (SMsgAVIoctrlSetVideoOSDReq *)malloc(sizeof(SMsgAVIoctrlSetVideoOSDReq));
    memset(s, 0, sizeof(SMsgAVIoctrlSetVideoOSDReq));
    if (showOSD) {
        s->osdEnable = 1;
    }else {
        s->osdEnable = 0;
    }
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_SET_VIDEOOSD_REQ
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlSetVideoOSDReq)];
    free(s);
}

#pragma mark ===============播放TF录像回放===============
- (void)sendStartPlayTFRecordWithEventModel:(JKEventModel *)model {
    SMsgAVIoctrlPlayRecord *s = (SMsgAVIoctrlPlayRecord *)malloc(sizeof(SMsgAVIoctrlPlayRecord));
    memset(s, 0, sizeof(SMsgAVIoctrlPlayRecord));
    s->channel = 0;
    s->command = AVIOCTRL_RECORD_PLAY_PAUSE;
    s->stTimeDay = [JKEventModel getTimeDay:model.eventTime];
    s->Param = model.eventType;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlPlayRecord)];
    free(s);
}
#pragma mark ===============停止播放TF录像回放===============
- (void)sendStopPlayTFRecordWithEventModel:(JKEventModel *)model {
    SMsgAVIoctrlPlayRecord *s = (SMsgAVIoctrlPlayRecord *)malloc(sizeof(SMsgAVIoctrlPlayRecord));
    memset(s, 0, sizeof(SMsgAVIoctrlPlayRecord));
    s->channel = 0;
    s->command = AVIOCTRL_RECORD_PLAY_STOP;
    s->stTimeDay = [JKEventModel getTimeDay:model.eventTime];
    s->Param = model.eventType;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlPlayRecord)];
    free(s);
}
#pragma mark ===============暂停播放TF录像回放===============
- (void)sendPauseStopTFRecordWithEventModel:(JKEventModel *)model {
    SMsgAVIoctrlPlayRecord *s = (SMsgAVIoctrlPlayRecord *)malloc(sizeof(SMsgAVIoctrlPlayRecord));
    memset(s, 0, sizeof(SMsgAVIoctrlPlayRecord));
    s->channel = 0;
    s->command = AVIOCTRL_RECORD_PLAY_PAUSE;
    s->stTimeDay = [JKEventModel getTimeDay:model.eventTime];
    s->Param = model.eventType;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL
                         Data:(char *)s
                     DataSize:sizeof(SMsgAVIoctrlPlayRecord)];
    free(s);
}
#pragma mark ===============暂停播放TF录像回放===============
- (void)sendPlayTFRecordWithEventModel:(JKEventModel *)model SeekTime:(unsigned int)time{
    SMsgAVIoctrlPlayRecord *req = (SMsgAVIoctrlPlayRecord *)malloc(sizeof(SMsgAVIoctrlPlayRecord));
    memset(req, 0, sizeof(SMsgAVIoctrlPlayRecord));
    req->channel = 0;
    req->command = AVIOCTRL_RECORD_PLAY_SEEKTIME;
    req->stTimeDay = [JKEventModel getTimeDay:model.eventTime];
    req->Param = model.eventType;
    req->reserved_ = time;
    [self sendIOCtrlToChannel:0
                         Type:IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL
                         Data:(char *)req
                     DataSize:sizeof(SMsgAVIoctrlPlayRecord)];
    free(req);
}


#pragma mark ===============检查喂食计划是否合法===============
- (BOOL)checkFeedSettingInfoValidity:(JKFeedModel *)model {
    
    NSInteger maxSetingCount = 6;
    BOOL isValidity = YES;
    if ([model.index intValue] > maxSetingCount || [model.index intValue] == 0) {
        isValidity = NO;
    } else if (model.hour > 23) {
        isValidity = NO;
    } else if (model.minute > 60) {
        isValidity = NO;
    } else if ([model.feedweight intValue] > 20 * 10 || [model.feedweight intValue] < 0) {
        isValidity = NO;
    } else if ([model.feedtype intValue]!= 1) {
        isValidity = NO;
    } else if ([model.gofeed intValue]!= 0 && [model.gofeed intValue]!= 1) {
        isValidity = NO;
    } else if ([model.audioindex intValue] > 10 ||
               ([model.audioindex intValue] >= 3 && [model.audioindex intValue] < 10)) {
        isValidity = NO;
    }
    return isValidity;
    
}
#pragma mark ===============CameraDelegate===============
- (void)camera:(Camera *)camera didChangeSessionStatus:(NSInteger)status{
    
    self.playing = NO;
    
    NSLog(@"didChangeSessionStatus = %ld", (long)status);
    
    if (status == CONNECTION_STATE_UNKNOWN_DEVICE ||
        status == CONNECTION_STATE_UNSUPPORTED ||
        status == CONNECTION_STATE_CONNECT_FAILED ||
        status == CONNECTION_STATE_TIMEOUT) {
       
        NSLog(@"333333333333");
        [self myDisconnect];
        
    }else {

    }
    
    
    if (self.cameraDelegate && [self.cameraDelegate respondsToSelector:@selector(JKCameraModel:didChangeSessionStatus:)]) {
        
        [self.cameraDelegate JKCameraModel:self didChangeSessionStatus:status];
    } 
}

- (void)camera:(Camera *)camera didChangeChannelStatus:(NSInteger)channel ChannelStatus:(NSInteger)status {
    
    
    NSLog(@"设备ID:%@,设备密码：%@,连接状态：%ld, status = %ld channel = %ld",self.devid,self.devPassword,(long)self.sessionState, (long)status, (long)channel);
    
    
    dispatch_async(dispatch_queue_create("wrong_password", NULL), ^{
        if (status == CONNECTION_STATE_WRONG_PASSWORD) {
            
            self.wrongPassword = YES;
            NSLog(@"4444444444");
            [self myDisconnect];

        }
    });


    if (self.cameraDelegate && [self.cameraDelegate respondsToSelector:@selector(JKCameraModel:didChangeChannelStatus:ChannelStatus:)]) {
        
        [self.cameraDelegate JKCameraModel:self didChangeChannelStatus:channel ChannelStatus:status];
    }
    
}

/// 设备回调
/// @param camera camera
/// @param type type
/// @param data data
/// @param size size
- (void)camera:(Camera *)camera didReceiveIOCtrlWithType:(NSInteger)type Data:(const char*)data DataSize:(NSInteger)size {
    
    if (type == (int)IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_RESP) {

        SMsgAVIoctrlGetSupportStreamResp *s = (SMsgAVIoctrlGetSupportStreamResp *)data;
        
        NSLog(@"!!! *** !!! *** !!! *** !!! *** !!! *** !!! *** !!! camera.uid:%@  MyCamera didReceiveIOCtrlWithType IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_RESP", self.uid);

        self.getSupportStream = YES;
        
        if (s->number > 0) {
            SStreamDef *def = malloc(size - (sizeof(s->number)));
            memcpy(def, s->streams, size - (sizeof(s->number)));
            
            for (int i = 0; i < s->number; i++) {
                
                SubStream_t ch;
                ch.index = def[i].index;
                ch.channel = def[i].channel;
                
                NSValue *objCh = [[NSValue alloc] initWithBytes:&ch objCType:@encode(SubStream_t)];
//                [arrayStreamChannel addObject:objCh];
//                [objCh release];
                
                NSLog(@"!!! *** !!! *** !!! *** !!! *** !!! *** !!! *** !!! camera.uid:%@  MyCamera didReceiveIOCtrlWithType IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_RESP s->number:%d, ch.index:%d, ch.channel:%d", self.uid, s->number, ch.index, ch.channel);

                if (def[i].channel != 0) {

                    [self start:def[i].channel];
                }
            }
            free(def);
        }
    }else if (type == IOTYPE_USER_IPCAM_PUSHSERVER_ADDR_SETTING_RESP) {
        SMsgAVIoctrlPushserverAddrResp *s = (SMsgAVIoctrlPushserverAddrResp*)data;
        
        NSLog(@"设备推送地址 s->command_type:%d  s->result:%d s->ip_addr:%s s->server_push_path:%s s->ip_port:%d", s->command_type, s->result, s->ip_addrs, s->server_push_path, s->ip_port);
 
        // 0-get  1-set
        if (s->command_type == 0) {
            
            if (0 == s->result) {
                
                self.getPushAddressSuccessful = YES;
                
                self.pushIP = [NSString stringWithFormat:@"%s", s->ip_addrs];
                self.pushPort = s->ip_port;
                self.pushServer = [NSString stringWithFormat:@"%s", s->server_push_path];

            }
            
            self.setPushAddressSuccessful = NO;
            [self setDevicePushAddress];
            
        } else {
            
            if (0 == s->result) {
                self.setPushAddressSuccessful = YES;
   
//                //获取版本号
//                [self getDeviceUpgrade];
            }
        }
    
    } else if (IOTYPE_USER_IPCAM_DEVICE_USER_EVENT_REPORT == type) {///移动侦测设备主动上报
        
        NSLog(@"移动侦测来了 deviceID:%@", self.devid);
        /*
        SMsgAVIoctrlUserEvent *s = (SMsgAVIoctrlUserEvent *)data;
        NSInteger eventType = s->event;
        NSLog(@"eventType:%ld", (long)eventType);
        NSUInteger eventTime = s->time;
        NSLog(@"eventTime:%ld", (long)eventTime);
        //NSString *eventAlias = [NSString stringWithFormat:@"",];

        NSString *picn = [NSString stringWithUTF8String:(char *)s->pic_name];
        NSString *alias = [NSString stringWithUTF8String:(char *)s->event_device_name];
        NSString *devid = [NSString stringWithUTF8String:(char *)s->key_id];
        
        if (!picn) {
            picn = [NSString stringWithFormat:@"%@", @""];
        }
        if (!alias) {
            alias = [NSString stringWithFormat:@"%@", @""];
        }
        if (!devid) {
            devid = [NSString stringWithFormat:@"%@", @""];
        }
        NSLog(@"picn:%@, alias:%@, devid:%@", picn, alias, devid);
 
        self.eventCount ++;
        
        ///更新数据库
        [OU_CAMDataBaseTool updataDeviceListWithDeviceID:self.devid andKey:@"eventCount" Value:[NSString stringWithFormat:@"%d",self.eventCount]];
        
        
        NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
        [dateFormatter setLocale:[NSLocale currentLocale]];
        [dateFormatter setDateStyle:NSDateFormatterMediumStyle];
        [dateFormatter setTimeStyle:NSDateFormatterMediumStyle];
        NSDate *date = [[NSDate alloc] initWithTimeIntervalSince1970:eventTime];
        NSString * time = [dateFormatter stringFromDate:date];

        NSDictionary * dict = @{@"devid":self.devid,
                                @"picn":picn,
                                @"time":time,
                                @"alias":self.deviceName,
                                @"type":[Event getEventTypeName:(int)eventType]};
        


        dispatch_async(dispatch_get_main_queue(), ^{
            [[NSNotificationCenter defaultCenter] postNotificationName:RELOAD_EVENT_COUNT object:nil];
        });
        
        if (self.motionDetectionRingMode) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [[NSNotificationCenter defaultCenter] postNotificationName:MOTION_DETECTION_REMINDER object:self
                                                                  userInfo:dict];
    
            });
        }else {///安静模式不弹窗
            
        }
        */
        SMsgAVIoctrlUserEvent *s = (SMsgAVIoctrlUserEvent *)data;
        NSLog(@"事件类型:%02lx", (long)s->event);
        NSLog(@"事件时间:%ld", (long)s->time);
        NSLog(@"喂食类型:%ld", (long)s->feed_type);
        NSLog(@"喂食重量:%ld", (long)s->feed_weight);
//        if (s->event == USER_EVENT_FEED_PETS_TIMER_FEED ||
//            s->event == USER_EVENT_FEED_PETS_MANUL_FEED ||
//            s->event == USER_EVENT_FEED_PETS_FEED_WARNING ||
//            s->event == USER_EVENT_FEED_PETS_NO_FOOD_WARING ||
//            s->event == USER_EVENT_FEED_PETS_OUT_FOOD_WARING ) {
//            
//        }
        /*
         typedef enum
         {
             USER_EVENT_ALL                    = 0x00,    // all event type(general APP-->IPCamera)
             USER_EVENT_MOTIONDECT            = 0x01,    // motion detect start//==s==
             USER_EVENT_VIDEOLOST            = 0x02,    // video lost alarm
             USER_EVENT_IOALARM                = 0x03, // io alarmin start //---s--

             USER_EVENT_MOTIONPASS            = 0x04, // motion detect end  //==e==
             USER_EVENT_VIDEORESUME            = 0x05,    // video resume
             USER_EVENT_IOALARMPASS            = 0x06, // IO alarmin end   //---e--

             USER_EVENT_EXPT_REBOOT            = 0x10, // system exception reboot
             USER_EVENT_SDFAULT                = 0x11, // sd record exception
             USER_EVENT_DOOR_BELL            = 0x12,  // door bell
             USER_EVENT_PIR_WARNING          = 0x13,  // pir (door alarm)
             USER_EVENT_ALARM_DOOR_WINDOW    = 0X14,  // for door window
             USER_EVENT_ALARM_INFRARED       = 0X15,  // for infrared
             USER_EVENT_ALARM_SMOKING        = 0X16,  // for smoking warning
             USER_EVENT_ALARM_AIR            = 0X17,  // for air warning
             USER_EVENT_ALARM_WHISTLE        = 0X18,  // for whistile warning (Siren)
             USER_EVENT_ALARM_SWITCH         = 0X19,  // for switch warning ()
             USER_EVENT_ALARM_REMOTE         = 0X1A,   // for remote control warning
             USER_EVENT_ALARM_GAS               = 0X1B,   // for gas warning
             USER_EVENT_ALARM_DOOR_LOWVOL        = 0X1C,   // for door low power warning
             USER_EVENT_ALARM_SMOK_LOWVOL        = 0X1D,   // for smok low power warning
             USER_EVENT_ALARM_IRDA_LOWVOL        = 0X1E,   // for 红外探测 low power warning
             USER_EVENT_ALARM_AIR_LOWVOL        = 0X1F,   // for air low power warning
             USER_EVENT_ALARM_SWITCH_LOWVOL    = 0X20,   // for 开关低电量 warning
             USER_EVENT_ALARM_WHISTLE_LOWVOL    = 0X21,   // for 警笛低电量 warning
             USER_EVENT_ALARM_DOOR_OFFLINE    = 0X22,   // for door离线 warning
             USER_EVENT_ALARM_SMOK_OFFLINE    = 0X23,   // for 烟感离线 warning
             USER_EVENT_ALARM_IRDA_OFFLINE    = 0X24,   // for 红外探测离线 warning
             USER_EVENT_ALARM_AIR_OFFLINE        = 0X25,   // for air离线 warning
             USER_EVENT_ALARM_SWITCH_OFFLINE    = 0X26,   // for 开关离线 warning
             USER_EVENT_ALARM_WHISTLE_OFFLINE    = 0X27,   // for 警笛离线 warning
             USER_EVENT_ALARM_GAS_OFFLINE        = 0X28,   // for gas离线 warning

             USER_EVENT_ALARM_ARMED          = 0X30,   // for armed  手机布防 away 模式
             USER_EVENT_ALARM_DISARM         = 0X31,    // fo disarmed, 手机撤防模式
             USER_EVENT_FEED_PETS_TIMER_FEED  = 0X32,    // for pets  timer feed success
             USER_EVENT_FEED_PETS_MANUL_FEED  = 0X33,    // for pets  manul feed success
             USER_EVENT_FEED_PETS_FEED_WARNING= 0X34,    // for pets alarm food warning
             USER_EVENT_FEED_PETS_NO_FOOD_WARING= 0X35,    // for pets alarm food warning,    // for pets feed failed
             USER_EVENT_FEED_PETS_OUT_FOOD_WARING= 0X36,    // for pets feed failed
             USER_EVENT_SAFEBOX_DOOR_OPENED= 0X37,    // for safebox door opened
             USER_EVENT_SAFEBOX_DOOR_ERROR = 0X38,    // for safebox door passwd-error, or safebox being moving,
             USER_EVENT_SAFEBOX_HOSTAGE    = 0X39,     // for SAFEBOX Hostage
             USER_EVENT_P2P_ONLIE  = 0X3A,             // for p2p online
             USER_EVENT_P2P_OFFLINE= 0X3B,             // for p2p offline
             USER_EVENT_ACCOUNT_LOGIN_OHTRER_LOCATION= 0X3C,    // login in orther loacaltion
             USER_EVENT_MUSIC_PLAYING_STATUS_CHANGED= 0X3D,     // 音乐播放状态变化提醒
             USER_EVENT_BABY_CRING_NOTIFY= 0X3E,                //婴儿哭声提醒
             USER_EVENT_DEVICE_PASSWD_CHANGED= 0X3F,     //设备密码修改提醒
             USER_EVENT_DEVICE_TEMPTURE_ALARMED= 0X40,     //温度告警提醒
             USER_EVENT_DEVICE_HUMIDITY_ALARMED= 0X41,     //湿度告警提醒
             USER_EVENT_FEED_PETS_FEED_OK      = 0X42,    // for pets  feed success
             USER_EVENT_FEED_PETS_FEED_FAILED  = 0X43,    // for pets  feed failed
             USER_EVENT_FEED_PETS_FEED_MOTOR_ERROR  = 0X44, //电机卡住了
             USER_EVENT_SNAP_SHOT_EVENT    = 0XEF,    // for sanp shot-BOGUANG
             USER_EVENT_RECORD_START       = 0XF0,    // for BOGUANG START RECORD
             USER_EVENT_RECORD_STOP        = 0XF1,    // for BOGUANG STOP RECORD,
             USER_EVENT_WARING_BLUE_BOOTTH = 0XF2,    // for BLUETOOLTH ALARMMING
             USER_EVENT_LOW_POWER          = 0XF3,     // for BATTERY LOW POWER
             USER_EVENT_ARMED_HOME_MODE    = 0XF4,     // for HOME-ALARMED -LAJITONG
             USER_EVENT_ARMED_DOOR_MOVED   = 0XF5,     // for door moved
             USER_EVENT_PETWANT_PIR_DETECT = 0XF6,     // for pet pir  detect notify
             USER_EVENT_ARMED_DISALAM_MODE_AUTO  = 0XF7,     // for DISALAM-ALARMED -LAJITONG
             USER_EVENT_ARMED_ALARM_MODE_AUTO    = 0XF8,     // for ALARM-ALARMED -LAJITONG
             USER_EVENT_ARMED_HOME_MODE_AUTO     = 0XF9,      // for HOME-ALARMED -LAJITONG
             USER_EVENT_NOTIFY_VIDEO_DISABLE     = 0XFA,      // for HOME-ALARMED -LAJITONG
             USER_EVENT_NOTIFY_VIDEO_ENABLED     = 0XFB,     // for ALARM-ALARMED -LAJITONG
             USER_EVENT_PM25_WARING              = 0XFC,      //  FOR PM2.5 WARING
             USER_EVENT_SOS_WARING               = 0XFD,      // for SOS KEY WARING
             USER_EVENT_EVENT_DETECT_NOTIFY_SERVER = 0XFE,      // FOR MOTION NOT NOTIFY PHONE (maxkin n8)

             USER_EVENT_SYSTEM_SETTING_SYNC      = 0X1FF,      //  //同步系统喂食定时列表信息
             USER_EVENT_SYSTEM_SETTING_SOUNDINFO_SYNC      = 0X200,     //同步系统喂食音频信息
             USER_EVENT_PLAYMUSIC_START          = 0X201,     //音乐播放开启
             USER_EVENT_PLAYMUSIC_STOPED         = 0X202,     // 音乐播放关闭

             USER_EVENT_SAFEBOX_SHOCK                = 0X203,     // for SAFEBOX震动报警
         }ENUM_USER_EVENTTYPE;
         */
        
        
    }else if (type == IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_RESP) {
        /*
        SMsgAVIoctrlGetAudioOutFormatResp *s = (SMsgAVIoctrlGetAudioOutFormatResp *)data;
         */
        /*
         typedef struct
         {
             unsigned int channel;        // camera index
             int codecId;                // refer to ENUM_CODECID in AVFRAMEINFO.h
             char sample_rate;
             char bitdata;
             char channels;
             char reserved[1];
         }SMsgAVIoctrlGetAudioOutFormatResp;
         */
        
//        //NSLog(@"获取设备音频格式 s->channel:%d s->codecId:%d s->channels:%c s->bitdata:%c", s->channel, s->codecId, s->channels, s->bitdata);
        
        self.getRecvAudioFormat = YES;
        
    } else if(type == (int)IOTYPE_USER_IPCAM_GET_TIMEZONE_RESP) {///获取时区
        SMsgAVIoctrlTimeZone* s = (SMsgAVIoctrlTimeZone*)data;
        
        NSLog(@"获取时区 s->nGMTDiff:%d", s->nGMTDiff);
        
        if( s->cbSize == sizeof(SMsgAVIoctrlTimeZone) ) {
            
            self.getTimeZoneSuccessful = YES;
            self.secondsnGMTDiff = s->nGMTDiff * 60;

            if(strlen(s->szTimeZoneString) > 0 ){
                
            }
        }

    } else if (type == (int)IOTYPE_USER_IPCAM_SET_TIMEZONE_RESP){///设置时区
        SMsgAVIoctrlTimeZone* s = (SMsgAVIoctrlTimeZone*)data;
        
        NSLog(@"设置时区 s->nGMTDiff:%d", s->nGMTDiff);
        
        if( s->cbSize == sizeof(SMsgAVIoctrlTimeZone) ) {

            self.getTimeZoneSuccessful = YES;
            
            self.secondsnGMTDiff = s->nGMTDiff * 60;
            
            if(strlen(s->szTimeZoneString) > 0 ){

            }
        }
    

        /*
    }else if(type == IOTYPE_USER_IPCAM_GET_DEVICE_ABILITY_LIST_RESP) {
        SmsgAVIoctrlGetDeviceAbilityListResp* p = (SmsgAVIoctrlGetDeviceAbilityListResp*)data;
        //NSLog(@"获取设备能力值 p->product_type_num:%d p->content_length:%d", p->product_type_num, p->content_length);
        self.getdeviceIdOrigSuccessful = YES;
        self.abilityProductTypeNum = p->product_type_num;
        self.abilityContentLength = p->content_length;
        self.abilityList = p->ability_list[0];
        
        //NSLog(@"设备能力值：%d",p->ability_list[0]);
         */
    }else if (type == IOTYPE_USER_IPCAM_PETS_GET_PLAY_DOG_SOUND_LIST_RESP) {//获取设备录音列表
        
        SmsgAVIoctrlGetSoundListResp *s = (SmsgAVIoctrlGetSoundListResp *)data;
        //NSLog(@"获取设备录音列表 s->result:%d", s->result);

        if (self.soundList == nil||!self.soundList) {
            self.soundList = [[NSMutableArray alloc] init];
        }
        
        if (0 == s->result) {
            
            self.getdeviceSoundListSuccessful = YES;
            
            [self.soundList removeAllObjects];

            for (int i=0; i<MAX_SOUND_LIST_COUNT; i++) {
                JKAudioModel *model = [[JKAudioModel alloc] init];
                model.ID = (i+1);

                NSString *sound_name = [NSString stringWithUTF8String:((s->sound_lists).sound_array_[i]).sound_name];

                NSString *sound_aliase = [NSString stringWithUTF8String:((s->sound_lists).sound_array_[i]).sound_aliase];


                model.fileName = [NSString stringWithFormat:@"%@", sound_name];
                model.alias = [NSString stringWithFormat:@"%@", sound_aliase];

                model.playTime = ((s->sound_lists).sound_array_[i]).play_time;
                model.createTime = ((s->sound_lists).sound_array_[i]).creat_time;
                
                ///时间戳转为日期格式
                NSDate *date = [[NSDate alloc]initWithTimeIntervalSince1970:model.createTime];

                NSDateFormatter *formatter = [[NSDateFormatter alloc]init];

                [formatter setDateFormat:@"yyyy/MM/dd"];

                model.createTimeString = [formatter stringFromDate:date];
                
                int seconds = (int)model.playTime%60;
                int minutes = (int)model.playTime/60;
                if (seconds < 10) {
                    if (minutes < 10) {
                        model.playTimeString = [NSString stringWithFormat:@"0%d:0%d",minutes,seconds];
                    }else {
                        model.playTimeString = [NSString stringWithFormat:@"%d:0%d",minutes,seconds];
                    }
                }else {
                    if (minutes < 10) {
                        model.playTimeString = [NSString stringWithFormat:@"0%d:%d",minutes,seconds];
                    }else {
                        model.playTimeString = [NSString stringWithFormat:@"%d:%d",minutes,seconds];
                    }
                }
                
                if ([model.alias isEqualToString:INVALID_ALIAS_STR] || [model.alias isEqualToString:INVALID_ALIAS_STR2]) {
     
                } else {
                    [self.soundList addObject:model];
                }
 
            }
        }
         
    }else if (type == IOTYPE_USER_IPCAM_PETS_SET_LOCALTION_RESP){
        
        SmsgAVIoctrlSetLocationResp *s = (SmsgAVIoctrlSetLocationResp *)data;
        
        NSString *cityName = [[NSString alloc] initWithUTF8String:s->localtion_string];
        //NSLog(@"设置设备所处城市 s->result:%d 所处城市：%@", s->result,cityName);
        
        if (s->result == 0) {///设置成功
            
            self.getdeviceCitySuccessful = YES;
            
            self.cityName = cityName;
            
        }else {
            self.getdeviceCitySuccessful = NO;
        }
        
        /*
         
          IOTYPE_USER_IPCAM_PETS_SET_LOCALTION_REQ     =0x2082,
          IOTYPE_USER_IPCAM_PETS_SET_LOCALTION_RESP    =0x2083,

          IOTYPE_USER_IPCAM_PETS_GET_LOCALTION_REQ     =0x2084,
          IOTYPE_USER_IPCAM_PETS_GET_LOCALTION_RESP    =0x2085,
          
         typedef struct
         {
             unsigned int  type;     //0-get localton, 1-setlocaltion
             unsigned char localtion_string[64];
         }SmsgAVIoctrlSetLocationReq;

         typedef struct
         {
             int     result; //0-ok, orther failed
             unsigned char localtion_string[64];
         }SmsgAVIoctrlSetLocationResp;

         ///设备所处城市获取成功
         @property (nonatomic,assign) BOOL getdeviceCitySuccessful;
         ///设备录音列表，视频款使用
         @property (nonatomic,retain) NSString *cityName;
         */
    }else if (type == IOTYPE_USER_IPCAM_PETS_GET_LOCALTION_RESP){///获取设备经纬度
        SmsgAVIoctrlSetLocationResp *s = (SmsgAVIoctrlSetLocationResp *)data;
        
        NSString *cityName = [[NSString alloc] initWithUTF8String:s->localtion_string];
        //NSLog(@"获取设备所处城市 s->result:%d 所处城市：%@", s->result,cityName);
        
        if (s->result == 0) {
            
            self.getdeviceCitySuccessful = YES;
            
            self.cityName = cityName;
            
        }
        /*
    }else if (type == IOTYPE_USER_IPCAM_SET_OR_GRT_ALEXA_RESP) {
        
//        ///设备Alexa开关成功
//        @property (nonatomic,assign) BOOL getAlexaSuccessful;
//        ///alexa开关
//        @property (nonatomic,assign) BOOL alexaSwitch;
//
        
        SmsgAVIoctrlSetOrGetAlexaResp *s = (SmsgAVIoctrlSetOrGetAlexaResp *)data;

        //NSLog(@"获取或者设置Alexa开关 s->type:%d s->on_off:%d", s->type, s->on_off);
        if (s->result == 0) {
            self.getAlexaSuccessful = YES;
            self.alexaSwitch = s->on_off;
        }
        
    }else if (type == IOTYPE_USER_IPCAM_SET_OR_GRT_DOG_BARK_STATUS_RESP){
        
         /获取设备犬吠侦测开关成功
         @property (nonatomic,assign) BOOL getDogBarkingSuccessful;
         /犬吠侦测开关 0关，1开
         @property (nonatomic,assign) NSInteger dogBarkingSwitch;

         

        SmsgAVIoctrlSetOrGetDogBarkStatusResp *s = (SmsgAVIoctrlSetOrGetDogBarkStatusResp *)data;

        //NSLog(@"狗吠检测开关 s->type:%d s->status:%d", s->type, s->status);

        if (s->result == 0) {
            self.getDogBarkingSuccessful = YES;
            self.dogBarkingSwitch = s->status;
        }
         */
    } else if (type == IOTYPE_USER_IPCAM_GETMOTIONDETECT_RESP) {///获取移动侦测灵敏度
        
        SMsgAVIoctrlGetMotionDetectResp *s = (SMsgAVIoctrlGetMotionDetectResp *)data;
        
        //NSLog(@"获取移动侦测灵敏度 s->sensitivity:%d", s->sensitivity);

        self.getLuminositySuccessful = YES;
        self.sensitivity = s->sensitivity;

    }  else if (type == IOTYPE_USER_IPCAM_SETMOTIONDETECT_RESP) {///置移动侦测灵敏度
        
        SMsgAVIoctrlSetMotionDetectResp *s = (SMsgAVIoctrlSetMotionDetectResp *)data;
        //NSLog(@"设置移动侦测灵敏度 s->result:%d", s->result);
        if (s->result == 0) {
            self.getLuminositySuccessful = YES;
        }else {
            self.getLuminositySuccessful = NO;
        }
    } else if (type == IOTYPE_USER_IPCAM_PETS_SET_SIXED_MEAL_LIST_RESP) {///喂食列表
        
        SmsgAVIoctrlGetMeaListResp *s = (SmsgAVIoctrlGetMeaListResp*)data;
        
        NSLog(@"获取设备喂食计划返回 s->result:%d, s->cmd_type:%d", s->result, s->cmd_type);
        
        if (0 == s->cmd_type && s->result == 0) {
            
            NSMutableArray *array = [[NSMutableArray alloc] init];
            
            self.getdeviceFeedListSuccessful = YES;
            
            struct_multiy_meal_list_p2p meal_list_info;
            memset(&meal_list_info, 0x00, sizeof(struct_multiy_meal_list_p2p));
            
            memcpy(&meal_list_info, &(s->meal_list_info), sizeof(struct_multiy_meal_list_p2p));

            NSLog(@"meal_list_info.num_:%d", meal_list_info.num_);
            
            if (meal_list_info.num_ > 0) {
                for (int i=0; i<meal_list_info.num_; i++){
                    JKFeedModel * model = [[JKFeedModel alloc] init];
                    
                    model.lattic = [NSString stringWithFormat:@"%d",(meal_list_info.device_meal_list_[i]).one_meal_weight];
                    model.isMealInfoChanged = (meal_list_info.device_meal_list_[i]).is_meal_info_changed;
                    model.feedname = [NSString stringWithUTF8String:(meal_list_info.device_meal_list_[i]).meal_aliase_];
                    
                    char info[14];
                    memset(info, 0x00, sizeof(info));
                    
                    memcpy(info, (meal_list_info.device_meal_list_[i]).tty_meal_info, sizeof(info));
                    
                    model.feedYear = info[4];
                    model.feedMonth = info[5];
                    model.feedDay = info[6];
   
                    model.weekday = [JKCameraModel getBinaryByHex:[NSString stringWithFormat:@"%02lx",(long)model.feedDay]];

                    model.hour = info[7];
                    model.minute = info[8];
                    
                    model.feedweight = [NSString stringWithFormat:@"%d",(info[10] << 8) | (info[9] & 0x00FF)];
                    
                    if ((info[11] & 0xF0) >> 4 == 0) {
                        model.feedtype = @"1";
                    }else {
                        model.feedtype = [NSString stringWithFormat:@"%d",(info[11] & 0xF0) >> 4];
                    }
                    model.gofeed = [NSString stringWithFormat:@"%d",(info[11] & 0x0F)];
                    
                    model.index = [NSString stringWithFormat:@"%d",info[12]];
                    
                    model.audioindex = [NSString stringWithFormat:@"%d",info[13]];
                    
                    //NSLog(@"喂食计划录音：%@", model.audioindex);
                    
                    if ([self checkFeedSettingInfoValidity:model]) {
                        [array addObject:model];
                    }
                    ///时间戳
                    model.timestamp = model.hour * 60 + model.minute;
                    
//                    model.feedtime = [NSString stringWithFormat:@"%d:%d",info[7],info[8]];
                    ///喂食份数
                    if ((meal_list_info.device_meal_list_[i]).one_meal_weight == 10) {///大格子，比例1:10
                        model.feeddeal = [NSString stringWithFormat:@"%d",((info[10] << 8) | (info[9] & 0x00FF))/10];
                    }else {///小格子，比例1：5
                        model.feeddeal = [NSString stringWithFormat:@"%d",((info[10] << 8) | (info[9] & 0x00FF))/5];
                    }
                    model.feedtime = [NSString stringWithFormat:@"%02ld:%02ld",(long)model.hour, (long)model.minute];

                    NSLog(@"model.index:%@, model.feedYear:%d, model.feedMonth:%d, model.feedDay:%d, model.feedtime:%@, model.feedweight:%@, model.lattic:%@, model.gofeed:%@, model.type:%@, model.name;%@", model.index, (int)model.feedYear, (int)model.feedMonth, (int)model.feedDay, model.feedtime, model.feedweight, model.lattic, model.gofeed, model.feedtype, model.feedname);
                }
                ///排序
                [array sortUsingComparator:^NSComparisonResult(id  _Nonnull obj1, id  _Nonnull obj2) {
                    JKFeedModel * model1 = (JKFeedModel *)obj1;
                    JKFeedModel * model2 = (JKFeedModel *)obj2;
                    if (model1.timestamp < model2.timestamp) {
                        return NSOrderedAscending;
                    }else{
                        return NSOrderedDescending;
                    }
                }];
                
            }
            self.feedPlanList = array;
        }
    } else if (type == IOTYPE_USER_IPCAM_SET_SCHEDULE_REOCRD_SEC_RESP){///录像模式
        self.getRecordModeSuccessful = YES;
        SmsgAVIoctrlSetRecordScheduleTimeReq *s = (SmsgAVIoctrlSetRecordScheduleTimeReq*)data;
        
        self.recordMode = s->type;
        
        //NSLog(@"录像模式 s->type:%d", s->type);
        
    } else if (type == IOTYPE_USER_IPCAM_GETRECORD_RESP) {///录像模式
        
        self.getRecordModeSuccessful = YES;
        
        SMsgAVIoctrlGetRecordResq *s = (SMsgAVIoctrlGetRecordResq*)data;
        self.recordMode = s->recordType;
        self.record_time_minite = s->record_time_minite;
        
    } else if (type == IOTYPE_USER_IPCAM_SETRECORD_RESP) {///设置录像模式
        SMsgAVIoctrlSetRecordResp *s = (SMsgAVIoctrlSetRecordResp*)data;
        
        if (s->result == 1) {///设置成功
            self.getRecordModeSuccessful = YES;
        }else {
            self.getRecordModeSuccessful = NO;
        }
        
    } else if (type == IOTYPE_USER_IPCAM_DEVINFO_RESP) {///有无SD卡

        self.getDeviceInfoSuccessful = YES;

        SMsgAVIoctrlDeviceInfoResp *structDevInfo = (SMsgAVIoctrlDeviceInfoResp*)data;

        self.totalSize = structDevInfo->total;
        
        self.freeSize = structDevInfo->free;
        
        NSString * version = [NSString stringWithFormat:@"%x",structDevInfo->version];
        
        if (version.length < 8) {
            for (int i = 0; i < 8 - version.length; i ++) {
                version = [NSString stringWithFormat:@"0%@",version];
            }
        }
        if (version.length >= 8) {
            NSString * v1 = [version substringWithRange:NSMakeRange(0, 2)];
            NSString * v2 = [version substringWithRange:NSMakeRange(2, 2)];
            NSString * v3 = [version substringWithRange:NSMakeRange(4, 2)];
            NSString * v4 = [version substringWithRange:NSMakeRange(6, 2)];
            
            int version1 = (int)strtoul([v1 UTF8String],0,16);  //16进制字符串转换成int
            int version2 = (int)strtoul([v2 UTF8String],0,16);  //16进制字符串转换成int
            int version3 = (int)strtoul([v3 UTF8String],0,16);  //16进制字符串转换成int
            int version4 = (int)strtoul([v4 UTF8String],0,16);  //16进制字符串转换成int
            
            self.currentVersion = [NSString stringWithFormat:@"%d.%d.%d.%d",version1, version2 ,version3, version4];
        }
        
        NSLog(@"有无SD卡 structDevInfo->total:%d structDevInfo->free:%d  structDevInfo->version:%d 16进制版本号:%@  设备版本号：%@", structDevInfo->total, structDevInfo->free, structDevInfo->version, version, self.currentVersion);

    } else if (type == IOTYPE_USER_IPCAM_SET_UPGRADEONLIN_RESP) {///设备版本号
        self.getDeviceVersionSuccessful = YES;
        
        SMsgAVIoctrlUpgradeOnlineResp *s = (SMsgAVIoctrlUpgradeOnlineResp*)data;
        
        self.currentVersion = [NSString stringWithFormat:@"%s",s->current_sys_version];
        self.lastVersion = [NSString stringWithFormat:@"%s",s->latest_sys_version];
        
        NSLog(@"设备版本号 s->current_ui_version:%s, s->current_sys_version:%s, s->latest_ui_version:%s, s->latest_sys_version:%s", s->current_ui_version, s->current_sys_version, s->latest_ui_version, s->latest_sys_version);

//        if (s->type == 0) {
//            [self sendUpgrade];
//        }
        
    }else if (type == IOTYPE_USER_IPCAM_LISTWIFIAP_RESP) {///wifi列表
        
        self.getDeviceWiFiListSuccessful = YES;
        
        SMsgAVIoctrlListWifiApResp *p = (SMsgAVIoctrlListWifiApResp *)data;

        NSMutableArray * array = [[NSMutableArray alloc] init];

        if (p->number <= 0) {

        }else{
            
            NSLog(@"获取的wifi列表信息 p->number:%d", p->number);


            for (int i = 0; i < p->number; ++i) {

                SWifiAp ap = p->stWifiAp[i];

                NSLog(@"获取的wifi列表信息 ap.ssid:%s, ap.status:%d, ap.signal:%d, ap.mode:%d, ap.enctype:%d", ap.ssid, ap.status, ap.signal, ap.mode, ap.enctype);

                NSString * ssid = [[NSString alloc] initWithCString:ap.ssid encoding:NSUTF8StringEncoding];
                
                if (![ssid isEqualToString:@"Unknown"] && ssid.length) {

//                     JKWiFiModel * model = [[JKWiFiModel alloc] init];
//                     model.ssid = ssid;
//                     model.status = [[NSString alloc] initWithFormat:@"%c",ap.status];
//                     model.signal = [[NSString alloc] initWithFormat:@"%c",ap.signal];
//                     model.mode = ap.mode;
//                     model.enctype = ap.enctype;
//
//                    if (ap.status == 1) {
//
//                        self.getDeviceWiFiInfoSuccessful = YES;
//
//                        self.deviceWiFiSSID = ssid;
//
////                        self.deviceWiFiPassword = [NSString stringWithFormat:@"%s",s->password];
//
//                        //NSLog(@"获取的wifi信息 self.deviceWiFiSSID:%@", self.deviceWiFiSSID);
//
//                    }
//                    NSValue *model = [NSValue valueWithBytes:&ap objCType:@encode(struct SWifiAp)];
                    
                    NSValue *model = [NSValue valueWithBytes:&ap objCType:@encode(SWifiAp)];
                    
                    [array addObject:model];
                }
            }
        }
        self.wifiList = array;
        
    } else if (type == IOTYPE_USER_IPCAM_GETSTREAMCTRL_RESP) {//视频质量
        
        SMsgAVIoctrlGetStreamCtrlResp *s = (SMsgAVIoctrlGetStreamCtrlResp*) data;
        self.currenQuality = s->quality;
        self.getCurrenQualitySuccessful = YES;
        NSLog(@"获取视频质量 self.currenQuality:%ld", (long)self.currenQuality);

    } else if (type == IOTYPE_USER_IPCAM_SETSTREAMCTRL_RESP) {//
        
        SMsgAVIoctrlSetStreamCtrlResp *s = (SMsgAVIoctrlSetStreamCtrlResp*) data;

        NSLog(@"设置视频质量 s->result:%ld", (long)s->result);
        if (s->result == 0) {
            
        }else {
            self.getCurrenQualitySuccessful = NO;
        }

    } else if(type == IOTYPE_USER_IPCAM_GET_VIDEOMODE_RESP){//翻转情况
        
        SMsgAVIoctrlGetVideoModeResp *s = (SMsgAVIoctrlGetVideoModeResp*)data;
        
        self.mirroring = s->mode;
        self.getMirroringSuccessful = YES;
        
        NSLog(@"获取视频翻转情况 self.mode:%ld", (long)self.mirroring);
    
    } else if(type == IOTYPE_USER_IPCAM_SET_VIDEOMODE_RESP){//翻转情况
        
        SMsgAVIoctrlSetVideoModeResp *s = (SMsgAVIoctrlSetVideoModeResp*)data;
        if (s->result == 0) {

        }else {
            self.getMirroringSuccessful = NO;
            
        }
        [self getDeviceVideoFlip];
        NSLog(@"设置视频翻转情况 result:%ld", (long)s->result);

    } else if(type == IOTYPE_USER_IPCAM_SET_IRLED_RESP){
        SIRLedCtrl *s = (SIRLedCtrl*)data;
        
        self.irLedAuto = s->isAuto;
        self.irLedLevel = s->ledLevel;
 
        NSLog(@"设备夜视状态 s->isAuto:%d, s->ledLevel:%d", s->isAuto, s->ledLevel);
        
    }else if (type == IOTYPE_USER_IPCAM_THIRDPART_SETTING_RESP) {//指示灯状态
        SMsgAVIoctrlThirdpartResp *s = (SMsgAVIoctrlThirdpartResp*)data;
        
        NSLog(@"设备指示灯 s->command_types_:%d, s->result_:%d, s->value_:%d",s->command_types_, s->result_, s->value_);
        if (s->result_ == 0) {
            self.getPilotLampSuccessful = YES;
            self.pilotLamp = s->value_;
        }else {
            self.getPilotLampSuccessful = NO;
        }
        
    }
    else if (type == IOTYPE_USER_IPCAM_GETWIFI_RESP){///wifi信息

        SMsgAVIoctrlGetWifiResp *s = (SMsgAVIoctrlGetWifiResp *)data;
        
        self.deviceWiFiSSID = [NSString stringWithFormat:@"%s",s->ssid];
        self.deviceWiFiPassword = [NSString stringWithFormat:@"%s",s->password];

        self.getDeviceWiFiInfoSuccessful = YES;
        
        NSLog(@"获取的wifi信息 s->ssid:%s, s->password:%s", s->ssid, s->password);

    }else if (type == IOTYPE_USER_SET_CHILDREN_LOCK_RESP) {///设置童锁
        /*
         typedef struct
         {
             int result;         // 0: success; otherwise: failed.
              char lockEnable;                 // 0：关闭；1：开启；
             char reserved[4];
         }SMsgAVIoctrlSetLockResp, SMsgAVIoctrlGetLockResp;

         */
        SMsgAVIoctrlSetLockResp *s = (SMsgAVIoctrlSetLockResp *)data;
    
        if (s->result == 0) {
            self.getChildrenLockSuccessful = YES;
            self.childrenLock = s->lockEnable;
        }else {
            self.getChildrenLockSuccessful = NO;
        }
    
        NSLog(@"设置童锁 s->result:%d, s->lockEnable:%d", s->result, s->lockEnable);
        
    }else if (type == IOTYPE_USER_GET_CHILDREN_LOCK_RESP) {///获取童锁
        
        SMsgAVIoctrlGetLockResp *s = (SMsgAVIoctrlGetLockResp *)data;
    
        if (s->result == 0) {
            self.getChildrenLockSuccessful = YES;
            self.childrenLock = s->lockEnable;
        }else {
            self.getChildrenLockSuccessful = NO;
        }
        
        NSLog(@"获取童锁 s->result:%d, s->lockEnable:%d", s->result, s->lockEnable);
        
    }else if (type == IOTYPE_USER_IPCAM_GET_VIDEOOSD_RESP) {///获取OSD
        
        SMsgAVIoctrlGetVideoOSDResp *s = ( SMsgAVIoctrlGetVideoOSDResp *)data;
    
        self.getShowOSDSuccessful = YES;
        self.showOSD = s->osdEnable;
  
        
        NSLog(@"获取OSD s->osdEnable:%d", s->osdEnable);
        
    }else if (type == IOTYPE_USER_IPCAM_SET_VIDEOOSD_RESP) {///设置OSD

        SMsgAVIoctrlSetVideoOSDResp *s = (SMsgAVIoctrlSetVideoOSDResp *)data;
    
        if (s->result == 0) {
            self.getShowOSDSuccessful = YES;
        }else {
            self.getShowOSDSuccessful = NO;
        }
    
        NSLog(@"设置OSD s->result:%d", s->result);
        
    }else if (type == IOTYPE_USER_IPCAM_TRANSFER_TTY_DATA_RESP) {
        SmsgAVIoctrlTtyDataResp *s = (SMsgAVIoctrlSetVideoOSDResp *)data;
        NSLog(@"手动喂食返回结果 s->result:%d", s->result);
    }
    
    NSLog(@"camere代理返回数据 命令号：%ld",(long)type);
    
    NSLog(@"camere代理返回数据 命令号：%lu",type);
    
    if (self.cameraDelegate && [self.cameraDelegate respondsToSelector:@selector(JKCameraModel:didReceiveIOCtrlWithType:Data:DataSize:)]) {
        [self.cameraDelegate JKCameraModel:self didReceiveIOCtrlWithType:type Data:data DataSize:size];
    }
}
- (void)camera:(Camera *)camera didReceiveFrameInfoWithVideoWidth:(NSInteger)videoWidth VideoHeight:(NSInteger)videoHeight VideoFPS:(NSInteger)fps VideoBPS:(NSInteger)videoBps AudioBPS:(NSInteger)audioBps OnlineNm:(NSInteger)onlineNm FrameCount:(unsigned long)frameCount IncompleteFrameCount:(unsigned long)incompleteFrameCount{
    
//    NSLog(@"onlineNm = %ld", (long)onlineNm);
    
    if (self.cameraDelegate && [self.cameraDelegate respondsToSelector:@selector(JKCameraModel:didReceiveFrameInfoWithVideoWidth:VideoHeight:VideoFPS:VideoBPS:AudioBPS:OnlineNm:FrameCount:IncompleteFrameCount:)]) {
        [self.cameraDelegate JKCameraModel:self didReceiveFrameInfoWithVideoWidth:videoWidth VideoHeight:videoHeight VideoFPS:fps VideoBPS:videoBps AudioBPS:audioBps OnlineNm:onlineNm FrameCount:frameCount IncompleteFrameCount:incompleteFrameCount];
    }
    
}
- (void)camera:(Camera *)camera didReceiveRawDataFrame:(const char *)imgData VideoWidth:(NSInteger)width VideoHeight:(NSInteger)height{

    if (self.cameraDelegate && [self.cameraDelegate respondsToSelector:@selector(JKCameraModel:didReceiveRawDataFrame:VideoWidth:VideoHeight:)]) {
        [self.cameraDelegate JKCameraModel:self didReceiveRawDataFrame:imgData VideoWidth:width VideoHeight:height];
    }
}
#pragma mark ===============音频buffer===============
- (void)camera:(Camera *)camera didReceiveAudioBytesWithDataBuffer:(unsigned char *)dataBuffer withLength: (unsigned int)aLength {

    if (dataBuffer) {
        if (self.recording) {
            if(self->myLocalRecorder)
            {
                [self->myLocalRecorder setAudioData:dataBuffer length:aLength];
            }
        }
    }
    
    if (self.cameraDelegate && [self.cameraDelegate respondsToSelector:@selector(JKCameraModel:didReceiveAudioBytesWithDataBuffer:withLength:)]) {
        [self.cameraDelegate JKCameraModel:self didReceiveAudioBytesWithDataBuffer:dataBuffer withLength:aLength];
    }
}
#pragma mark ===============视频buffer===============
- (void)camera:(Camera *)camera didReceiveVideoBytesWithDataBuffer:(unsigned char *)dataBuffer withLength:(unsigned int)aLength{

    self.playing = YES;

    if (self.encryptionFormat == ENCRYPTION_FORMAT_H264) {

    }else if (self.encryptionFormat == ENCRYPTION_FORMAT_H265) {
        @autoreleasepool {
            if (aLength > 0) {
                H265Decode(dataBuffer, aLength);
            }
        }
    }
    if (self.cameraDelegate && [self.cameraDelegate respondsToSelector:@selector(JKCameraModel:didReceiveVideoBytesWithDataBuffer:withLength:)]) {
        [self.cameraDelegate JKCameraModel:self didReceiveVideoBytesWithDataBuffer:dataBuffer withLength:aLength];
    }
}
#pragma mark ===============H264解码后的bufferRef(底层已经做了解码，上层不用再次解码，直接拿来渲染)===============
- (void)camera:(Camera *)camera didReceiveVideoBytesWithHW264ImageBufferRef:(CVImageBufferRef)imageBufferRef {
    
    if (self.encryptionFormat == ENCRYPTION_FORMAT_H264) {
        
        @autoreleasepool {
            
            CIImage *ciImage = [CIImage imageWithCVPixelBuffer:imageBufferRef];
            CIContext *temporaryContext = [CIContext contextWithOptions:nil];
            CGImageRef videoImage = [temporaryContext createCGImage:ciImage fromRect:CGRectMake(0, 0, CVPixelBufferGetWidth(imageBufferRef), CVPixelBufferGetHeight(imageBufferRef))];
            UIImage * image = [[UIImage alloc] initWithCGImage:videoImage];

            CGImageRelease(videoImage);
            CVPixelBufferRelease(imageBufferRef);
         
            dispatch_async(dispatch_get_main_queue(), ^{
           
                self.videoMonitor.image = image;
                
            });

            if (self.recording) {
                
                if(myLocalRecorder)
                {
                    if (NO == myLocalRecorder.startRecordFlag) {

                        self.fileName = [NSString stringWithFormat:@"%f", [[NSDate date] timeIntervalSince1970]];

                        if (self.fileName) {

                            NSInteger sampleRate = 8000;
                            NSInteger channel = 1; // 1:单声道；2:立体声
                            NSInteger bitRate = 16;
                            [myLocalRecorder startRecordRawAndAudio:self.fileName VideoWidth:image.size.width VideoHeight:image.size.height AudioSampleRate:sampleRate AudioChannel:channel AudioBitRate:bitRate];
                            
                            [myLocalRecorder startRecordImage:image];
                        }
                    }
                    [myLocalRecorder startRecordImage:image];
                }
            }
        }
    }
}
#pragma mark ===============流解析中增加返回时间戳，用于显示水印（由于竖屏水印只能竖着，故由App做水印渲染）===============
- (void)camera:(Camera *)camera didReceiveVideoBytesWithDataBuffer:(unsigned char *)dataBuffer withLength:(unsigned int)aLength withTimestamp:(unsigned long)timestamp {
    
    if(self.cameraDelegate && [self.cameraDelegate respondsToSelector:@selector(JKCameraModel:didReceiveVideoBytesWithDataBuffer:withLength:withTimestamp:)]) {
        [self.cameraDelegate JKCameraModel:self didReceiveVideoBytesWithDataBuffer:dataBuffer withLength:aLength withTimestamp:timestamp - self.phoneZeroTimeZone];
    }

}
#pragma mark ===============视频buffer及编码格式===============
- (void)camera:(Camera *)camera didReceiveVideoBytesWithDataBuffer:(unsigned char *)dataBuffer withLength:(unsigned int)aLength videoCodecID:(NSInteger)codecID {
    /*
     MEDIA_CODEC_UNKNOWN            = 0x00,
     MEDIA_CODEC_VIDEO_MPEG4        = 0x4C,
     MEDIA_CODEC_VIDEO_H263        = 0x4D,
     MEDIA_CODEC_VIDEO_H264        = 0x4E,
     MEDIA_CODEC_VIDEO_MJPEG        = 0x4F,
     MEDIA_CODEC_VIDEO_H265      = 0x50,
     */
    
//    NSLog(@"编码格式 codecID = %d", (int)codecID);
    
    if (codecID == MEDIA_CODEC_VIDEO_H264) {
        self.encryptionFormat = ENCRYPTION_FORMAT_H264;
    }else if (codecID == MEDIA_CODEC_VIDEO_H265) {
        self.encryptionFormat = ENCRYPTION_FORMAT_H265;
    }else {
        self.encryptionFormat = ENCRYPTION_FORMAT_NONE;
    }
}
#pragma mark ===============JKFFmpegH265DecoderDelegate===============
- (void)ffmpegH265Decoder:(JKFFmpegH265Decoder *)decoder decodeImage:(UIImage *)img {
//    NSLog(@"解码成功");
    dispatch_async(dispatch_get_main_queue(), ^{
        self.videoMonitor.image = img;
    });

    if (self.recording) {
        if(myLocalRecorder) {
            if (NO == myLocalRecorder.startRecordFlag) {

                self.fileName = [NSString stringWithFormat:@"%f", [[NSDate date] timeIntervalSince1970]];

                if (self.fileName) {

                    NSInteger sampleRate = 8000;
                    NSInteger channel = 1; // 1:单声道；2:立体声
                    NSInteger bitRate = 16;
                    [myLocalRecorder startRecordRawAndAudio:self.fileName VideoWidth:img.size.width VideoHeight:img.size.height AudioSampleRate:sampleRate AudioChannel:channel AudioBitRate:bitRate];
                    
                    [myLocalRecorder startRecordImage:img];
                }
            }
            [myLocalRecorder startRecordImage:img];
        }
    }
}

#pragma mark - Public Methods

- (NSArray *)getSupportedStreams
{
    return [self.arrayStreamChannel count] == 0 ? nil : [[NSArray alloc] initWithArray:self.arrayStreamChannel];
}

- (BOOL)getAudioInSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 1) == 0;
}

- (BOOL)getAudioOutSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 2) == 0;
}

- (BOOL)getPanTiltSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 4) == 0;
}

- (BOOL)getEventListSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 8) == 0;
}

- (BOOL)getPlaybackSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 16) == 0;
}

- (BOOL)getWiFiSettingSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 32) == 0;
}

- (BOOL)getMotionDetectionSettingSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 64) == 0;
}

- (BOOL)getRecordSettingSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 128) == 0;
}

- (BOOL)getFormatSDCardSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 256) == 0;
}

- (BOOL)getVideoFlipSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 512) == 0;
}

- (BOOL)getEnvironmentModeSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 1024) == 0;
}

- (BOOL)getMultiStreamSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 2048) == 0;
}

- (NSInteger)getAudioOutFormatOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 4096) == 0 ? MEDIA_CODEC_AUDIO_SPEEX : MEDIA_CODEC_AUDIO_ADPCM;
}

- (BOOL)getVideoQualitySettingSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 8192) == 0;
}

- (BOOL)getDeviceInfoSupportOfChannel:(NSInteger)channel
{
    return ([self getServiceTypeOfChannel:channel] & 16384) == 0;
}

- (BOOL)getDeviceUpgradeOnlineSupportOfChannel:(NSInteger)channel
{
    //18
    return (([self getServiceTypeOfChannel:channel] & (1<<18)) > 0);
}

- (BOOL)getDevicePTZSupportOfChannel:(NSInteger)channel
{
    //19
    return (([self getServiceTypeOfChannel:channel] & (1<<19)) > 0);
}

- (BOOL)getDeviceRestorySupportOfChannel:(NSInteger)channel
{
    //20
    return (([self getServiceTypeOfChannel:channel] & (1<<20)) > 0);
}

- (BOOL)getDeviceRebootSupportOfChannel:(NSInteger)channel
{
    //21
    return (([self getServiceTypeOfChannel:channel] & (1<<21)) > 0);
}

- (BOOL)getDeviceIRCutSupportOfChannel:(NSInteger)channel
{
    //22
    return (([self getServiceTypeOfChannel:channel] & (1<<22)) > 0);
}

- (BOOL)getDeviceArmSupportOfChannel:(NSInteger)channel
{
    //23
    return (([self getServiceTypeOfChannel:channel] & (1<<23)) > 0);
}

- (BOOL)getDeviceWarnSupportOfChannel:(NSInteger)channel
{
    //24
    return (([self getServiceTypeOfChannel:channel] & (1<<24)) > 0);
}

- (BOOL)getPWDeviceLowProfileSupportOfChannel:(NSInteger)channel
{
    //27
    return (([self getServiceTypeOfChannel:channel] & (1<<27)) > 0);
}

#pragma mark =============== 监听耳机拔插 、 蓝牙耳机连接与断开 等===============
- (void)audioRouteChangeListenerCallback:(NSNotification*)notification {

    NSDictionary *interuptionDict = notification.userInfo;

    NSInteger routeChangeReason = [[interuptionDict valueForKey:AVAudioSessionRouteChangeReasonKey] integerValue];
 
    
    //NSLog(@"耳机连接与断开回调:%d",routeChangeReason);

    switch (routeChangeReason) {

        case AVAudioSessionRouteChangeReasonNewDeviceAvailable:{//插入耳机时

            //NSLog(@"耳机插入");
            if (self.listening) {
                [self stopSoundToPhone:self.lastChannel];
                
                double delayInSeconds = 500.0;
                dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_MSEC));
                dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
 
                    [self startSoundToPhone:self.lastChannel];
                  
                });
            }else {
                
            }
            if (self.talking) {
                
                [self stopSoundToDevice:self.lastChannel];
                
                double delayInSeconds = 500.0;
                dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_MSEC));
                dispatch_after(popTime, dispatch_get_main_queue(), ^(void){

                    [self startSoundToDevice:self.lastChannel];
                });
            }else {
                
            }
            
            dispatch_async(dispatch_get_main_queue(), ^{
                self.audioOutputMethod = 1;
                NSError *nserror = nil;
                AVAudioSession* sysSession = [AVAudioSession sharedInstance];
                [sysSession setCategory:AVAudioSessionCategoryPlayAndRecord error:&nserror];
            });
        }
            break;

        case AVAudioSessionRouteChangeReasonOldDeviceUnavailable:{//拔出耳机时

            //NSLog(@"耳机拔出");
            
            if (self.listening) {
                [self stopSoundToPhone:self.lastChannel];
                
                double delayInSeconds = 500.0;
                dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_MSEC));
                dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
                    if (self.twoWayVoice) {
                        [self startSoundToPhoneForEcho:self.lastChannel];
                    }else {
                        [self startSoundToPhone:self.lastChannel];
                    }
                    
                    
                });
            }else {
                
            }
            
            if (self.talking) {
                [self stopSoundToDevice:self.lastChannel];
                
                double delayInSeconds = 500.0;
                dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_MSEC));
                dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
                    //NSLog(@"对讲开启消回音");
                   
                    if (self.twoWayVoice) {
                        [self startSoundToDeviceForEcho:self.lastChannel];
                    }else {
                        [self startSoundToDevice:self.lastChannel];
                    }
                
                });
            }else {
                
            }

            dispatch_async(dispatch_get_main_queue(), ^{
                self.audioOutputMethod = 0;
                NSError *nserror = nil;
                AVAudioSession* sysSession = [AVAudioSession sharedInstance];

                [sysSession setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionDefaultToSpeaker error:&nserror];
            });
        }
            break;

        default:
            break;

    }
    [self isReceiverOrSpeaker];
}

- (void)isReceiverOrSpeaker {
    
    AVAudioSession *audioSession = [AVAudioSession sharedInstance];

    AVAudioSessionRouteDescription *currentRoute = [audioSession currentRoute];

    for (AVAudioSessionPortDescription *output in currentRoute.outputs) {

        //NSLog(@"output.portType = %@",output.portType);


        if ([[output portType] isEqualToString:AVAudioSessionPortHeadphones]) {
            //NSLog(@"有线耳机输出");
            self.audioOutputMethod = 1;


        }
        if ([[output portType] isEqualToString:AVAudioSessionPortBluetoothHFP] ||
            [[output portType] isEqualToString:AVAudioSessionPortBluetoothA2DP]) {
            //NSLog(@"蓝牙耳机输出");
            self.audioOutputMethod = 2;

        }
        
        if ([[output portType] isEqualToString:AVAudioSessionPortBuiltInReceiver]) {

        }
    }
    //NSLog(@"扬声器输出");
    self.audioOutputMethod = 0;


}

+ (void)IOTC_Setup_Session_Alive_Timeout_ForJKCamera:(NSUInteger)timeout {
    
    IOTC_Setup_Session_Alive_Timeout((unsigned int)timeout);

}

/**
 十六进制转换为二进制
   
 @param hex 十六进制数
 @return 二进制数
 */
+ (NSString *)getBinaryByHex:(NSString *)hex {
    
    NSMutableDictionary *hexDic = [[NSMutableDictionary alloc] initWithCapacity:16];
    [hexDic setObject:@"0000" forKey:@"0"];
    [hexDic setObject:@"0001" forKey:@"1"];
    [hexDic setObject:@"0010" forKey:@"2"];
    [hexDic setObject:@"0011" forKey:@"3"];
    [hexDic setObject:@"0100" forKey:@"4"];
    [hexDic setObject:@"0101" forKey:@"5"];
    [hexDic setObject:@"0110" forKey:@"6"];
    [hexDic setObject:@"0111" forKey:@"7"];
    [hexDic setObject:@"1000" forKey:@"8"];
    [hexDic setObject:@"1001" forKey:@"9"];
    [hexDic setObject:@"1010" forKey:@"A"];
    [hexDic setObject:@"1011" forKey:@"B"];
    [hexDic setObject:@"1100" forKey:@"C"];
    [hexDic setObject:@"1101" forKey:@"D"];
    [hexDic setObject:@"1110" forKey:@"E"];
    [hexDic setObject:@"1111" forKey:@"F"];
    
    NSString *binary = @"";
    for (int i=0; i<[hex length]; i++) {
        
        NSString *key = [hex substringWithRange:NSMakeRange(i, 1)];
        NSString *value = [hexDic objectForKey:key.uppercaseString];
        if (value) {
            
            binary = [binary stringByAppendingString:value];
        }
    }
    return binary;
}

- (void)dealloc {
 
}

@end
