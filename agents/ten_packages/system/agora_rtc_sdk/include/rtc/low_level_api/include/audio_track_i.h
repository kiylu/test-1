//
//  Agora Media SDK
//
//  Created by Rao Qi in 2019.
//  Copyright (c) 2019 Agora IO. All rights reserved.
//
#pragma once

#include <memory>

#include "AgoraRefPtr.h"
#include "AgoraBase.h"

#include "NGIAgoraAudioTrack.h"

#include "track_stat_i.h"
#include "video_config_i.h"

namespace agora {
namespace rtc {

class AudioState;
class AudioNodeBase;
struct PacketStats;

class ILocalAudioTrackEx : public ILocalAudioTrack {
 public:
  enum DetachReason { MANUAL, TRACK_DESTROY, MIXER_DESTROY };
  struct DetachOption {
    bool sync_destroy;
  };

 public:
  ILocalAudioTrackEx() {}
  virtual ~ILocalAudioTrackEx() {}

  virtual void attach(agora_refptr<agora::rtc::AudioState> audioState,
                      std::shared_ptr<AudioNodeBase> audioNetworkSink, uint32_t sourceId) = 0;
  virtual void detach(DetachReason reason) = 0;

  virtual void setMaxBufferedAudioFrameNumber(int number) = 0;

  virtual void setAudioFrameSendDelayMs(int32_t delay_ms) {}

  virtual int ClearSenderBuffer() {
    return -ERR_NOT_SUPPORTED;
  }

  virtual int setExtraDelay(int delay_ms) {
    return -ERR_NOT_SUPPORTED;
  }

  virtual bool getStatistics(PacketStats& stats) { return true; }

  virtual bool isMediaPacketTrack() { return false; }

  virtual bool isEncodedFrameTrack() { return false; }

  virtual void setDefaultAudioState(bool isDefaultAudioState) { return; };

  virtual int setDetachOption(DetachOption& option) {
    return -ERR_NOT_SUPPORTED;
  }
  
  virtual int enableMusicMode(bool enable) {
    return -ERR_NOT_SUPPORTED;
  }
};

class IRemoteAudioTrackEx : public IRemoteAudioTrack {
  using RemoteAudioEvents = StateEvents<REMOTE_AUDIO_STATE, REMOTE_AUDIO_STATE_REASON>;  
 public:
  IRemoteAudioTrackEx() : notifier_(REMOTE_AUDIO_STATE_STOPPED) {}

  virtual ~IRemoteAudioTrackEx() {}

  void NotifyTrackStateChange(uint64_t ts, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason) {
    notifier_.Notify(ts, state, reason);
  }

  virtual void SetExternalJitterInfo(int32_t audio_jitter95, int32_t video_jitter95, bool receiving_video) = 0;
    
  RemoteAudioEvents GetEvents() {
    return notifier_.GetEvents();
  }

  virtual int GetAudioLevel() { return 0; }
 protected:
  StateNotifier<REMOTE_AUDIO_STATE, REMOTE_AUDIO_STATE_REASON> notifier_;
};

}  // namespace rtc
}  // namespace agora
