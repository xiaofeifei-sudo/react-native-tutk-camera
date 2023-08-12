//
//  JKFFmpegH265Decoder.m
//  Wisdom
//
//  Created by mac on 2022/11/16.
//  Copyright © 2022 mac. All rights reserved.
//

#import "JKFFmpegH265Decoder.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "avcodec.h"
#include "imgutils.h"
#include "samplefmt.h"
#include "timestamp.h"
#include "avformat.h"
#include "log.h"
//#include <libavcodec/avcodec.h>
//#include <libavutil/imgutils.h>
//#include <libavutil/samplefmt.h>
//#include <libavutil/timestamp.h>
//#include <libavformat/avformat.h>

typedef enum {
    DECODE_UNINIT       = 0,//未初始化
    DECODE_INITCOMPLETE = 1,//初始化完成
    DECODE_DECODING     = 2,//正在解码
    DECODE_STOPDECODE   = 3,//停止解码
    DECODE_RESET        = 4,//重新初始化（码流大小发生变化，停止解码一帧有卡顿&花屏的现象，重新初始化解码器试试）
}Decode_Status;

static AVCodec *codec = NULL;
static AVCodecContext *codec_ctx= NULL;
static AVFrame *frame = NULL;
static AVPacket avpkt;
static AVIOContext *avio_ctx;
static AVFormatContext *fmt_ctx;
static int codecInited = 0;
static char *outputframe = NULL;
static Decode_Status decodeStatus = 0;
static BOOL decoderComplete = NO;//增加个标志位，当解码完成才能释放解码器，不然可能会有空指针导致崩溃

#define SCALEY     76309
#define SCALECrv   104597
#define SCALECbu   132201
#define SCALECgu   25675
#define SCALECgv   53279

#define SHIFTY     16
#define SHIFTCC    128
#define SHIFTCrv   128
#define SHIFTCbu   128
#define SHIFTCgu   128
#define SHIFTCgv   128

long int mycrv_tab[256];
long int mycbu_tab[256];
long int mycgu_tab[256];
long int mycgv_tab[256];
long int mytab_76309[256];

unsigned char myclp[1024];


static JKFFmpegH265Decoder * shareManager = nil;
static dispatch_once_t onceToken; //拿到函数体外,成为全局的.

@interface JKFFmpegH265Decoder()
///多尼斯切换高清会崩溃，增加这两个属性
@property (nonatomic, assign)int imgWidth;
@property (nonatomic, assign)int imgHeight;

@property (nonatomic, assign)int clean;//解码丢掉

@end

@implementation JKFFmpegH265Decoder

+ (instancetype)shareManager{
    dispatch_once(&onceToken, ^{
        shareManager = [[self alloc] init];
        InitH265Decoder();
    });
    return shareManager;
}

///长后台重新返回到前台时，调用该方法，重新初始化解码器
void reinitializeH265Decoder(void) {
    if (decodeStatus != DECODE_UNINIT) {
        decodeStatus = DECODE_UNINIT;
    }
    if (decoderComplete && decodeStatus == DECODE_UNINIT){
        avcodec_close(codec_ctx);
        av_free(codec_ctx);
        av_frame_free(&frame);
        
        if (avio_ctx) {
            av_freep(&avio_ctx->buffer);
        }
        avio_context_free(&avio_ctx);
        
        if (fmt_ctx) {
            avformat_close_input(&fmt_ctx);
        }
        avformat_free_context(fmt_ctx);
        
        free(outputframe);
        
        //重新初始化解码器
        InitH265Decoder();
    }
}

//其实可以不调用
+ (void)deallocManager {
    onceToken = 0;
    shareManager = NULL;
    UninitH265Decoder();
}

