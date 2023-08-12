//
//  AACEncode.hpp
//  IPCAM_oa
//
//  Created by apple on 2019/1/3.
//  Copyright © 2019 TUTK. All rights reserved.
//

#ifndef AACEncode_hpp
#define AACEncode_hpp

#include <stdio.h>
#include "ffmpeg_h264.h"

typedef struct{
    
    unsigned char*      aacData;
    int                 size;
    
}AACData;


void SetEncoderParameter();
AACData *PCMToAAC(unsigned char *pcmData,int size);

int MaxSizeForAAC();
void CloseAACEncode();


#endif /* AACEncode_hpp */
