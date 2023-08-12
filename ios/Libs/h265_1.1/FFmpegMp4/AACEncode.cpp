//
//  AACEncode.cpp
//  IPCAM_oa
//
//  Created by apple on 2019/1/3.
//  Copyright © 2019 TUTK. All rights reserved.
//

#include "AACEncode.hpp"


unsigned long    aacSamplesRate;//编码采样率
unsigned int     aacNumChannels;//编码声道数
unsigned long    aacInputSample;//输入样本大小，在打开编码器时会得到此值
unsigned int     aacPCMBitSize;//pcm位深，用于计算一帧pcm大小
unsigned long    aacMaxOutputBytes;//最大输出，编码后的输出数据大小不会高于这个值，也是打开编码器时获得
unsigned long    aacPCMBufferSize;//一帧pcm缓存大小
int              aacCountSize;//计算缓存大小

faacEncHandle               aacEncoder;//faac编码器句柄
faacEncConfigurationPtr     aacConfig;//faac设置类

/**
 *初始化编码器参数
 */
void SetEncoderParameter(){
    
    aacSamplesRate = 8000;
    aacNumChannels = 1;
    aacInputSample = 0;
    aacMaxOutputBytes = 0;
    aacPCMBitSize = 16;
    aacPCMBufferSize = 0;
    aacCountSize = 0;

    aacEncoder = faacEncOpen(aacSamplesRate, aacNumChannels, &aacInputSample, &aacMaxOutputBytes);

    aacConfig = faacEncGetCurrentConfiguration(aacEncoder);
    aacConfig->aacObjectType = LOW;
    aacConfig->useLfe = 0;
    aacConfig->useTns = 1;
    aacConfig->allowMidside = 0;
    aacConfig->outputFormat = 1;
    aacConfig->bitRate = 44100;
    aacConfig->inputFormat = FAAC_INPUT_16BIT;
    faacEncSetConfiguration(aacEncoder, aacConfig);
    aacPCMBufferSize = aacInputSample *aacPCMBitSize /8;

    
}


void CloseAACEncode(){
    
    if (aacEncoder != NULL) {
        
        faacEncClose(aacEncoder);
        aacEncoder = NULL;
    }
    
}

int MaxSizeForAAC(){
    
    return (int)aacPCMBufferSize;
}

AACData *PCMToAAC(unsigned char *pcmData,int size){
    
    AACData *aac = new AACData();
    aac->size = 0;
    
    unsigned char *aacData = new unsigned char[aacMaxOutputBytes];
    
    int ret = (int)faacEncEncode(aacEncoder, (int32_t *)pcmData, (int)aacInputSample, aacData, (int)aacMaxOutputBytes);
    
    if (ret >0) {
        
        printf("encode voice success!\n");
        aac->aacData = aacData;
        aac->size = ret;

        
    }else{
        
        printf("encode voice failed\n");
        
    }
    
    return aac;
}

