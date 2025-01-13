//
//  Agora Media SDK
//
//  Created by Sting Feng in 2015-05.
//  Copyright (c) 2015 Agora IO. All rights reserved.
//
#pragma once

#include <memory>
#include <string>

#include "AgoraRefPtr.h"

#include "IAgoraService.h"
#include "IAgoraLog.h"

#include "audio_options_i.h"
#include "content_inspect_i.h"
#include "bitrate_constraints.h"

#include <functional>
#include <string>

struct event_base;

namespace agora {
namespace rtc {
class AgoraGenericBridge;
class ConfigService;
class ConfigSourceAP;
class IDiagnosticService;
class ILocalUserEx;
class PredefineIpList;
class IRtcConnection;
struct RtcConnectionConfigurationEx;
class IMediaExtensionObserver;
class XdumpHandler;
}  // namespace rtc

namespace utils {
struct AudioSessionParam;
template<class T> class RtcAsyncCallback;
}  // namespace utils

namespace commons {
namespace cjson {
class JsonWrapper;
}  // namespace cjson
}  // namespace commons

typedef agora::commons::cjson::JsonWrapper any_document_t;

namespace base {
class IAgoraServiceObserver;

enum MediaEngineType {
  /**
   * The WebRTC engine.
   */
  MEDIA_ENGINE_WEBRTC,
  /**
   * An empty engine.
   */
  MEDIA_ENGINE_EMPTY,
  /**
   * An unknown engine.
   */
  MEDIA_ENGINE_UNKNOWN
};

struct AgoraServiceConfigEx : public AgoraServiceConfiguration {
  MediaEngineType engineType = MEDIA_ENGINE_WEBRTC;
  const char* deviceId = nullptr;
  const char* deviceInfo = nullptr;
  const char* systemInfo = nullptr;
  const char* configDir = nullptr;
  const char* dataDir = nullptr;
  const char* pluginDir = nullptr;
  rtc::BitrateConstraints bitrateConstraints;

  AgoraServiceConfigEx() {
    bitrateConstraints.start_bitrate_bps = kDefaultStartBitrateBps;
    bitrateConstraints.max_bitrate_bps = kDefaultMaxBitrateBps;
  }

  AgoraServiceConfigEx(const AgoraServiceConfiguration& rhs)
      : AgoraServiceConfiguration(rhs) {
    bitrateConstraints.max_bitrate_bps = kDefaultMaxBitrateBps;
    bitrateConstraints.start_bitrate_bps = kDefaultStartBitrateBps;
  }

  bool apSendRequest = true;

 private:
  static constexpr int kDefaultMaxBitrateBps = (24 * 10 * 1000 * 95);
  static constexpr int kDefaultStartBitrateBps = 300000;
};


// full feature definition of rtc engine interface
class IAgoraServiceEx : public IAgoraService {
 public:
  virtual int initializeEx(const AgoraServiceConfigEx& context) = 0;
  virtual agora_refptr<rtc::IRtcConnection> createRtcConnectionEx(
      const rtc::RtcConnectionConfigurationEx& cfg) = 0;
  // Returns a libevent event_base created by event_base_new. Also this implies
  // the application might use this event as its main event loop.
  virtual event_base* getWorkerEventBase() = 0;

  virtual int32_t setLogWriter(agora::commons::ILogWriter* logWriter) = 0;
  virtual agora::commons::ILogWriter* releaseLogWriter() = 0;

  virtual int32_t setAudioDumpPath(const char* filePath) = 0;

  virtual agora_refptr<rtc::IRtcConnection> getOneRtcConnection(bool admBinded) const = 0;
  
  virtual void enableStringUid(bool enabled) = 0;
  virtual bool useStringUid() const = 0;
  virtual rtc::uid_t getUidByUserAccount(const std::string& app_id, const std::string& user_account) const = 0;

  // Register string user account before join channel, this would speed up join channel time.
  virtual int registerLocalUserAccount(const char* appId, const char* userAccount) = 0;

  virtual rtc::IDiagnosticService *getDiagnosticService() const = 0;

  virtual int registerAgoraServiceObserver(IAgoraServiceObserver* observer) = 0;
  virtual int unregisterAgoraServiceObserver(IAgoraServiceObserver* observer) = 0;

  virtual agora_refptr<rtc::IFileUploaderService> createFileUploadServiceEx(
      agora_refptr<rtc::IRtcConnection> rtcConnection, const char* appId, media::CONTENT_INSPECT_CLOUD_TYPE cloudType) = 0;

  /**
   * Start trace with mask and max ring buffer size: count.
   *
   * @return
   *
   * - -1: Service don't start or start trace failure.
   * - 1: Success, and do nothing if it already started.
   */
  virtual int startTrace(uint32_t count, uint64_t mask) = 0;
  /**
   * stop trace, and save log in file_path.
   *
   * @return
   *
   * - -1: Service don't start
   * - 1: Success, and do nothing if it already stoped
   */
  virtual int stopTrace(const char* file_path) = 0;

  /**
   * Sets the external audio sink.
   *
   * This method applies to scenarios where you want to use external audio
   * data for playback.
   *
   * @param enabled
   * - true: Enables the external audio sink.
   * - false: Disables the external audio sink.
   * @param sampleRate Sets the sample rate (Hz) of the external audio sink, which can be set as 16000, 32000, 44100 or 48000.
   * @param channels Sets the number of audio channels of the external
   * audio sink:
   * - 1: Mono.
   * - 2: Stereo.
   *
   * @return
   * - 0: Success.
   * - < 0: Failure.
   */
  virtual int setExternalAudioSink(bool enabled, int sampleRate, int channels) = 0;

  /**
   * Pulls the playback PCM audio data from all the channel.
   *
   * @param[out] payloadData The pointer to the playback PCM audio data.
   * @param[in] audioFrameInfo The reference to the information of the PCM audio data: \ref agora::rtc::AudioPcmDataInfo "AudioPcmDataInfo".
   * @return
   * - 0: Success.
   * - < 0: Failure.
   */
  virtual int pullPlaybackAudioPcmData(void* payloadData, const rtc::AudioPcmDataInfo& audioFrameInfo) = 0;

  virtual int setExtensionProviderProperty(const char* provider, const char* key, const char* value) = 0;
  
 protected:
  virtual ~IAgoraServiceEx() {}
};

class IAgoraServiceObserver{
 public:
  virtual ~IAgoraServiceObserver() = default;

  virtual void onLocalUserRegistered(rtc::uid_t uid, const char* userAccount) = 0;
};

IAgoraServiceEx* GetService();

}  // namespace base
}  // namespace agora
