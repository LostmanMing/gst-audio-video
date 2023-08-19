//
// Created by 迷路的男人 on 2023/7/27.
//

#ifndef ARCH_STREAMER_GST_CALL_BACK_FUNCS_H
#define ARCH_STREAMER_GST_CALL_BACK_FUNCS_H
#include "source_manage.h"
static  GstFlowReturn sourceCallback(GstElement* sink, gpointer data) {
    return ((SourceMgr*)data)->Excute(sink);
}
#endif //ARCH_STREAMER_GST_CALL_BACK_FUNCS_H

