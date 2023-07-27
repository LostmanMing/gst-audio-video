//
// Created by 迷路的男人 on 2023/7/26.
//

#ifndef ARCH_STREAMER_AUDIO_MANAGE_H
#define ARCH_STREAMER_AUDIO_MANAGE_H
#include<source_manage.h>
#include<common.h>
class AudioMgr : public SourceMgr{
public:
    explicit AudioMgr(ProgramData* data) : SourceMgr(data){}

    void Init() override;

    GstFlowReturn Excute(GstElement *bin) override;

private:

    GstElement* audio_sink = nullptr;
    GstElement* audio_src = nullptr;
};


#endif //ARCH_STREAMER_AUDIO_MANAGE_H
