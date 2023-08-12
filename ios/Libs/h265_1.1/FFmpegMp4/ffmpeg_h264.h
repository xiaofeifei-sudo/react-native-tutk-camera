//
//  ffmpeg_h264.h
//  IPCAM_oa
//
//  Created by apple on 2018/12/25.
//  Copyright © 2018 TUTK. All rights reserved.
//

#ifndef ffmpeg_h264_h
#define ffmpeg_h264_h

#include <stdio.h>
#include "avcodec.h"
#include "avformat.h"
//#include <libavcodec/avcodec.h>
//#include <libavformat/avformat.h>
#include "faac.h"
#include <sys/time.h>

#define AV_MAX_AUDIO_DATA_SIZE           1280
#define AV_MAX_VIDEO_DATA_SIZE           512 *1024





int CreateMp4ForFFmpeg(const char* filename,unsigned long width);
void WriteVideoForH264(void* data, int nLen,unsigned char *sps_pps,int sps_ppsLen,unsigned long width);
void writeVideoForAAC(void* data, int nLen);
void CloseMp4ForH264();


#endif /* ffmpeg_h264_h */
