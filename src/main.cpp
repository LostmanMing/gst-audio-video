//
// Created by 迷路的男人 on 2023/7/24.
//
#include <fstream>
#include <StreamMgr.h>
#include <json/json.h>

static void Parse(PipelineOptions& config, std::string& config_path){
    Json::Value root;
    Json::Reader g_reader;
    std::ifstream in(config_path,std::ios::binary);
    g_reader.parse(in, root);
    if(root.isMember("type")){
        if(root["type"] == "rtmp") config.deviceType = DEVICE_TYPE::RTMP;
        else if(root["type"] == "file") config.deviceType = DEVICE_TYPE::FILE;
    }
    if(root.isMember("decode_config")){
        Json::Value decode_config = root["decode_config"];
        if(decode_config.isMember("stream")){
            Json::Value stream = decode_config["stream"];
            config.rtsp_uri = stream["uri"].asString();
            spdlog::debug("---Decoder: rtsp_uri: {}",config.rtsp_uri);
        }
        if(decode_config.isMember("video_sink")){
            Json::Value video_sink = decode_config["video_sink"];
            config.video_sink_sync = video_sink["sync"].asBool();
            config.video_sink_emit_signals = video_sink["emit-signals"].asBool();
            config.sink_format = video_sink["format"].asString();
            config.height = video_sink["height"].asInt();
            config.width = video_sink["width"].asInt();
        }
        if(decode_config.isMember("audio_sink")){
            Json::Value audio_sink = decode_config["audio_sink"];
            config.audio_sink_sync = audio_sink["sync"].asBool();
            config.audio_sink_emit_signals = audio_sink["emit-signals"].asBool();

        }
    }
    if(root.isMember("encode_config")){
        Json::Value encode_config = root["encode_config"];
        config.rtmp_uri = encode_config["stream"]["uri"].asString();
        spdlog::debug("---Eecoder: rtmp_uri: {}",config.rtmp_uri);
    }
}

int main(){
    spdlog::set_level(spdlog::level::debug);
    std::string CONFIG_PATH = "../config/rtsp_rtmp.json";
    PipelineOptions opts;
    Parse(opts,CONFIG_PATH);
    std::unique_ptr<StreamMgr> smgr = std::make_unique<StreamMgr>(opts);

    smgr->Init();

    smgr->Start();

    smgr->Realse();
    return 0;
}

