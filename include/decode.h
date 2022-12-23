/*
 The MIT License (MIT)

Copyright (c) 2022 Aili-Light. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef __DECODE_H__
#define __DECODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <gst/gst.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MINGW32) && defined(BUILD_EXPORT)
    #ifdef ALG_SDK_EXPORT
        #define ALG_SDK_API __declspec(dllexport)
    #else
        #define ALG_SDK_API __declspec(dllimport)
    #endif // ALG_SDK_EXPORT
#else
    #define ALG_SDK_API extern
#endif // MINGW32

typedef void(*alg_sdk_callback_func)(void* p);
#define ALG_SDK_DECODER_STRING_SIZE 256

enum ALG_SDK_DECODER_TYPE
{
    DECODER_DEFAULT = 0, 
    DECODER_AVH264 = 0x01, 
    DECODER_NVH264 = 0x02, 
};

enum ALG_SDK_DECODER_METHOD
{
    DECODER_NO_SEI = 0, 
    DECODER_HAVE_SEI = 0x01, 
};

typedef struct _GstElement GstElement;
typedef struct _GstBus GstBus;
typedef struct _GstCaps GstCaps;

typedef struct alg_sdk_gst_decoder
{
    char launch_str[ALG_SDK_DECODER_STRING_SIZE * 4];
    char protocol[ALG_SDK_DECODER_STRING_SIZE];
    char encoder_h264[ALG_SDK_DECODER_STRING_SIZE];
    char file_location[ALG_SDK_DECODER_STRING_SIZE];
    char decoder_h264[ALG_SDK_DECODER_STRING_SIZE];

    int width;
    int height;
    int frame_rate;
    int format;
    int ch_id;
    int have_sei;
    uint32_t frame_index;
    uint64_t timestamp;
    uint8_t* payload;
    size_t img_size;

    bool need_data;
    bool need_sei_data;
    bool mStreaming;

    GstBus *mBus;
    GstElement *mIdentity;
    GstElement *mPipeline;
    GstCaps *mBufferCaps;
    GstElement *mAppSink;

} alg_sdk_gst_decoder_t;

ALG_SDK_API int alg_sdk_decoder_init(const char* filename, alg_sdk_callback_func consumer, ALG_SDK_DECODER_TYPE type, ALG_SDK_DECODER_METHOD method);
ALG_SDK_API int alg_sdk_decoder_start();
ALG_SDK_API void alg_sdk_decoder_stop();
ALG_SDK_API void alg_sdk_decoder_deinit();
ALG_SDK_API void alg_sdk_save_image_bmp(const char *filename, void *image_ptr, void *_decoder);

#ifdef __cplusplus
}
#endif
#endif