//
// Created by 迷路的男人 on 2023/7/25.
//

#ifndef ARCH_STREAMER_VIDEO_MANAGE_H
#define ARCH_STREAMER_VIDEO_MANAGE_H
#include<source_manage.h>
#include<common.h>
#include <sys/time.h>

class VideoMgr :public SourceMgr{
public:
    explicit VideoMgr(ProgramData* data) : SourceMgr(data){}

    void Init() override;

    GstFlowReturn Excute(GstElement *bin) override;

private:

    GstElement* video_sink = nullptr;
    GstElement* video_src = nullptr;
};


#endif //ARCH_STREAMER_VIDEO_MANAGE_H
