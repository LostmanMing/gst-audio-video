//
// Created by 迷路的男人 on 2023/7/24.
//

#ifndef ARCH_STREAMER_COMMON_H
#define ARCH_STREAMER_COMMON_H

enum class DEVICE_TYPE{
    FILE,RTMP
};
enum class IMAGE_FORMAT{
    JPEG,BGRA,BGR,GRAY16,GRAY8,RGB,RGBA
};
class PipelineOptions{
public:
    IMAGE_FORMAT imageFormat;
    DEVICE_TYPE deviceType;
    int frameRate;
    int width;
    int height;
    std::string rtsp_uri;
    std::string rtmp_uri;
    bool video_sink_sync;
    bool video_sink_emit_signals;
    bool audio_sink_sync;
    bool audio_sink_emit_signals;
    std::string sink_format;

};
typedef struct
{
    GMainLoop* loop;
    GstElement* source;
    GstElement* sink;
} ProgramData;

#endif //ARCH_STREAMER_COMMON_H
