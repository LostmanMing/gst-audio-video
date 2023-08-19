//
// Created by 迷路的男人 on 2023/7/24.
//

#ifndef GST_AUDIO_VIDEO_SOURCE_MANAGE_H
#define GST_AUDIO_VIDEO_SOURCE_MANAGE_H
#include <gst/app/gstappsrc.h>
#include <gst/app/gstappsink.h>
#include "spdlog/spdlog.h"
#include <cmath>
#include <functional>
#include "common.h"


class SourceMgr{
private:

public:
    virtual ~SourceMgr(){}

    virtual void Init() = 0;

    virtual GstFlowReturn Excute(GstElement* bin) = 0;


protected:
    explicit SourceMgr(ProgramData* data,PipelineOptions &opts): src(data->source),sink(data->sink),opts(opts){}
    //    std::function< GstFlowReturn(GstElement* , ProgramData* )> gst_cb;
    PipelineOptions opts;
    GstElement* src = nullptr;
    GstElement* sink = nullptr;
};
#endif //GST_AUDIO_VIDEO_SOURCE_MANAGE_H
