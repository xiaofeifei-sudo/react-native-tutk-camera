//
//  HardwareDecompressVideo.h
//  H264HardwareCodec
//
//  Created by scott on 11/26/15.
//  Copyright © 2015 com.KirogiYi. All rights reserved.
//

//#include "AVFrameData.h"
//#include "YUVData.h"
#import <VideoToolbox/VideoToolbox.h>
#import <Foundation/Foundation.h>

typedef struct _NALUnit{
    unsigned int type;
    unsigned int size;
    unsigned char *data;
}NALUnit;

typedef enum{
    NALUTypeBPFrame = 0x01,
    NALUTypeIFrame = 0x05,
    NALUTypeSEI = 0x06,
    NALUTypeSPS = 0x07,
    NALUTypePPS = 0x08
}NALUType;

typedef struct _SPS_PPS{
    
    unsigned char *dataBuffer;
    int aLength;
    
}SPS_PPS;

@protocol GetSpsAndPpsDelegate <NSObject>

- (void)displayDecodedFrame:(CVImageBufferRef )imageBuffer;


@end

@interface GetSpsAndPps : NSObject {
    float fileCount;
unsigned char *spsAndPpsBuffer;
}

@property (weak, nonatomic) id<GetSpsAndPpsDelegate> delegate;

- (id)init;
- (BOOL)takePicture:(NSString *)fileName;
-(SPS_PPS)deCompressedCMSampleBufferWithData:(uint8_t *)frame withSize:(uint32_t)frameSize andOffset:(int)offset;

@end
