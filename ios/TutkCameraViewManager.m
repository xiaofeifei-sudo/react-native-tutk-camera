
#import "TutkCameraViewManager.h"

@interface TutkCameraViewManager ()<JKCameraModelDelegate>
@property (strong, nonatomic)JKCameraModel *cameraModel;
@property (strong, nonatomic)UIView *playerBgView;
@property (nonatomic, assign) NSInteger width;
@property (strong, nonatomic)UILabel *statusLabel;

@end

@implementation TutkCameraViewManager


@synthesize bridge = _bridge;

- (dispatch_queue_t)methodQueue
{
    return dispatch_get_main_queue();
}

+ (BOOL)requiresMainQueueSetup
{
    return YES;
}

RCT_EXPORT_MODULE()

- (UIView *)view
{
  return [[UIView alloc] init];
}

#pragma mark ===============重新连接===============
- (void)disConnect {

    dispatch_queue_t queue = dispatch_queue_create("disConnect", NULL);
    dispatch_async(queue, ^{
        [self.cameraModel myDisconnect];
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.cameraModel.videoMonitor removeFromSuperview];
            NSLog(@"设备离线");
        });
        usleep(0.5*1000*1000);
        [self.cameraModel connectStatus];
    });
}


- (void)JKCameraModel:(JKCameraModel *)cameraModel didChangeChannelStatus:(NSInteger)channel ChannelStatus:(NSInteger)status {
    if (![cameraModel.devid isEqualToString:self.cameraModel.devid]) {
        return;
    }
    if (cameraModel.wrongPassword) {
        dispatch_async(dispatch_get_main_queue(), ^{
//            self.statusLabel.text = @"密码错误";
            NSLog(@"密码错误");
        });
    }else {
        switch ([cameraModel getConnectStatus]) {
            case ONLINE:{
                dispatch_async(dispatch_get_main_queue(), ^{
                    [self.cameraModel startShowWithChannel:self.cameraModel.lastChannel];
                    
//                    [self changeLed];
                    
//                    self.statusLabel.text = @"在线";
                    NSLog(@"设备在线");

                    self.cameraModel.videoMonitor.frame = CGRectMake(0, 0, self.playerBgView.frame.size.width, self.playerBgView.frame.size.height);
                    [self.playerBgView addSubview:self.cameraModel.videoMonitor];
                    
//                    [self.cameraModel getDeviceFeedPlanListIsNewMethod:YES];
//                    [self.cameraModel getDeviceTimeZone];
//                    [self.cameraModel getDeviceVideoQuality];
//                    [self.cameraModel getDeviceLedStatus];
//                    [self.cameraModel getDeviceTFInfo];
                    [self.cameraModel getDeviceFeedPlanListIsNewMethod:1];
//                    [self.cameraModel getDevicePushAddress];
                    
                    NSMutableArray *array = [NSMutableArray new];
                    for (int i = 1; i < 7; i++) {
                        JKFeedModel *model = [JKFeedModel new];
                        model.index = [NSString stringWithFormat:@"%d", i];
                        model.feedweight = @"0";
                        model.hour = 0;
                        model.minute = 0;
                        model.gofeed = @"0";
                        model.feedYear = -91;
                        model.feedMonth = -89;
                        model.feedDay = 0x7f;
                        model.feedtype = @"1";
                        model.lattic = @"1";
                        model.isMealInfoChanged = 1;
                        if (i == 1) {
                            model.feedname = @"Breakfast";
                        }else if (i == 2) {
                            model.feedname = @"Lunch";
                        }else if (i == 3) {
                            model.feedname = @"Dinner";
                        }else if (i == 4) {
                            model.feedname = @"Fourth Meal";
                        }else if (i == 5) {
                            model.feedname = @"Fifth Meal";
                        }else {
                            model.feedname = @"Sixth Meal";
                        }
                        
                        [array addObject:model];
                    }
//                    [self.cameraModel sendAutoFeedingIsNewMethod:array];
                });
            }
                break;
            case OFFLINE:{
                dispatch_async(dispatch_get_main_queue(), ^{
//                    self.statusLabel.text = @"离线";
                    NSLog(@"设备已离线");
                });
            }
                break;
            case CONNECTING:{
                dispatch_async(dispatch_get_main_queue(), ^{
//                    self.statusLabel.text = @"连接中";
                    NSLog(@"设备连接中...");
                });
            }
                break;
                
            default:
                break;
        }
    }
}


