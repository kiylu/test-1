//
//  Agora Media SDK
//
//  Created by Sting Feng in 2015-05.
//  Copyright (c) 2015 Agora IO. All rights reserved.
//
#pragma once

#include <string>
#include <vector>

#include "IAgoraService.h"
#include "NGIAgoraLocalUser.h"
#include "NGIAgoraRtcConnection.h"
#include "audio_options_i.h"
#include "channel_capability_i.h"

namespace agora {
namespace rtc {

struct TConnectionInfo;

struct audio_packet_t;
struct SAudioFrame;
struct video_packet_t;
struct control_broadcast_packet_t;
struct CallBillInfo;

class ITransportPacketObserver {
 public:
  virtual ~ITransportPacketObserver() {}
  virtual int onAudioPacket(const agora::rtc::TConnectionInfo& connectionInfo,
                            const audio_packet_t& p) = 0;
  virtual int onVideoPacket(const agora::rtc::TConnectionInfo& connectionInfo,
                            const video_packet_t& p) = 0;
  virtual int onControlBroadcastPacket(const agora::rtc::TConnectionInfo& connectionInfo,
                                       control_broadcast_packet_t& p) = 0;
  virtual int onDataStreamPacket(const agora::rtc::TConnectionInfo& connectionInfo,
                                 agora::rtc::uid_t uid, uint16_t streamId, const char* data,
                                 size_t length) = 0;
};

// Audio frame dump position for sending.
extern const std::string AUDIO_PIPELINE_POS_RECORD_ORIGIN;
extern const std::string AUDIO_PIPELINE_POS_PRE_APM_PROC;
extern const std::string AUDIO_PIPELINE_POS_APM;
extern const std::string AUDIO_PIPELINE_POS_PRE_SEND_PROC;
extern const std::string AUDIO_PIPELINE_POS_FILTER;
extern const std::string AUDIO_PIPELINE_POS_ENC;
extern const std::string AUDIO_PIPELINE_POS_TX_MIXER;
extern const std::string AUDIO_PIPELINE_POS_AT_RECORD;
extern const std::string AUDIO_PIPELINE_POS_ATW_RECORD;

// Audio frame dump position for receiving.
extern const std::string AUDIO_PIPELINE_POS_DEC;
extern const std::string AUDIO_PIPELINE_POS_MIXED;
extern const std::string AUDIO_PIPELINE_POS_PLAY;
extern const std::string AUDIO_PIPELINE_POS_RX_MIXER;
extern const std::string AUDIO_PIPELINE_POS_PLAYBACK_MIXER;
extern const std::string AUDIO_PIPELINE_POS_PCM_SOURCE_PLAYBAC_MIXER;
extern const std::string AUDIO_PIPELINE_POS_PRE_PLAY_PROC;
extern const std::string AUDIO_PIPELINE_POS_AT_PLAYOUT;
extern const std::string AUDIO_PIPELINE_POS_ATW_PLAYOUT;

const int64_t AUDIO_FRAME_DUMP_MIN_DURATION_MS = 0;
const int64_t AUDIO_FRAME_DUMP_MAX_DURATION_MS = 150000;

class IAudioFrameDumpObserver {
 public:
  virtual ~IAudioFrameDumpObserver() = default;
  virtual void OnAudioFrameDumpCompleted(const std::string& location, const std::string& uuid,
                                         const std::vector<std::string>& files) = 0;
};

struct CapabilityItem {
  uint8_t id;
  const char* name;
  CapabilityItem() : id(0), name(nullptr) {}
  CapabilityItem(uint8_t i, const char* n) : id(i), name(n) {}
};

struct CapabilityItemMap {
  CapabilityItem* item;
  size_t size;
  CapabilityItemMap() : item(nullptr), size(0) {}
  CapabilityItemMap(CapabilityItem* i, size_t s) : item(i), size(s) {}
};

struct Capabilities {
  CapabilityItemMap* item_map;
  agora::capability::CapabilityType type;
  Capabilities() : item_map(nullptr), type(agora::capability::CapabilityType::kChannelProfile) {}
  Capabilities(CapabilityItemMap* i, agora::capability::CapabilityType t) : item_map(i), type(t) {}
};

class ICapabilitesObserver {
 public:
  virtual void OnCapabilitesChanged(const Capabilities* capabilities, size_t size){};
  virtual ~ICapabilitesObserver() = default;
};

class ILocalUserEx : public rtc::ILocalUser {
 public:
  virtual int initialize() = 0;
  // We should deprecate sendAudioPacket.
  virtual int sendAudioPacket(const audio_packet_t& packet, int delay = 0) = 0;

