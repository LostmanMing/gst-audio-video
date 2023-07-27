//
// Created by 迷路的男人 on 2023/7/25.
//

#include "video_manage.h"

GstFlowReturn VideoMgr::Excute(GstElement *bin) {
    GstSample* sample = gst_app_sink_pull_sample(GST_APP_SINK(bin));
    GstElement* source;
    GstFlowReturn ret;
    if (sample) {
        GstBuffer* buffer = gst_sample_get_buffer(sample);
        GstMapInfo info;
        if (gst_buffer_map(buffer, &info, GST_MAP_READ)) {
            // 在这里处理 BGRA 数据
            // info.data 包含 BGRA 图像数据
            // info.size 是数据的大小
            // TODO: 处理 BGRA 数据的逻辑
            //Sleep(25);
            //模拟图像推理,并打印推理时间
            struct timeval start,end;
            gettimeofday(&start, NULL);
            // g_usleep(1000);
            float tmp = 2;
            for(int j = 0; j < 500;j++)
                for(int i = 0;i < 10000;i++){
                    tmp = (tmp / 2 + 1)*2-1;
                }
            gettimeofday(&end, NULL);
            float runtime = ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec)) / 1000;
            spdlog::debug("video runtime:{}ms",runtime);
            //模拟图像绘图，模拟检查对数据进行修改是否成功
            // int c = buffer->pts%1000;
            // int off_set = 1920 * 4 * c + 4 * 100;
            // unsigned char* d = info.data+off_set;
            // unsigned char color[4] = { 0,0,0,1 };
            // for (int i = 0; i < 100; i++) {
            //     memcpy(d, color, sizeof(color));
            //     d += sizeof(color);
            // }
            // off_set += 1920 * 4;
            // d = info.data + off_set;
            // for (int i = 0; i < 100; i++) {
            //     memcpy(d, color, sizeof(color));
            //     d += sizeof(color);
            // }
            // g_print("video size: %d\n",info.size);


            gst_buffer_unmap(buffer, &info);
        }
    }
    source = gst_bin_get_by_name(GST_BIN(data->sink), "video_src");
    if(source){
        ret = gst_app_src_push_sample(GST_APP_SRC(source), sample);
        gst_object_unref(source);
    }

    /* we don't need the appsink sample anymore */
    gst_sample_unref(sample);
    return ret;
}

void VideoMgr::Init() {
    video_sink = gst_bin_get_by_name(GST_BIN(data->source), "video_sink");
    g_signal_connect(video_sink, "new-sample",
                     G_CALLBACK(sourceCallback), this);
    //指定数据类型，宽高不要指定死，能动态设置宽高
    g_object_set(
            G_OBJECT(video_sink),
            "sync", TRUE,
            "emit-signals", TRUE,
            "caps", gst_caps_new_simple("video/x-raw",
                    // "width", G_TYPE_INT, 1920,
                    // "height", G_TYPE_INT, 1080,
                    // "framerate", GST_TYPE_FRACTION, 10, 1,
                                        "format", G_TYPE_STRING, "BGRx", NULL),
            NULL
    );
    gst_object_unref(video_sink);

    video_src = gst_bin_get_by_name(GST_BIN(data->sink), "video_src");
    /* 插件的 "format" 属性为 GST_FORMAT_TIME。这意味着 "video_src" 插件将会按照时间来处理数据，而不是按照字节或帧数。
     * 这对于同步视频流是很重要的，因为它允许 GStreamer 根据时间戳来正确地调度视频帧的处理和播放。
     * time-based format
     * */
    g_object_set(video_src, "format", GST_FORMAT_TIME, NULL);

    /* block 属性设置后，如果appsrc内部队列已满，将阻塞push-buffer、push-buffer-list 或 end-of-stream的调用 */
    /* g_object_set (video_src, "block", TRUE, NULL); */
    gst_object_unref(video_src);
}
