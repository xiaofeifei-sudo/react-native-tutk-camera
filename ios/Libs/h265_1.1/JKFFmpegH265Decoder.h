//
//  JKFFmpegH265Decoder.h
//  Wisdom
//
//  Created by mac on 2022/11/16.
//  Copyright © 2022 mac. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

#define H265DecoderManager [JKFFmpegH265Decoder shareManager]

@class JKFFmpegH265Decoder;
@protocol JKFFmpegH265DecoderDelegate <NSObject>

- (void)ffmpegH265Decoder:(JKFFmpegH265Decoder *)decoder decodeImage:(UIImage *)img;

@end

@interface JKFFmpegH265Decoder : NSObject

@property (nonatomic, weak)id<JKFFmpegH265DecoderDelegate> delegate;

+ (instancetype)shareManager;

///// 该方法已弃用，改用startH265Decode（快速调用释放和初始化可能会导致空指针的问题）
//int InitH265Decoder(void);
///// 该方法已弃用，改用stopH265Decode（快速调用释放和初始化可能会导致空指针的问题）
//void UninitH265Decoder(void);

int startH265Decode(void);
void stopH265Decode(void);

///长后台重新返回到前台时，调用该方法，重新初始化解码器
void reinitializeH265Decoder(void);

//用来将内存buffer的数据拷贝到buf
int read_packet(void *opaque, uint8_t *buf, int buf_size);

int H265Decode(unsigned char * framedata, int framelen);

@end

NS_ASSUME_NONNULL_END
