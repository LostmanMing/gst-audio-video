//
// Created by 迷路的男人 on 2023/7/26.
//

#include "audio_manage.h"

// // 计算音频数据的分贝值
double calculate_decibel(const gfloat* audio_data, gsize size) {
    // 计算 RMS 值
    double rms_sum = 0;
    for (gsize i = 0; i < size; ++i) {
        rms_sum += audio_data[i] * audio_data[i];
    }
    double rms = std::sqrt(rms_sum / size);

    // 计算分贝值
    double db = 20 * std::log10(rms);
    return db;
}

double getPcmDB(const unsigned char *pcmdata, size_t size) {

    double db = 0;
    short int value = 0;
    double sum = 0;
    for(int i = 0; i < size; i += 2)
    {
        memcpy(&value, pcmdata+i, 2); //获取2个字节的大小（值）
        sum += abs(value); //绝对值求和
    }
    sum = sum / (size / 2); //求平均值（2个字节表示一个振幅，所以振幅个数为：size/2个）
    if(sum > 0)
    {
        db = 20.0*log10(sum);
    }
    return db;
}

GstFlowReturn AudioMgr::Excute(GstElement *bin) {
    GstSample* sample= gst_app_sink_pull_sample(GST_APP_SINK(bin));;
    GstElement* source;
    GstFlowReturn ret;
    /* get the sample from appsink */
    if (sample) {
        GstBuffer* buffer = gst_sample_get_buffer(sample);
        GstMapInfo info;
        if (gst_buffer_map(buffer, &info, GST_MAP_READ)) {
            // 处理音频数据
            // info.data 包含 音频数据
            // info.size 是数据的大小
            // TODO: 处理 音频 数据的逻辑
            // float db = calculate_decibel((gfloat*)info.data, info.size/(sizeof(gfloat)));
            // 计算 RMS 值
            // gfloat *audio_data = (gfloat*)info.data;
            // int audio_size = info.size;
            // double rms_sum = 0;
            // for (gsize i = 0; i < audio_size / sizeof(gfloat); ++i) {
            //     rms_sum += audio_data[i] * audio_data[i];
            // }
            // double rms = std::sqrt(rms_sum / (audio_size / sizeof(gfloat)));

            // 计算分贝值
            // double db = 20 * std::log10(rms);
            double db = getPcmDB(info.data,info.size);
            // double db = getPcmDB(info.data,info.size);
            spdlog::debug("audio db:{:.2f} size:{}",db,info.size);
            GstCaps* caps = gst_sample_get_caps(sample);
            GstStructure* structure = gst_caps_get_structure(caps, 0);

            //保存十秒左右的音频数据,验证音频数据
            // static int index=0;
            // static FILE *file;
            // if(index==0){
            //     file = fopen("./res.aac","wb");
            //     fwrite(info.data,info.size,1,file);
            // }else if(index < 100){
            //     fwrite(info.data,info.size,1,file);
            //     g_print("index:%d\n",index);
            // }else if(index==100){
            //     fclose(file);
            // }
            // index++;

            // 获取音频格式
            const gchar* audio_format = gst_structure_get_string(structure, "format");
            // 获取采样率
            gint audio_rate = 0;
            gst_structure_get_int(structure, "rate", &audio_rate);
            // 获取声道数
            gint audio_channels = 0;
            gst_structure_get_int(structure, "channels", &audio_channels);
            // g_print("format:%s rate:%d channels:%d\n",audio_format,audio_rate,audio_channels);
            gst_buffer_unmap(buffer, &info);
        }
    }
    /* get source an push new sample */
    source = gst_bin_get_by_name(GST_BIN(data->sink), "audio_src");
    ret = gst_app_src_push_sample(GST_APP_SRC(source), sample);
    gst_object_unref(source);

    /* we don't need the appsink sample anymore */
    gst_sample_unref(sample);
    return ret;
}

void AudioMgr::Init() {
    audio_sink = gst_bin_get_by_name(GST_BIN(data->source), "audio_sink");
    g_signal_connect(audio_sink, "new-sample",
                     G_CALLBACK(sourceCallback), this);
    g_object_set(
            G_OBJECT(audio_sink),
            "sync", TRUE,
            "emit-signals", TRUE,
            "caps", gst_caps_new_simple("audio/x-raw",
                                        "format", G_TYPE_STRING, "S16LE",
                                        "rate", G_TYPE_INT, 44100,
                                        "channels", G_TYPE_INT, 2,
                                        NULL),
            NULL
    );
    gst_object_unref(audio_sink);

    audio_src = gst_bin_get_by_name(GST_BIN(data->sink), "audio_src");
    /* configure for time-based format */
    // g_object_set(audio_src, "format", GST_FORMAT_TIME, NULL);
    g_object_set(
            G_OBJECT(audio_src),
            "format", GST_FORMAT_TIME,
            "caps", gst_caps_new_simple("audio/x-raw",
                                        "format", G_TYPE_STRING, "S16LE",
                                        "rate", G_TYPE_INT, 44100,
                                        "channels", G_TYPE_INT, 2,
                                        NULL),
            NULL
    );

    /* g_object_set (audio_src, "block", TRUE, NULL); */
    gst_object_unref(audio_src);
}


