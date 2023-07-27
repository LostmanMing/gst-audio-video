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
typedef struct
{
    GMainLoop* loop;
    GstElement* source;
    GstElement* sink;
} ProgramData;

class SourceMgr{
private:

public:
    virtual ~SourceMgr(){}

    virtual void Init() = 0;

    virtual GstFlowReturn Excute(GstElement* bin) = 0;

    ProgramData* data;
protected:

    explicit SourceMgr(ProgramData* data): data(data){}
    //    std::function< GstFlowReturn(GstElement* , ProgramData* )> gst_cb;

};
#endif //GST_AUDIO_VIDEO_SOURCE_MANAGE_H