  virtual int sendAudioFrame(const SAudioFrame& frame, int delay = 0) = 0;
  virtual int sendVideoPacket(const video_packet_t& packet) = 0;
  virtual int sendControlBroadcastPacket(control_broadcast_packet_t& packet) = 0;

  virtual int sendDataStreamPacket(uint16_t streamId, const char* data, size_t length) = 0;

  // No-thread safe, it must be called before joinChannel().
  // No unregister method provided to simplify internal logic.
  virtual int registerTransportPacketObserver(ITransportPacketObserver* observer) = 0;

  // internal usage
  virtual int setAudioOptions(const rtc::AudioOptions& options) = 0;
  virtual int getAudioOptions(rtc::AudioOptions* options) = 0;
  virtual int setAdvancedAudioOptions(const rtc::AudioOptions& options, int sourceType) = 0;
  virtual int getAecDelay(int sourceType, int* aecDelay) = 0;
  virtual void getBillInfo(CallBillInfo* bill_info) = 0;

  virtual void forceDeviceScore(const int32_t deviceScore) = 0;
  virtual int setPrerendererSmoothing(bool enabled) = 0;
  virtual int setDtx(bool enabled) = 0;
  virtual int setCustomAudioBitrate(int bitrate) = 0;
  virtual int setAudioFrameSizeMs(int sizeMs) = 0;
  virtual int setAudioCC(bool value) = 0;

  virtual int registerAudioFrameDumpObserver(IAudioFrameDumpObserver* observer) = 0;
  virtual int unregisterAudioFrameDumpObserver(IAudioFrameDumpObserver* observer) = 0;

  virtual int startAudioFrameDump(const std::string& location, const std::string& uuid,
                                  const std::string& passwd, int64_t duration_ms,
                                  bool auto_upload) = 0;
  virtual int stopAudioFrameDump(const std::string& location) = 0;
  
  virtual int enalbeSyncRenderNtpBroadcast(bool enable_sync_render_ntp_broadcast) = 0;
  virtual int enalbeSyncRenderNtpAudience(bool enable_sync_render_ntp_audience) = 0;
  virtual int enableStablePlayout(bool enable_stable_playout) = 0;
  virtual int setPlayoutUserAnonymous(rtc::uid_t uid, bool anonymous) = 0;
  virtual int enableAudioPlayout(bool enabled, bool recording = false) = 0;
  virtual int setAudioMaxTargetDelay(int delay) = 0;

  virtual void registerVideoMetadataObserver(media::IMetadataObserver* observer) = 0;
  virtual void unregisterVideoMetadataObserver(media::IMetadataObserver* observer) = 0;

  virtual int setVideoFrameObserver(agora::media::IVideoFrameObserver* observer) = 0;

  virtual agora_refptr<IRemoteVideoTrack> getRemoteVideoTrack(rtc::uid_t uid) = 0;

  virtual int setAVSyncPeer(rtc::uid_t uid) = 0;
  virtual int getOnlySubscribeEncodedVideoFrame(user_id_t peerUid, bool& subscribe) = 0;
  virtual void setMinPlayoutDelay(int delay) = 0;
  virtual int setAllowSubscribeSelf(bool allow) = 0;
  virtual int adjustRecordingSignalVolume(int volume) = 0;
  virtual int getRecordingSignalVolume(int* volume) = 0;
  virtual int enableDownlinkNoiseGate(int noise_gate) = 0;
  virtual bool ForcePeriodicKeyFrame() = 0;
  virtual int registerCapabilitiesObserver(ICapabilitesObserver* cap_observer) = 0;
  virtual int unRegisterCapabilitiesObserver(ICapabilitesObserver* cap_observer) = 0;
  virtual void updateAppDefinedCapabilities(const Capabilities* cap, size_t size) = 0;
  virtual int sendIntraRequestQuick(user_id_t uid) = 0;
  // this function should only be used in media_relay
  // In the media_relay case, there are no track to help video_stream_manager get the video_height
  // and video_width just receive the video packets and send this function used to help us
  // UpdateBillInfo by ourself
  virtual void customUpdateBillInfo(int height, int width, bool isSendingVideo) = 0;
  virtual void setInteractiveAudience(bool interactive) = 0;
  virtual int setVideoDumpMode(int mode, bool enabled) = 0;
  
  virtual void muteLocalAudioStream(bool mute) = 0;
};

}  // namespace rtc
}  // namespace agora
