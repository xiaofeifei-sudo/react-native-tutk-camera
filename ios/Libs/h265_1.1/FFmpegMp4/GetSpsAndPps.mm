//
//  HardwareDecompressedVideoFrame.m
//  H264HardwareCodec
//
//  Created by scott on 11/26/15.
//  Copyright © 2015 com.KirogiYi. All rights reserved.
//

#import <UIKit/UIKit.h>

#include "GetSpsAndPps.h"

@implementation GetSpsAndPps{
    uint8_t *_sps;
    uint8_t *_pps;
    
    BOOL _isTakePicture;
    BOOL _isSaveTakePictureImage;
    NSString *_saveTakePicturePath;
    
    unsigned int _spsSize;
    unsigned int _ppsSize;
    
    int64_t mCurrentVideoSeconds;
    VTDecompressionSessionRef _decompressionSession;
    CMVideoFormatDescriptionRef _decompressionFormatDesc;
}

-(id)init
{
    if(self = [super init]){
        _isTakePicture = false;
        
        _sps = NULL;
        _pps = NULL;

        _spsSize = 0;
        _ppsSize = 0;
        
        _decompressionSession = NULL;
        _decompressionFormatDesc = NULL;
    }
    
    return self;
}

-(BOOL)takePicture:(NSString *)fileName
{
    _isTakePicture = true;
    _isSaveTakePictureImage = false;
    _saveTakePicturePath = fileName;
    
    while(_isSaveTakePictureImage == false){
        //Just waiting "_isSaveTakePictureImage" become true.
    }
    
    _isTakePicture = false;
    return true;;
}

-(SPS_PPS)deCompressedCMSampleBufferWithData:(uint8_t *)frame withSize:(uint32_t)frameSize andOffset:(int)offset
{
    NALUnit nalUnit;
    
    SPS_PPS sps_pps;
    char *data = (char*)frame;
    int dataLen = frameSize;
    
    if(data == NULL || dataLen == 0){
        
        sps_pps.aLength = 0;
        return sps_pps;
    }
    
    BOOL isIFrame = NO;
    
    while([self nalunitWithData:data andDataLen:dataLen andOffset:offset toNALUnit:&nalUnit])
    {
        if(nalUnit.data == NULL || nalUnit.size == 0){
            sps_pps.aLength = 0;
            return sps_pps;
        }
        
        [self infalteStartCodeWithNalunitData:&nalUnit];
//        NSLog(@"NALUint Type: %d.", nalUnit.type);
        
        switch (nalUnit.type) {
            case NALUTypeIFrame://IFrame

                break;
                
            case NALUTypeSEI://SEI
                break;
            case NALUTypeSPS://SPS
                
                if (_sps) {
                    free(_sps);
                }
                _sps = NULL;
                
                _spsSize = nalUnit.size - 4;
                if(_spsSize <= 0){
                    sps_pps.aLength = 0;
                    return sps_pps;
                }
                
                _sps = (uint8_t*)malloc(_spsSize);
                memcpy(_sps, nalUnit.data + 4, _spsSize);
                NSLog(@"NALUint SPS size:%d", nalUnit.size - 4);
                
                for (int i = 0; i <nalUnit.size; i ++) {
                    
                    NSLog(@"-----%x",nalUnit.data[i]);
                }
                break;
            case NALUTypePPS://PPS
                
                if (_pps) {
                    free(_pps);
                }
                _pps = NULL;
                
                _ppsSize = nalUnit.size - 4;
                if(_ppsSize <= 0){
                    
                    sps_pps.aLength = 0;
                    return sps_pps;
                }
                
                _pps = (uint8_t*)malloc(_ppsSize);
                memcpy(_pps, nalUnit.data + 4, _ppsSize);
                NSLog(@"NALUint PPS size:%d", nalUnit.size - 4);
                
//                spsAndPpsBuffer = new unsigned char[_spsSize +_ppsSize];
                
                spsAndPpsBuffer = new unsigned char[_spsSize +_ppsSize+8];
                
                unsigned char spsHead[4] = {0x00,0x00,0x00,0x01};
                unsigned char ppsHead[4] = {0x00,0x00,0x00,0x01};
                memcpy(spsAndPpsBuffer, spsHead, 4);
                memcpy(spsAndPpsBuffer +4, _sps, _spsSize);
                memcpy(spsAndPpsBuffer +_spsSize +4, ppsHead, 4);
                memcpy(spsAndPpsBuffer +_spsSize +8, _pps, _ppsSize);
                
                NSLog(@"----1231---%s",spsAndPpsBuffer);

                sps_pps.dataBuffer = spsAndPpsBuffer;
                sps_pps.aLength = _spsSize +_ppsSize +8;
                
                for (int i = 0; i<_spsSize+_ppsSize+8; i++) {
                    
                    NSLog(@"--11---%x",spsAndPpsBuffer[i]);
                }
                NSLog(@"The AVFrame data size:%d", offset);
                
                
                for (int i = 0; i <nalUnit.size; i ++) {
                    
                    NSLog(@"-----%x",nalUnit.data[i]);
                }
                
                return sps_pps;
                
                break;

        }
        
        
    }
    
    return sps_pps;
}


