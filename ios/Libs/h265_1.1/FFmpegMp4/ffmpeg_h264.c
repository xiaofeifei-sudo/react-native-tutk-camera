//
//  ffmpeg_h264.c
//  IPCAM_oa
//
//  Created by apple on 2018/12/25.
//  Copyright © 2018 TUTK. All rights reserved.
//

#include "ffmpeg_h264.h"

//视频帧设置参数
int ptsInc = 0;

//音频帧设置参数
int ptsAac = 0;
int waitkey = 1;

/**
 *录制mp4的上下文
 */
AVFormatContext* m_pOc;



//音频编码后的模型
AVStream *audioStream;

//视频编码后的模型
AVStream *videoStream;




int getVopType( const void *p, int len )
{
    if ( !p || 6 >= len )
        return -1;
    unsigned char *b = (unsigned char*)p;
    // Verify NAL marker
    if ( b[ 0 ] || b[ 1 ] || 0x01 != b[ 2 ] )
    {   b++;
        if ( b[ 0 ] || b[ 1 ] || 0x01 != b[ 2 ] )
            return -1;
    } // end if
    b += 3;
    // Verify VOP id
    if ( 0xb6 == *b )
    {
        b++;
        return ( *b & 0xc0 ) >> 6;
    } // end if
    switch( *b )
    {
        case 0x65 : return 0;
        case 0x61 : return 1;
        case 0x01 : return 2;
    } // end switch
    return -1;
}


/**
 *为初始化视频、音频编码器
 */
AVStream *add_stream(AVFormatContext *oc, AVCodec **codec, enum AVCodecID codec_id,unsigned long width)
{
    AVCodecContext *c;
    AVStream *ost;
    
    *codec = avcodec_find_encoder(codec_id);
    if (!(*codec)) {
        fprintf(stderr, "Could not find encoder for '%s'\n",
                avcodec_get_name(codec_id));
        exit(1);
    }
    ost = avformat_new_stream(oc, *codec);
    if (!ost) {
        fprintf(stderr, "Could not allocate stream\n");
        exit(1);
    }
    ost->id = oc->nb_streams-1;
    c = ost->codec;
    ost->start_time =0;
    
    /**
     *设置音频编码器参数
     */
    switch ((*codec)->type) {
        case AVMEDIA_TYPE_AUDIO:
            c->codec_id = codec_id;
            c->sample_fmt  = AV_SAMPLE_FMT_S16;
            c->bit_rate    = 8000;
            c->sample_rate = 8000;
            c->channels = 1;
            c->block_align = 0;
            c->profile = LOW;
            c->channel_layout = AV_CH_LAYOUT_MONO;

            ost->time_base = (AVRational){ 1, c->sample_rate };
            c->time_base = ost->time_base;
            
            /**
             *用来计算时间戳
             */
            c->time_base.den = 125;
            c->time_base.num = 8;

            
            break;
            
        /**
          *设置视频编码器参数
          */
        case AVMEDIA_TYPE_VIDEO:
            c->codec_id = codec_id;
            c->bit_rate = 44100;
            /* Resolution must be a multiple of two. */
            c->width    = (int)width;
            c->height   = (int)(width *9)/16;

            ost->time_base = (AVRational){ 1, 20 };
            c->time_base       = ost->time_base;
            
            /**
             *用来计算时间戳
             */
            c->time_base.den = 219;
            c->time_base.num = 11;
            
            c->gop_size      = 12; /* emit one intra frame every twelve frames at most */
            c->pix_fmt       = AV_PIX_FMT_YUV420P;
            c->max_b_frames = 2;
            
            if (c->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
                c->max_b_frames = 2;
            }
            if (c->codec_id == AV_CODEC_ID_MPEG1VIDEO) {
 
                c->mb_decision = 2;
            }
        
            break;
        default:
            break;
    
    }


    return ost;
}

/**
 *打开视频编码器
 */
