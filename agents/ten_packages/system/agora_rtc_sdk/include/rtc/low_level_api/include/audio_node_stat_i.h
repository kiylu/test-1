//
//  Agora Engine SDK
//
//  Created by ChenZhipeng in 2022-08.
//  Copyright (c) 2022 Agora.io. All rights reserved.
//
#pragma once


#include <stddef.h>

#include <algorithm>
#include <cstring>
#include <map>
#include <string>

namespace agora {
namespace rtc {

enum class AUDIO_FRAME_SOURCE_TYPE {
  UNKNOWN = 0,
  RECORD = 1 << 0,
  PUSH_DIRECT = 1 << 1,
  PUSH_EXTERNAL = 1 << 2,
  SIMPLE_MEDIA_PLAYER = 1 << 3,
  FFMPEG_MEDIA_PLAYER = 1 << 4,
  KNOWN_TYPE_COUNT = 5,
};

struct AudioFrameHandleInfo {
  enum AUDIO_UPLINK_HANDLE_TIMING {
    FRAME_PTS,
    DATA_READY,
    FORMAT_FRAME,
    POST_TO_ENCODER_QUEUE,
    PRE_ENCODE,
    ENCODED,
    POST_TO_SEND_QUEUE,
    READY_SEND,
    VOS_SEND,
    TIMING_COUNT,
  };
  int64_t time_us[TIMING_COUNT]{};
  int source_type = static_cast<int>(AUDIO_FRAME_SOURCE_TYPE::UNKNOWN);

  bool valid() const {
    return (source_type >= 0 && time_us[FORMAT_FRAME] > 0 &&
            time_us[VOS_SEND] > time_us[FORMAT_FRAME]);
  }

  static std::string getAudioFrameSourceName(int type) {
    std::map<int, const char*> source_name = {
        {static_cast<int>(AUDIO_FRAME_SOURCE_TYPE::UNKNOWN), "unknown"},
        {static_cast<int>(AUDIO_FRAME_SOURCE_TYPE::RECORD), "record"},
        {static_cast<int>(AUDIO_FRAME_SOURCE_TYPE::PUSH_DIRECT), "push-direct"},
        {static_cast<int>(AUDIO_FRAME_SOURCE_TYPE::PUSH_EXTERNAL),
         "push-external"},
        {static_cast<int>(AUDIO_FRAME_SOURCE_TYPE::SIMPLE_MEDIA_PLAYER),
         "simple_media_player"},
        {static_cast<int>(AUDIO_FRAME_SOURCE_TYPE::FFMPEG_MEDIA_PLAYER),
         "ffmpeg_media_player"},
    };

    std::string name;
    int cnt = static_cast<int>(AUDIO_FRAME_SOURCE_TYPE::KNOWN_TYPE_COUNT);
    for (int i = 0; i < cnt; ++i) {
      if (type & (1 << i)) {
        auto iter = source_name.find(1 << i);
        if (iter != source_name.end()) {
          if (!name.empty()) {
            name.push_back('|');
          }
          name.append(iter->second);
        }
      }
    }
    if (name.empty()) {
      return "unknown";
    }
    return name;
  }
};

}  // namespace rtc
}  // namespace agora
