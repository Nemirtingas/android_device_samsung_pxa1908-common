/*
** Copyright 2011, The Android Open-Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

//#define LOG_NDEBUG 0
#define LOG_TAG "shimmed_echo_reference"

#include <errno.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdlib.h>

#include <log/log.h>
#include <system/audio.h>
#include <audio_utils/resampler.h>
#include <audio_utils/echo_reference.h>

// echo reference state: bit field indicating if read, write or both are active.
enum state {
    ECHOREF_IDLE = 0x00,        // idle
    ECHOREF_READING = 0x01,     // reading is active
    ECHOREF_WRITING = 0x02      // writing is active
};

struct echo_reference {
    struct echo_reference_itfe itfe;
    int status;                     // init status
    uint32_t state;                 // active state: reading, writing or both
    audio_format_t rd_format;       // read sample format
    uint32_t rd_channel_count;      // read number of channels
    uint32_t rd_sampling_rate;      // read sampling rate in Hz
    size_t rd_frame_size;           // read frame size (bytes per sample)
    audio_format_t wr_format;       // write sample format
    uint32_t wr_channel_count;      // write number of channels
    uint32_t wr_sampling_rate;      // write sampling rate in Hz
    size_t wr_frame_size;           // write frame size (bytes per sample)
    void *buffer;                   // main buffer
    size_t buf_size;                // main buffer size in frames
    size_t frames_in;               // number of frames in main buffer
    void *wr_buf;                   // buffer for input conversions
    size_t wr_buf_size;             // size of conversion buffer in frames
    size_t wr_frames_in;            // number of frames in conversion buffer
    size_t wr_curr_frame_size;      // number of frames given to current write() function
    void *wr_src_buf;               // resampler input buf (either wr_buf or buffer used by write())
    struct timespec wr_render_time; // latest render time indicated by write()
                                    // default ALSA gettimeofday() format
    int32_t  playback_delay;        // playback buffer delay indicated by last write()
    int16_t prev_delta_sign;        // sign of previous delay difference:
                                    //  1: positive, -1: negative, 0: unknown
    uint16_t delta_count;           // number of consecutive delay differences with same sign
    pthread_mutex_t lock;                      // mutex protecting read/write concurrency
    pthread_cond_t cond;                       // condition signaled when data is ready to read
    struct resampler_itfe *resampler;          // input resampler
    struct resampler_buffer_provider provider; // resampler buffer provider
};

#include <dlfcn.h>

void *_lib;
int (*stock_create_echo_reference)(audio_format_t rdFormat,
                            uint32_t rdChannelCount,
                            uint32_t rdSamplingRate,
                            audio_format_t wrFormat,
                            uint32_t wrChannelCount,
                            uint32_t wrSamplingRate,
                            struct echo_reference_itfe **echo_reference);
void (*stock_release_echo_reference)(struct echo_reference_itfe *echo_reference);

extern "C" int create_echo_reference(uint64_t rdFormat,
                          uint32_t rdChannelCount,
                          uint32_t rdSamplingRate,
                          uint64_t wrFormat,
                          uint32_t wrChannelCount,
                          uint32_t wrSamplingRate,
                          uint32_t wrMaxFrameCount,
                          struct echo_reference_itfe **echo_reference)
{
    return stock_create_echo_reference((audio_format_t)rdFormat, rdChannelCount, rdSamplingRate, (audio_format_t)wrFormat, wrChannelCount, wrSamplingRate, echo_reference);
}
 
extern "C" void release_echo_reference(struct echo_reference_itfe *echo_reference)
{
    stock_release_echo_reference(echo_reference);
}

__attribute__((constructor)) void __so_load__() 
{
    _lib = dlopen("libaudioutils.so", RTLD_NOW);
    if( _lib == NULL
      || (*(int*)&stock_create_echo_reference = (int)dlsym(_lib, "create_echo_reference")) == 0 
      || (*(int*)&stock_release_echo_reference = (int)dlsym(_lib, "release_echo_reference")) == 0
      )
    {
        ALOGE("Failed to load libaudioutils from the shim libaudioutils.");
        exit(-1);
    }
}

__attribute__((destructor)) void __so_unload__()
{
    dlclose(_lib);
}