//为啥要每次解码都初始化？不如启动App时就初始化，这样就避免了快速关闭和开启视频流时，可能这边没释放完，那边又开始了，导致outputframe数据有问题
int InitH265Decoder(void) {
    if (decodeStatus != DECODE_UNINIT) {
#if DEBUG
        printf("已经初始化 decodeStatus = %d\n", decodeStatus);
#endif
        return 1;
    }
    av_log_set_level(AV_LOG_QUIET);
    myyuv420torgb24_c_init__();
    
    av_register_all();
    avformat_network_init();

    codec = avcodec_find_decoder(AV_CODEC_ID_HEVC);

    if(!codec) {
#if DEBUG
        printf("初始化解码失败 avcodec_find_decoder fail\n");
#endif
        return 0;
    }
    codec_ctx = avcodec_alloc_context3(codec);
    if(!codec_ctx) {
#if DEBUG
        printf("初始化解码失败 avcodec_alloc_context3 fail\n");
#endif
        return 0;
    }/*
      else
      {
      codec_ctx->time_base.num = 1;
      codec_ctx->frame_number = 1; //每包一个视频帧
      codec_ctx->codec_type = AVMEDIA_TYPE_VIDEO;
      codec_ctx->bit_rate = 0;
      codec_ctx->time_base.den = den;//帧率
      codec_ctx->width = width;//视频宽
      codec_ctx->height = height;//视频高
      }*/
    
    //设置该标记后，如果解码校验失败则会在avcodec_decode_video2的时候返回失败，这样就可以不去解码错误的码流，这个可以过滤部分花屏的码流
    codec_ctx->err_recognition |= AV_EF_EXPLODE;

    if(avcodec_open2(codec_ctx, codec, 0) < 0) {
#if DEBUG
        printf("初始化失败 avcodec_open2 fail\n");
#endif
        return 0;
    }
    frame = av_frame_alloc();
    if(!frame) {
#if DEBUG
        printf("初始化失败 av_frame_alloc fail\n");
#endif
        return 0;
    }
    av_init_packet(&avpkt);

    outputframe = (char *)malloc(1920*1080*4);
    decodeStatus = DECODE_INITCOMPLETE;

    return 1;
}

void UninitH265Decoder(void) {
    if (decodeStatus != DECODE_UNINIT) {
        decodeStatus = DECODE_UNINIT;
    }
    if (decoderComplete && decodeStatus == DECODE_UNINIT){
        avcodec_close(codec_ctx);
        av_free(codec_ctx);
        av_frame_free(&frame);
        
        if (avio_ctx) {
            av_freep(&avio_ctx->buffer);
        }
        avio_context_free(&avio_ctx);
        
        if (fmt_ctx) {
            avformat_close_input(&fmt_ctx);
        }
        avformat_free_context(fmt_ctx);
        
        free(outputframe);
    }
}

int startH265Decode(void) {
    int res = InitH265Decoder();
    if (res) {
        decodeStatus = DECODE_DECODING;
    }
    return res;
}
void stopH265Decode(void) {
    decodeStatus = DECODE_STOPDECODE;
}

void myyuv420torgb24_c_init__() {
    long int crv,cbu,cgu,cgv;
    int i,ind;
    
    crv = SCALECrv; cbu = SCALECbu;
    cgu = SCALECgu; cgv = SCALECgv;
    
    for(i = 0; i < 256; i++){
        mycrv_tab[i] = (i-SHIFTCrv) * crv;
        mycbu_tab[i] = (i-SHIFTCbu) * cbu;
        mycgu_tab[i] = (i-SHIFTCgu) * cgu;
        mycgv_tab[i] = (i-SHIFTCgv) * cgv;
        mytab_76309[i]= SCALEY*(i-SHIFTY);
    }
    
    for(i=0; i<384; i++) myclp[i] =0;
    ind=384;
    for(i=0;i<256; i++) myclp[ind++]=i;
    ind=640;
    for(i=0;i<384;i++) myclp[ind++]=255;
}

//how to use:
//yuv420torgb24_c(y, yStride, v, u, uvStride, rgb, 320, 240);
int  myyuv420torgb24_c__(unsigned char *src0, int stride_y,
                      unsigned char *src1, unsigned char *src2, int stride_uv,
                      unsigned char *dst_ori, int wid, int hei) {
    
    int h = hei, w = wid;
    if (hei > H265DecoderManager.imgHeight && H265DecoderManager.imgHeight != 0) {
        h = H265DecoderManager.imgHeight;
    }
    
    if (wid > H265DecoderManager.imgWidth && H265DecoderManager.imgWidth != 0) {
        w = H265DecoderManager.imgWidth;
    }
    
    if (H265DecoderManager.imgWidth != wid||
        H265DecoderManager.imgHeight != hei) {
        H265DecoderManager.imgWidth = wid;
        H265DecoderManager.imgHeight = hei;
        H265DecoderManager.clean = 1;
    }

    int y1,y2,u,v;
    unsigned char *py1,*py2, *pSrc1, *pSrc2;
    int yDeltaPerRow =(stride_y-w+stride_y),
        uvDeltaPerRow=((stride_uv-w+stride_uv)>>1);
    
    int i,j, c1, c2, c3, c4;
    unsigned char *d1, *d2;
    
    py1=src0;
    py2=src0+stride_y;
    pSrc1=src1;
    pSrc2=src2;
    
    d1=dst_ori;
    d2=d1+3*w;
    for(j=0; j<h; j+=2)    //hei/2
    {
        for(i=0; i<w; i+=2) //w/2
        {
            u = *pSrc1++;
            v = *pSrc2++;
            
            c1 = mycrv_tab[v];
            c2 = mycgu_tab[u];
            c3 = mycgv_tab[v];
            c4 = mycbu_tab[u];
            
            //up-left
            y1 = mytab_76309[*py1++];
            *d1++ = myclp[384+((y1 + c1)>>16)];
            *d1++ = myclp[384+((y1 - c2 - c3)>>16)];
            *d1++ = myclp[384+((y1 + c4)>>16)];
            
            //down-left
            y2 = mytab_76309[*py2++];
            *d2++ = myclp[384+((y2 + c1)>>16)];
            *d2++ = myclp[384+((y2 - c2 - c3)>>16)];
            *d2++ = myclp[384+((y2 + c4)>>16)];
            
            
            //up-right
            y1 = mytab_76309[*py1++];
            *d1++ = myclp[384+((y1 + c1)>>16)];
            *d1++ = myclp[384+((y1 - c2 - c3)>>16)];
            *d1++ = myclp[384+((y1 + c4)>>16)];
            
            //down-right
            y2 = mytab_76309[*py2++];
            *d2++ = myclp[384+((y2 + c1)>>16)];
            *d2++ = myclp[384+((y2 - c2 - c3)>>16)];
            *d2++ = myclp[384+((y2 + c4)>>16)];
        }//for(w)--end
        
        d1 += 3*w;
        d2 += 3*w;
        
        py1+= yDeltaPerRow;
        py2+= yDeltaPerRow;
        pSrc1+=uvDeltaPerRow;
        pSrc2+=uvDeltaPerRow;
    }
    int bRes = myCheckY(w, h, frame->data[0]);
    if(0 == bRes) {
        printf("灰屏或者绿屏不显示\n");
        return -1;
    }
    return 0;
}

