//
// Created by 迷路的男人 on 2023/7/24.
//

#ifndef GST_AUDIO_VIDEO_STREAMMGR_H
#define GST_AUDIO_VIDEO_STREAMMGR_H
#include <gst/gst.h>
#include <sstream>
#include <common.h>
#include <spdlog/spdlog.h>
#include <audio_manage.h>
#include <video_manage.h>


class StreamMgr {
public:
    StreamMgr(PipelineOptions & opt) : opts(opt){}

    gboolean Init();

    gboolean Start();

    int Realse();
private:
    gboolean buildDecodeStr();

    ProgramData* data = nullptr;

    void setCaps();

    void checkBus(_GstElement* bin);

    gboolean buildEecodeStr();

    PipelineOptions opts;
    GstBus* bus = nullptr;
    std::unique_ptr<VideoMgr>  video;
    std::unique_ptr<AudioMgr>  audio;
};


#endif //GST_AUDIO_VIDEO_STREAMMGR_H