#pragma mark ===============开始连接===============
- (void)startConnect {
    
    CGSize size = [UIScreen mainScreen].bounds.size;
    NSLog(@"开始连接");
    NSLog(@"屏幕大小: %@", NSStringFromCGSize(size));
    
    //保存uid和连接密码
//    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
//    [defaults setValue:self.uidTextField.text forKey:@"uid"];
//    [defaults setValue:self.pwdTextField.text forKey:@"pwd"];
    
    if (self.cameraModel) {
        [self.cameraModel myDisconnect];
        [self.cameraModel.videoMonitor removeFromSuperview];
    }
    self.cameraModel = [[JKCameraModel alloc] initWithName:@"camera" Password:@"HxkyFdVtlA"];
    self.cameraModel.devid = @"V99DXG55SN5VK13S111A";
    self.cameraModel.cameraDelegate = self;
    [self.cameraModel connectStatus];
    
}



- (void)JKCameraModel:(JKCameraModel *)cameraModel didReceiveIOCtrlWithType:(NSInteger)type Data:(const char *)data DataSize:(NSInteger)size {

}

- (void)JKCameraModel:(JKCameraModel *)camera didReceiveVideoBytesWithDataBuffer:(unsigned char *)dataBuffer withLength:(unsigned int)aLength {
    
    
}



RCT_CUSTOM_VIEW_PROPERTY(color, NSString, UIView)
{
//    CGFloat width = [UIScreen mainScreen].bounds.size.width;
//    self.statusLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 10, width, 80)];
//    self.statusLabel.textAlignment = NSTextAlignmentCenter;
//    [view addSubview:self.statusLabel];
//    self.statusLabel.text = @"离线";
    if (json == nil) return;

    
    
//  [view setBackgroundColor:[self hexStringToColor:json]];
}


RCT_CUSTOM_VIEW_PROPERTY(videoWidth, NSInteger, UIView)
{
    if (json == nil) return;
    NSInteger width = [RCTConvert NSInteger:json];
    NSLog(@"video宽度===>>> %ld", width);
    self.playerBgView = [[UIView alloc] initWithFrame:CGRectMake(0, 100, width, width/16.0*9.0)];
    self.playerBgView.backgroundColor = [UIColor blackColor];
    [view addSubview:self.playerBgView];
    
//    [self startConnect]; 模拟开始连接
}



//连接设备
RCT_EXPORT_METHOD(connectDevice:(NSString *)message
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject){
    NSLog(@"连接设备");
    
    [self startConnect];
    
    resolve(@{@"result": @"success"});
}



RCT_EXPORT_METHOD(disConnectDevice:(NSString *)message
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject){
    NSLog(@"断开设备连接");
    
    [self disConnect];
    
    resolve(@{@"result": @"success"});
}






//- (void)setWidth:(NSInteger)width {
//
//    self.playerBgView = [[UIView alloc] initWithFrame:CGRectMake(0, 100, width, width/16.0*0.9)];
//    self.playerBgView.backgroundColor = [UIColor blackColor];
//
//    [self.view addSubview:self.playerBgView];
//}


- hexStringToColor:(NSString *)stringToConvert
{
  NSString *noHashString = [stringToConvert stringByReplacingOccurrencesOfString:@"#" withString:@""];
  NSScanner *stringScanner = [NSScanner scannerWithString:noHashString];

  unsigned hex;
  if (![stringScanner scanHexInt:&hex]) return nil;
  int r = (hex >> 16) & 0xFF;
  int g = (hex >> 8) & 0xFF;
  int b = (hex) & 0xFF;

  return [UIColor colorWithRed:r / 255.0f green:g / 255.0f blue:b / 255.0f alpha:1.0f];
}

@end
