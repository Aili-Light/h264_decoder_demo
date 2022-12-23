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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "decode.h"

bool g_signal_recieved = false;

void int_handler(int sig)
{
    // g_signal_recieved = true;
    // printf("STOP SIGNAL\n");
    // alg_sdk_decoder_stop();
    // alg_sdk_decoder_deinit();

    /* terminate program */
    exit(sig);
}

void callback(void *p)
{
    alg_sdk_gst_decoder_t* decoder = (alg_sdk_gst_decoder_t*)p;
    printf("*****Decode Image [Width:%d] [Height:%d] [TS:%ld]\n", decoder->width, decoder->height, decoder->timestamp);
    char filename[1024];
    sprintf(filename, "data/image_%08d_%16ld.bmp", decoder->frame_index, decoder->timestamp);
    alg_sdk_save_image_bmp(filename, decoder->payload, decoder);
}

int main(int argc, char **argv)
{
    signal(SIGINT, int_handler);

    /* Launch Decoder */
    printf("------------Launch Decoder\n");

    char file_name[1024];
    if (argc == 2)
    {
        strcpy(file_name, argv[1]);
        printf("Decoder filename = %s\n", file_name);
    }
    else
    {
        printf("ERROR ! Usuage : ./decoder [FILENAME]\n");
        exit(0);
    }
    
    /* Init Decoder */
    int ret = alg_sdk_decoder_init(file_name, callback, DECODER_AVH264, DECODER_HAVE_SEI);
    if (ret>0)
    {
        printf("ERROR! Init Decoder Failed! [CODE:%d]\n", ret);
        exit(0);
    }

    /* Start Decoding */
    alg_sdk_decoder_start();

    while (g_signal_recieved == false)
    {
        usleep(100);
    }

    printf("Stop Decoder.");
    return 0;
}
