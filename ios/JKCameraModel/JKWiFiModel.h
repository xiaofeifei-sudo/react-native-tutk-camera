//
//  JKWiFiModel.h
//  PetWant
//
//  Created by mac on 2019/12/23.
//  Copyright © 2019 TUTK. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JKWiFiModel : NSObject

@property (strong, nonatomic) NSString *ssid;
@property (strong, nonatomic) NSString *status;
@property (strong, nonatomic) NSString *signal;
@property (assign, nonatomic) char mode;
@property (assign, nonatomic) char enctype;
@property (strong, nonatomic) NSString *password;


@end

NS_ASSUME_NONNULL_END