void open_video(AVFormatContext *oc, AVCodec *codec, AVStream *st)
{
    int ret;
    AVCodecContext *c = st->codec;
    c->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    /* open the codec */
    ret = avcodec_open2(c, codec, NULL);
    if (ret < 0)
    {
        printf("could not open video codec");
        //exit(1);
    }
}

/**
 *打开音频编码器
 */
void open_audio(AVFormatContext *oc, AVCodec *codec, AVStream *st)
{
    int ret;
    AVCodecContext *c = st->codec;
    c->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    /* open the codec */
    ret = avcodec_open2(c, codec, NULL);
    if (ret < 0)
    {
        printf("could not open video codec");
        //exit(1);
    }
}

/**
 *创建mp4文件
 */
int CreateMp4ForFFmpeg(const char* filename,unsigned long width)
{
    
    //必须重新归零
    ptsInc = 0;
    ptsAac = 0;
    waitkey = -1;
    
    int ret; // 成功返回0，失败返回1
    int haveVideo = 0;
    int haveAudio = 0;
    const char* pszFileName = filename;
    AVFormatContext* context;
    AVOutputFormat* fmt;
    
    /**
     *音视频编码器
     */
    AVCodec *video_codec;
    AVCodec *audio_codec;
    
    AVStream *m_pVideoSt;
    AVStream *m_pAudioSt;
    
    av_register_all();
    
    avformat_alloc_output_context2(&context, NULL, NULL, pszFileName);
    if (!context)
    {
        printf("Could not deduce output format from file extension: using MPEG. \n");
//        avformat_alloc_output_context2(&context, NULL, "mpeg", pszFileName);
        return 0;
    }
    
    // 强制指定 264 编码
    context->oformat->video_codec = AV_CODEC_ID_H264;
    context->oformat->audio_codec = AV_CODEC_ID_AAC;

    if (!context)
    {
        ret = AVERROR_UNKNOWN;
        return ret;
    }
    fmt = context->oformat;
    
    
    if (fmt->video_codec != AV_CODEC_ID_NONE)
    {
        printf("1111111111111111add_stream\n");
        m_pVideoSt = add_stream(context, &video_codec, fmt->video_codec,width);
        haveVideo = 1;
    }
    if (haveVideo)
    {
        printf("1111111111111111open_video\n");
        open_video(context, video_codec, m_pVideoSt);
    }
    videoStream = m_pVideoSt;
    
    if (fmt->audio_codec != AV_CODEC_ID_NONE) {
        
        printf("2222222222222222add_stream\n");
        m_pAudioSt = add_stream(context, &audio_codec, fmt->audio_codec,width);
        haveAudio = 1;
    }
    if (haveAudio) {
        
        printf("222222222222222open_video\n");
        open_audio(context, audio_codec, m_pAudioSt);
    }

    audioStream = m_pAudioSt;
    
    printf("==========Output Information==========\n");
    av_dump_format(context, 0, pszFileName, 1);
    printf("======================================\n");
    /* open the output file, if needed */
    if (!(fmt->flags & AVFMT_NOFILE))
    {
        ret = avio_open(&context->pb, pszFileName, AVIO_FLAG_WRITE);
        if (ret < 0)
        {
            printf("could not open %s\n", pszFileName);
            ret = AVERROR_UNKNOWN;
        }
    }

    
    /* Write the stream header, if any */
    //写入头文件
    ret = avformat_write_header(context, NULL);
    if (ret < 0)
    {
        printf("Error occurred when opening output file");
        ret = AVERROR_UNKNOWN;
    }
    
    m_pOc = context;
    
    return ret;
}

/* write h264 data to mp4 file
 * 写入h264
 */