-(void)infalteStartCodeWithNalunitData:(NALUnit *)dataUnit
{
    //Inflate start code with data length
    unsigned char* data  = dataUnit->data;
    unsigned int dataLen = dataUnit->size - 4;
    
    data[0] = (unsigned char)(dataLen >> 24);
    data[1] = (unsigned char)(dataLen >> 16);
    data[2] = (unsigned char)(dataLen >> 8);
    data[3] = (unsigned char)(dataLen & 0xff);
}

-(int)nalunitWithData:(char *)data andDataLen:(int)dataLen andOffset:(int)offset toNALUnit:(NALUnit *)unit
{
    unit->size = 0;
    unit->data = NULL;
    
    int addUpLen = offset;
    while(addUpLen < dataLen)
    {
        if (data[addUpLen++] == 0x00 &&
            data[addUpLen++] == 0x00) {
            
            char tmpData = data[addUpLen++];
            if (tmpData == 0x00) {

                if (data[addUpLen++] == 0x01) {

                    int pos = addUpLen;
                    while(pos < dataLen){//Find next NALU
                        if(data[pos++] == 0x00 &&
                           data[pos++] == 0x00 &&
                           data[pos++] == 0x00 &&
                           data[pos++] == 0x01){
        
                            break;
                        }
                    }
        
                    unit->type = data[addUpLen] & 0x1f;
                    if(pos == dataLen){
                        unit->size = pos - addUpLen + 4;
                    }else{
                        unit->size = pos - addUpLen;
                    }
                    
                    unit->data = (unsigned char*)&data[addUpLen - 4];
                    return 1;
                }
                
            } else if (tmpData == 0x01) {
                
                NSLog(@"nalunitWithData 0x000001  dataLen:%d", dataLen);
                return 1;
            }
        }

    }
    return -1;
}

static void decompressionOutputCallbackRecord(void *decompressionOutputRefCon,
                                                  void *sourceFrameRefCon,
                                                  OSStatus status,
                                                  VTDecodeInfoFlags infoFlags,
                                                  CVImageBufferRef imageBuffer,
                                                  CMTime presentationTimeStamp,
                                                  CMTime presentationDuration ){
    
    
    CVPixelBufferRef *outputPixelBuffer = (CVPixelBufferRef *)sourceFrameRefCon;
    *outputPixelBuffer = CVPixelBufferRetain(imageBuffer);

}

-(void)dealloc
{
    
    if(_sps){
        free(_sps);
        _sps = NULL;
    }
    
    if(_pps){
        free(_pps);
        _pps = NULL;
    }
    
    [self clearDecompressionSession];
    
//    [super dealloc];

}

- (void)clearDecompressionSession {
    
    NSLog(@"clearDecompressionSession");
    
    if(_decompressionSession){
        CFRelease(_decompressionSession);
        _decompressionSession = NULL;
    }
    
    if(_decompressionFormatDesc){
        CFRelease(_decompressionFormatDesc);
        _decompressionFormatDesc = NULL;
    }
}


@end