int myCheckY(int iwidth, int iHeight, unsigned char*Buf) {
    unsigned char * pNewPoint = Buf;
    int iCountY = 0;
    //定位最后一行Y
    pNewPoint = Buf;
    //获得新的像素位置
    pNewPoint = Buf + (iHeight - 8)*iwidth;
    //遍历Y信息的所有高
    for (int i = 0; i < 8; i++) {
        unsigned char *pNewPoint2 = pNewPoint + i*iwidth;
        //遍历Y信息的宽
        for (int j = 0; j < iwidth; j+=24)
        {
            int a = memcmp(pNewPoint2 + j, pNewPoint2 + j + 8, 8);
            int b = memcmp(pNewPoint2 + j + 8, pNewPoint2 + j + 16, 8);
                        //判断连续两个8像素宏块，是否相同，并且在这个值范围内(0x7A~0x80)
            if (a == b && b == 0 && pNewPoint2[j] > 0x7A&& pNewPoint2[j] <= 0x80) {
                iCountY++;
            }
        }
    }
    if(iCountY>100) {
        return 0;
    }
    return 1;
}

struct buffer_data {
    uint8_t *ptr; /* 文件中对应位置指针 */
    size_t size;  ///< size left in the buffer /* 文件当前指针到末尾 */
};
// 重点，自定的buffer数据要在外面这里定义
struct buffer_data bd = {0};

