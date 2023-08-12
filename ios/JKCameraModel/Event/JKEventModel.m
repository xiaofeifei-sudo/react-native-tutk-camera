//
//  JKEventModel.h
//  demo
//
//  Created by mac on 2021/9/15.
//  Copyright © 2021 mac. All rights reserved.
//

#import <CoreFoundation/CFUUID.h>
#import "JKEventModel.h"

@implementation JKEventModel

+ (NSString *)getEventTypeName:(int)eventType {
    
    NSMutableString *result = [NSMutableString string];
    
    switch (eventType) {
        case AVIOCTRL_EVENT_ALL:
            [result appendString:NSLocalizedString(@"Full-time recording", @"")];
            break;
            
        case AVIOCTRL_EVENT_EXPT_REBOOT:
            [result appendString:NSLocalizedString(@"Reboot", @"")];
            break;
            
        case AVIOCTRL_EVENT_IOALARM:
            [result appendString:NSLocalizedString(@"Alarm record", @"")];
            break;
            
        case AVIOCTRL_EVENT_IOALARMPASS:
            break;
            
        case AVIOCTRL_EVENT_MOTIONDECT:
            [result appendString:NSLocalizedString(@"Motion Detection", @"")];
            break;
            
        case AVIOCTRL_EVENT_MOTIONPASS:
            break;
            
        case AVIOCTRL_EVENT_SDFAULT:
            [result appendString:NSLocalizedString(@"SDCard Fault", @"")];
            break;
            
        case AVIOCTRL_EVENT_VIDEOLOST:
            [result appendString:NSLocalizedString(@"Video Lost", @"")];
            break;
            
        case AVIOCTRL_EVENT_VIDEORESUME:
            [result appendString:NSLocalizedString(@"Video Resume", @"")];
            break;
            
        case USER_EVENT_DOOR_BELL:
            [result appendString:NSLocalizedString(@"Door Bell", @"")];
            break;
            
        case USER_EVENT_ALARM_INFRARED:
            [result appendString:NSLocalizedString(@"Infrared", @"")];
            break;
            
        case USER_EVENT_ALARM_SMOKING:
            [result appendString:NSLocalizedString(@"Smoke Sensor", @"")];
            break;
            
        case USER_EVENT_ALARM_AIR:
            [result appendString:NSLocalizedString(@"Gas Sensor", @"")];
            break;
            
        case USER_EVENT_ALARM_REMOTE:
            [result appendString:NSLocalizedString(@"Remote Control", @"")];
            break;
            
        case USER_EVENT_ALARM_DOOR_WINDOW:
            [result appendString:NSLocalizedString(@"Door Sensor", @"")];
            break;
            
        case USER_EVENT_ALARM_WHISTLE:
            [result appendString:NSLocalizedString(@"Siren", @"")];
            break;

        case USER_EVENT_ALARM_ARMED:
            [result appendString:NSLocalizedString(@"Arm", @"")];
            break;
            
        case USER_EVENT_ALARM_DISARM:
            [result appendString:NSLocalizedString(@"Disarm", @"")];
            break;
            
        case USER_EVENT_PIR_WARNING:
            [result appendString:NSLocalizedString(@"Infrared Alarm", @"")];
            break;
            
        case USER_EVENT_ALARM_SWITCH:
            [result appendString:NSLocalizedString(@"Switch", @"")];
            break;
            
        case USER_EVENT_FEED_PETS_TIMER_FEED:           // for pets  timer feed success
            [result appendString:NSLocalizedString(@"Programmed Feeding", @"")];
            break;
        case USER_EVENT_FEED_PETS_MANUL_FEED:           // for pets  manul feed success
            [result appendString:NSLocalizedString(@"Manual Feeding", @"")];
            break;
        case USER_EVENT_FEED_PETS_FEED_WARNING:         // for pets device out food  failed warning

            [result appendString:NSLocalizedString(@"Dispense excessive food", @"")];

            break;
        case USER_EVENT_FEED_PETS_NO_FOOD_WARING:       // for pets alarm food warning
            [result appendString:NSLocalizedString(@"No Food", @"")];
            break;
        case USER_EVENT_FEED_PETS_OUT_FOOD_WARING:    // for pets feed failed

            [result appendString:NSLocalizedString(@"Device is abnormal", @"")];
 
            break;
        case USER_EVENT_SAFEBOX_DOOR_OPENED:       // for safebox door opened
            [result appendString:NSLocalizedString(@"Door Opened", @"")];
            break;
        case USER_EVENT_SAFEBOX_DOOR_ERROR:       // for safebox door error
            [result appendString:NSLocalizedString(@"Anti-theft Alarmed", @"")];
            break;
        case USER_EVENT_SAFEBOX_HOSTAGE:
            [result appendString:NSLocalizedString(@"Hijack alarm", @"")];
            break;
            
        case USER_EVENT_P2P_ONLIE:
            [result appendString:NSLocalizedString(@"Online device", @"")];
            break;
        case USER_EVENT_P2P_OFFLINE:
            [result appendString:NSLocalizedString(@"Offline device", @"")];
            break;
            
        case USER_EVENT_ARMED_DOOR_MOVED:
            [result appendString:NSLocalizedString(@"Dismantle alarm", @"")];
            break;
            
        case USER_EVENT_PETWANT_PIR_DETECT:
            [result appendString:NSLocalizedString(@"Infared Detection", @"")];
            break;
        case USER_EVENT_LOW_POWER:
            [result appendString:NSLocalizedString(@"Battery Low Power", @"")];

            break;
            
        case USER_EVENT_ALARM_GAS:
            [result appendString:NSLocalizedString(@"Gas Sensor", @"")];

            break;
        case USER_EVENT_ALARM_DOOR_LOWVOL:
            [result appendString:NSLocalizedString(@"Door Sensor Low Voltage", @"")];

            break;
        case USER_EVENT_ALARM_SMOK_LOWVOL:
            [result appendString:NSLocalizedString(@"Smoke Alarm Sensor  Low Voltage", @"")];

            
            break;
        case USER_EVENT_ALARM_IRDA_LOWVOL:
            [result appendString:NSLocalizedString(@"Infrared Sensor  Low Voltage", @"")];

            
            break;
        case USER_EVENT_ALARM_AIR_LOWVOL:
            [result appendString:NSLocalizedString(@"", @"")];

            break;
        case USER_EVENT_ALARM_SWITCH_LOWVOL:
            [result appendString:NSLocalizedString(@"", @"")];

            break;
        case USER_EVENT_ALARM_WHISTLE_LOWVOL:
            [result appendString:NSLocalizedString(@"", @"")];

            break;
        case USER_EVENT_ALARM_DOOR_OFFLINE:
            [result appendString:NSLocalizedString(@"Door Sensor Offline", @"")];
            
            break;
        case USER_EVENT_ALARM_SMOK_OFFLINE:
            [result appendString:NSLocalizedString(@"Smoke Alarm Sensor Offline", @"")];
            
            break;
        case USER_EVENT_ALARM_IRDA_OFFLINE:
            [result appendString:NSLocalizedString(@"Infrared Sensor Offline", @"")];

            break;
        case USER_EVENT_ALARM_AIR_OFFLINE:
            [result appendString:NSLocalizedString(@"", @"")];

            break;
        case USER_EVENT_ALARM_SWITCH_OFFLINE:
            [result appendString:NSLocalizedString(@"", @"")];

            break;
        case USER_EVENT_ALARM_WHISTLE_OFFLINE:
            [result appendString:NSLocalizedString(@"", @"")];

            break;
        case USER_EVENT_ALARM_GAS_OFFLINE:
            [result appendString:NSLocalizedString(@"Gas Sensor Offline", @"")];

            break;
            //                           = 0X1B,   // for gas warning
            //                    = 0X1C,   // for door low power warning
            //                    = 0X1D,   // for smok low power warning
            //                    = 0X1E,   // for 红外探测 low power warning
            //                    = 0X1F,   // for air low power warning
            //                = 0X20,   // for 开关低电量 warning
            //                = 0X21,   // for 警笛低电量 warning
            //                = 0X22,   // for door离线 warning
            //                = 0X23,   // for 烟感离线 warning
            //                = 0X24,   // for 红外探测离线 warning
            //                    = 0X25,   // for air离线 warning
            //                = 0X26,   // for 开关离线 warning
            //                = 0X27,   // for 警笛离线 warning
            //                    = 0X28,   // for gas离线 warning

            
        case USER_EVENT_ARMED_HOME_MODE:
            [result appendString:NSLocalizedString(@"Stay Arm", @"")];
            
            break;
        case USER_EVENT_ARMED_DISALAM_MODE_AUTO:
            [result appendString:NSLocalizedString(@"Disarm", @"")];
            
            break;
        case USER_EVENT_ARMED_ALARM_MODE_AUTO:
            [result appendString:NSLocalizedString(@"Arm", @"")];
            
            break;
        case USER_EVENT_ARMED_HOME_MODE_AUTO:
            [result appendString:NSLocalizedString(@"Stay Arm", @"")];
            
            break;

        case USER_EVENT_NOTIFY_VIDEO_DISABLE:
            [result appendString:NSLocalizedString(@"Private Mode Inactived", @"")];
            
            break;
        case USER_EVENT_NOTIFY_VIDEO_ENABLED:
            [result appendString:NSLocalizedString(@"Private Mode Actived", @"")];
            
            break;
            
        default:
            [result appendString:NSLocalizedString(@"Other", @"")];
            break;
    }
    
    return result;
}


