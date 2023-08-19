//
// Created by 迷路的男人 on 2023/7/26.
//

#ifndef ARCH_STREAMER_AUDIO_MANAGE_H
#define ARCH_STREAMER_AUDIO_MANAGE_H
#include<source_manage.h>
#include "gst_call_back_funcs.h"

class AudioMgr : public SourceMgr{
public:
    explicit AudioMgr(ProgramData* data,PipelineOptions &opts) : SourceMgr(data,opts){}

    /* 初始化音频管道属性 */
    void Init() override;

    /* 音频处理回调函数 */
    GstFlowReturn Excute(GstElement *bin) override;

private:
    double db;
    GstElement* audio_sink = nullptr;
    GstElement* audio_src = nullptr;
};


#endif //ARCH_STREAMER_AUDIO_MANAGE_H