//用来将内存buffer的数据拷贝到buf
int read_packet(void *opaque, uint8_t *buf, int buf_size) {
    if(decodeStatus != DECODE_DECODING) {
        if (decodeStatus == DECODE_UNINIT) {
            reinitializeH265Decoder();
        }
        return -1;
    }
    buf_size = FFMIN(buf_size, bd.size);
    if (!buf_size) {
        if (decodeStatus == DECODE_UNINIT) {
            reinitializeH265Decoder();
        }
        return AVERROR_EOF;
    }
    //printf("ptr:%p size:%zu bz:%d\n", bd.ptr, bd.size, buf_size);
    
    /* copy internal buffer data to buf */
    memcpy(buf, bd.ptr, buf_size);
    bd.ptr += buf_size;
    bd.size -= buf_size;
    
    avpkt.size = buf_size;
    avpkt.data = buf;

    if (avcodec_send_packet(codec_ctx, &avpkt)) {
        // 增加于2021-07-05
        av_packet_unref(&avpkt);
        if (decodeStatus == DECODE_UNINIT) {
            reinitializeH265Decoder();
        }
        return -1;
    }
    if (frame) {
        if(avcodec_receive_frame(codec_ctx, frame)) {
            if (decodeStatus == DECODE_UNINIT) {
                reinitializeH265Decoder();
            }
            return -1;
        }
    }

    unsigned char *myOutputframe = (unsigned char *)malloc(1920*1080*4);
    int res = 0;
    switch (codec_ctx->pix_fmt) {
        case AV_PIX_FMT_YUV422P: {
            int index = 0;
            int y_i = 0, u_i = 0, v_i = 0;
            for (index = 0; index < frame->width*frame->height * 2;) {
                myOutputframe[index++] = frame->data[0][y_i++];
                myOutputframe[index++] = frame->data[1][u_i++];
                myOutputframe[index++] = frame->data[0][y_i++];
                myOutputframe[index++] = frame->data[2][v_i++];
            }
        }
            break;
        default: {
            res = myyuv420torgb24_c__(frame->data[0], frame->linesize[0], frame->data[1], frame->data[2], frame->linesize[1], myOutputframe, codec_ctx->width, codec_ctx->height);
        }
            break;
    }
    if (res == -1) {
        free(myOutputframe);
        if (decodeStatus == DECODE_UNINIT) {
            reinitializeH265Decoder();
        }
        return -1;
    }
    
    if (H265DecoderManager.clean > 0) {//丢一帧还是不够好，丢两帧试试
        free(myOutputframe);
        H265DecoderManager.clean --;
        if (decodeStatus == DECODE_UNINIT) {
            reinitializeH265Decoder();
        }
        return -1;
    }
    
    int w = 0;
    int h = 0;

    int *width = &w;
    int *height = &h;

    *width = codec_ctx->width;
    *height = codec_ctx->height;
    
    memcpy(outputframe, myOutputframe, (1920*1080*4));
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CFDataRef data = CFDataCreateWithBytesNoCopy(kCFAllocatorDefault, (const unsigned char *) outputframe, w * h * 3,kCFAllocatorNull);
    CGDataProviderRef provider = CGDataProviderCreateWithCFData(data);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGImageRef imgRef = CGImageCreate(w, h, 8, 24, w * 3, colorSpace, bitmapInfo, provider, NULL, YES, kCGRenderingIntentDefault);

    UIImage *img = [[UIImage alloc] initWithCGImage:imgRef];

    CGImageRelease(imgRef);
    CGColorSpaceRelease(colorSpace);
    CGDataProviderRelease(provider);
    CFRelease(data);
    free(myOutputframe);
    if(decodeStatus == DECODE_DECODING) {
        if (H265DecoderManager.delegate && [H265DecoderManager.delegate respondsToSelector:@selector(ffmpegH265Decoder:decodeImage:)]) {
            [H265DecoderManager.delegate ffmpegH265Decoder:H265DecoderManager decodeImage:img];
        }
    }
    decoderComplete = YES;
    if (decodeStatus == DECODE_UNINIT) {
        reinitializeH265Decoder();
    }
    return buf_size;
}

//解码一帧详细操作（这里只是做了YUV422P的处理）
//因为avcodec_decode_video2这个接口被ffmpeg所摒弃的，可以用新的接口
int H265Decode(unsigned char * framedata, int framelen) {//output
    if(decodeStatus != DECODE_DECODING) {
        return -1;
    }
    decoderComplete = NO;
    if (!fmt_ctx) {
        fmt_ctx = avformat_alloc_context();
    }
    if (!frame) {
        frame = av_frame_alloc();
    }
    
    size_t avio_ctx_buffer_size = framelen;
    bd.ptr = framedata;  /* will be grown as needed by the realloc above */
    bd.size = framelen; /* no data at this point */
    unsigned char *avio_ctx_buffer = (unsigned char *)av_malloc(avio_ctx_buffer_size);
    avio_ctx = avio_alloc_context(avio_ctx_buffer, avio_ctx_buffer_size, 0, NULL, read_packet, NULL, NULL);
    fmt_ctx->pb = avio_ctx;
    fmt_ctx->flags = AVFMT_FLAG_CUSTOM_IO;

    /* 打开内存缓存文件, and allocate format context */

    int res = avformat_open_input(&fmt_ctx, NULL, NULL, NULL);
    if (res < 0){

        if (avio_ctx) {
            av_freep(&avio_ctx->buffer);
        }
        avio_context_free(&avio_ctx);

        if (fmt_ctx) {
            avformat_close_input(&fmt_ctx);
        }
        avformat_free_context(fmt_ctx);

        return -1;
    }

    if (avformat_find_stream_info(fmt_ctx, NULL) < 0) {
        if (avio_ctx) {
            av_freep(&avio_ctx->buffer);
        }
        avio_context_free(&avio_ctx);

        if (fmt_ctx) {
            avformat_close_input(&fmt_ctx);
        }
        avformat_free_context(fmt_ctx);

        return -1;
    }

    AVPacket packet;

    int ret = av_read_frame(fmt_ctx, &packet);
    if (ret < 0) {
        //printf("read: %d (%s)\n", ret, av_err2str(ret));
    } else {
        AVRational *tb = &fmt_ctx->streams[packet.stream_index]->time_base;

        av_packet_unref(&packet);
    }
    if (avio_ctx) {
        av_freep(&avio_ctx->buffer);
    }
    avio_context_free(&avio_ctx);

    if (fmt_ctx) {
        avformat_close_input(&fmt_ctx);
    }
    avformat_free_context(fmt_ctx);

    return -1;
}


@end