void WriteVideoForH264(void* data, int nLen,unsigned char *sps_pps,int sps_ppsLen,unsigned long width)
{
    
    int ret;
    
    if (data ==NULL) {
        
        return;
    }
    
    if (sps_pps == NULL) {
        
        return;
    }
    
    AVStream *pst = videoStream;
    // Init packet
    AVPacket pkt;
    // 我的添加，为了计算pts
    AVCodecContext *c = pst->codec;
    
    /**
     *设置extradata(即为sps和pps)
     */
    printf("!!!!!!!!!!!");
    pst->codecpar->extradata_size = sps_ppsLen;
    pst->codecpar->extradata =  (uint8_t*)av_mallocz(pst->codecpar->extradata_size + AV_INPUT_BUFFER_PADDING_SIZE);
    if (pst->codecpar->extradata == NULL) {
        printf("could not av_malloc the video params extradata!\n");
    }
    pst->codecpar->extradata = sps_pps;
    
    
    av_init_packet( &pkt );
    pkt.flags = ( 0 >= getVopType( data, nLen ) ) ? AV_PKT_FLAG_KEY : 0;
    pkt.stream_index = pst->index;
    pkt.data = (uint8_t*)data;
    pkt.size = nLen;
    // Wait for key frame
    if ( waitkey )
        if ( 0 == ( pkt.flags & AV_PKT_FLAG_KEY ) )
            return ;
        else
            waitkey = 0;
    
    /**
     *pts和dts为时间戳
     */
    if (width == 1920) {
        
        pkt.pts = (av_rescale_q((ptsInc++)*2, c->time_base,pst->time_base) *2) /3;
        
    }else if (width == 640){
        
        pkt.pts = av_rescale_q((ptsInc++)*2, c->time_base,pst->time_base) /2;
    }else{
        
        pkt.pts = av_rescale_q((ptsInc++)*2, c->time_base,pst->time_base);
    }
    printf("------234567---%lu",width);
    
    pkt.dts = pkt.pts;
    pkt.duration = av_rescale_q(pkt.duration,c->time_base, pst->time_base);
    pkt.pos = -1;
    printf("-------+++++++%lld--%lld--%lld\n",pkt.pts,pkt.dts,pkt.duration);
    printf("---pkt.pts=%lld\n",pkt.pts);
    
    /**
     *将数据包写入上下文
     */
    ret = av_interleaved_write_frame( m_pOc, &pkt);
    
    av_free_packet(&pkt);
    if (ret < 0)
    {
        printf("cannot write frame");
    }
}

/**
 *写入aac
 */
void writeVideoForAAC(void *data, int nLen){
    
    int ret;
    
    AVStream *pst = audioStream;
    // Init packet
    AVPacket pkt;
    
    AVCodecContext *c = pst->codec;
    
    //初始化AVpacket
    av_init_packet( &pkt );
    pkt.flags = ( 0 >= getVopType( data, nLen ) ) ? AV_PKT_FLAG_KEY : 0;;
    pkt.stream_index = pst->index;
    pkt.data = (uint8_t*)data;
    pkt.size = nLen;
    // Wait for key frame
    if ( waitkey )
        if ( 0 == ( pkt.flags & AV_PKT_FLAG_KEY ) )
            return ;
        else
            waitkey = 0;
    
    /**
     *计算pts和dts(时间戳)
     */
    pkt.pts = av_rescale_q((ptsAac++)*2, c->time_base,pst->time_base);
    pkt.dts = pkt.pts;
    pkt.duration = av_rescale_q(pkt.duration,c->time_base, pst->time_base);
    pkt.pos = -1;
    printf("~~~~~~~~~+++++++%lld--%lld--%lld\n",pkt.pts,pkt.dts,pkt.duration);
    printf("pkt.size=%d\n",pkt.size);

    /**
     *将数据包写入上下文
     */
    ret = av_interleaved_write_frame( m_pOc, &pkt);
    
    av_free_packet(&pkt);
    if (ret < 0)
    {
        printf("cannot write frame");
    }
}


/**
 *关闭mp4文件
 */
void CloseMp4ForH264()
{
    
    if (m_pOc)
        
        /**
         *将上下文写入mp4文件
         */
        av_write_trailer(m_pOc);
    if (m_pOc && !(m_pOc->oformat->flags & AVFMT_NOFILE))
        
        /**
         *关闭mp4文件
         */
        avio_close(m_pOc->pb);
    
    if (m_pOc)
    {
        //需要释放
//        avformat_free_context(m_pOc);
//        m_pOc = NULL;

    }
    
}