+ (STimeDay)getTimeDay:(long)time {
    
    STimeDay result;
    
    NSDate *date = [[NSDate alloc] initWithTimeIntervalSince1970:time];
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
//    [dateFormatter setTimeZone:[NSTimeZone timeZoneWithName:@"UTC"]];
//    
    
    [dateFormatter setDateFormat:@"yyyy"];
    result.year = [[dateFormatter stringFromDate:date] intValue];
    
    [dateFormatter setDateFormat:@"MM"];
    result.month = [[dateFormatter stringFromDate:date] intValue];
    
    [dateFormatter setDateFormat:@"dd"];
    result.day = [[dateFormatter stringFromDate:date] intValue];
    
    [dateFormatter setDateFormat:@"e"];
    result.wday = [[dateFormatter stringFromDate:date] intValue];
    
    [dateFormatter setDateFormat:@"HH"];
    result.hour = [[dateFormatter stringFromDate:date] intValue];
    
    [dateFormatter setDateFormat:@"mm"];
    result.minute = [[dateFormatter stringFromDate:date] intValue];
    
    [dateFormatter setDateFormat:@"ss"];
    result.second = [[dateFormatter stringFromDate:date] intValue];
    
    return result;
}


// return a new autoreleased UUID string
- (NSString *)generateUuidString
{
    // create a new UUID which you own
    CFUUIDRef uuid = CFUUIDCreate(kCFAllocatorDefault);

    // create a new CFStringRef (toll-free bridged to NSString)
    // that you own
    NSString *uuidString = (NSString *)CFBridgingRelease(CFUUIDCreateString(kCFAllocatorDefault, uuid));

    // transfer ownership of the string
    // to the autorelease pool
//    [uuidString autorelease];

    // release the UUID
    CFRelease(uuid);

    return uuidString;
}

- (id)initWithEventType:(int)type EventTime:(long)time EventStatus:(int)status {
    
    self = [super init];
    
    if (self) {
        
//        self.UUID = [self generateUuidString];
        
        [self myInit];
        
        self.eventType = type;
        self.eventTime = time;
        self.eventStatus = status;

    }
    
    return self;
}
- (id)initWithEventType:(int)eventType EventTime:(long)eventTime EventStatus:(int)status EventPicn:(NSString *)eventPicn {
    self = [super init];
    
    if (self) {
        
//        self.UUID = [self generateUuidString];
        
        [self myInit];
        
        self.eventType = eventType;
        self.eventTime = eventTime;
        self.eventStatus = status;
        self.eventPicn = eventPicn;
    }
    
    return self;
}

- (void)myInit {

    self.timeStr = @"";
    self.isSelection = NO;
    self.devid = @"";
    self.eventType = 0;
    self.eventTypeStr = @"";
    self.eventTime = 0;
    self.eventStatus = 0;
    self.eventPicn = @"";
    self.weight = 0;
}


- (void)dealloc {
    
}

@end
