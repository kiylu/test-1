//
//  Agora Media SDK
//
//  Created by Sting Feng in 2015-05.
//  Copyright (c) 2015 Agora IO. All rights reserved.
//
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "AgoraRefPtr.h"

#include "NGIAgoraCameraCapturer.h"
#include "NGIAgoraVideoMixerSource.h"
#include "NGIAgoraMediaNodeFactory.h"
#include "NGIAgoraMediaNode.h"
#include "api/video/video_frame.h"

namespace webrtc {
class VideoFrame;
}  // namespace webrtc

namespace rtc {
struct VideoSinkWants;

template <typename VideoFrameT>
class VideoSinkInterface;
}  // namespace rtc

namespace agora {
namespace rtc {
struct RenderFreezeStats;

enum InternalRendererType {
  RENDERER_NONE = -1,
  RENDERER_BUILT_IN_RENDERER = 0,
  RENDERER_EXT_OBSERVER = 3,
};

struct PreviewMetaInfo {
  uintptr_t handle;
  bool mirror;
  media::base::RENDER_MODE_TYPE render_mode;
};

static const char* const BUILT_IN_SOURCE_FILTER = "built-in-source-filter";
static const char* const BUILT_IN_METADATA_OBSERVER = "built-in-metadata-observer";
static const char* const BUILT_IN_ADAPTER = "built-in-adapter";
static const char* const BUILT_IN_PRE_ENCODER_WATERMARK_FILTER = "built-in-pre-encoder-watermarker";
static const char* const BUILT_IN_POST_CAPTURER_WATERMARK_FILTER = "built-in-post-capturer-watermarker";
static const char* const BUILT_IN_PRE_ENCODER_FACEDETECE_FILTER = "built-in-pre-encoder-facedetect";
static const char* const BUILT_IN_PREVIEW_TEE = "built-in-preview-tee";
static const char* const BUILT_IN_MAJOR_TEE = "built-in-major-tee";
static const char* const BUILT_IN_MINOR_TEE = "built-in-minor-tee";
static const char* const BUILT_IN_MINOR_ADAPTER = "built-in-minor-adapter";
static const char* const BUILT_IN_POST_CAPTURER_FILTER_OBSERVER = "built-in-post-capturer-filter-observer";
static const char* const BUILT_IN_PRE_ENCODER_FILTER_OBSERVER = "built-in-pre-encoder-filter-observer";

/** Filter definition for internal pipeline usage.
 */
class IVideoFilterEx : public IVideoFilter {
 public:
  using IVideoFilter::adaptVideoFrame;
  // Internal node can use webrtc video frame directly to reduce copy operation.
  virtual bool adaptVideoFrame(const webrtc::VideoFrame& capturedFrame,
                               webrtc::VideoFrame& adaptedFrame) = 0;
  // TODO(Bob): This should be moved to node base.
  virtual void onSinkWantsChanged(const ::rtc::VideoSinkWants& wants) = 0;
  bool isExternal() override { return false; }
  virtual void attachStatsSpace(uint64_t stats_space) {}

 protected:
  ~IVideoFilterEx() {}
};

/** Video frame adapter.
 */
class IVideoFrameAdapter : public IVideoFilterEx {
 public:
  // Requests the output frame size and frame interval from
  // |AdaptFrameResolution| to not be larger than |format|. Also, the input
  // frame size will be cropped to match the requested aspect ratio. When "fixed"
  // is set false, the requested aspect ratio is orientation agnostic
  // and will be adjusted to maintain the input orientation, so it doesn't matter
  // if e.g. 1280x720 or 720x1280 is requested. Otherwise, the output format is
  // fixed. The input frame may be cropped and rotated to meet the output format.
  virtual void setOutputFormat(const VideoFormat& format, bool fixed = false) = 0;

  // Request the output frame in a fixed rotation.
  virtual void setOutputRotation(webrtc::VideoRotation rotation) {}

  // mirror the frame
  virtual void setMirror(bool mirror) {}

 protected:
  ~IVideoFrameAdapter() {}
};

enum CAMERA_OUTPUT_DATA_TYPE {
    CAMERA_OUTPUT_RAW = 0,              // YUV
    CAMERA_OUTPUT_TEXTURE = 1,          // Texture
    CAMERA_OUTPUT_TEXTURE_AND_RAW = 2,  // YUV && Texture
};

class ICameraCapturerEx : public ICameraCapturer {
 public:
  virtual ~ICameraCapturerEx() {}

#if defined(__ANDROID__) || defined(TARGET_OS_IPHONE)
  virtual void setPreviewInfo(const PreviewMetaInfo& info) {}
#endif

#if defined(__ANDROID__)
  virtual void setCameraOutputDataType(CAMERA_OUTPUT_DATA_TYPE type) = 0;
  virtual CAMERA_OUTPUT_DATA_TYPE getCameraOutputDataType() = 0;
  virtual void setCameraSelected(int module_selected) = 0;
  virtual void setCameraSelectedLevel(int camera_selected_level) = 0;
  virtual void setCameraPqFirst(bool pq_first) = 0;
  virtual void setVideoStabilityMode(int mode) = 0;
#endif

#if defined(WEBRTC_IOS)
  virtual void setCameraFormatType(CAMERA_FORMAT_TYPE type) = 0;
  virtual void setCameraDropCount(int dropcount) = 0;
  virtual void setHDRCaptureEnable(bool enableHDRCapture) = 0;
#endif
  virtual void setColorSpaceInfo(webrtc::ColorSpace colorSpace) = 0;

#if defined(_WIN32) || (defined(__linux__) && !defined(__ANDROID__)) || \
    (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
  virtual std::string getDeviceId() = 0;
#endif
  // Requests the output frame size and frame rate. It takes effect
  // only if regulator is enabled. 
  // The output frame size will be cropped to match the requested aspect
  // ratio, and frame rate will not be larger than the requested value. 
  // When "fixed" is set false, the requested aspect ratio is orientation
  // agnostic, so it doesn't matter if e.g. 1280x720 or 720x1280 is requested. 
  // Otherwise, the aspect ratio of output frame is fixed.
  virtual void setOutputFormat(const rtc::VideoFormat& format, bool fixed = false) = 0;
  virtual void enableRegulator(bool enable) = 0;
  virtual bool regulatorEnabled() = 0;
};

class IVideoRendererEx : public IVideoRenderer {
 public:
  using IVideoRenderer::onFrame;
  virtual int onFrame(const webrtc::VideoFrame& videoFrame) {
    (void)videoFrame;
    return -ERR_NOT_SUPPORTED;
  }

  int setView(void* view) override {
    (void) view;
    return -ERR_NOT_SUPPORTED;
  }

  int addView(void* view, const Rectangle& cropArea) override {
    (void) view;
    (void) cropArea;
    return -ERR_NOT_SUPPORTED;
  }

  int removeView(void* view) override {
    (void) view;
    return -ERR_NOT_SUPPORTED;
  }

  virtual int addViewEx(uintptr_t handle, const Rectangle& cropArea) {
    (void) handle;
    (void) cropArea;
    return -ERR_NOT_SUPPORTED;
  }

  virtual int addViewEx(uintptr_t handle) {
    (void) handle;
    return -ERR_NOT_SUPPORTED;
  }

  virtual int removeViewEx(uintptr_t handle) {
    (void) handle;
    return unsetView();
  }

  int setRenderMode(void* view, media::base::RENDER_MODE_TYPE renderMode) override {
    (void) view;
    (void) renderMode;
    return -ERR_NOT_SUPPORTED;
  }

  int setMirror(void* view, bool mirror) override {
    (void) view;
    (void) mirror;
    return -ERR_NOT_SUPPORTED;
  }

  using IVideoRenderer::setRenderMode;
  virtual int setRenderModeEx(uintptr_t handle, media::base::RENDER_MODE_TYPE renderMode) {
    (void) handle;
    return setRenderMode(renderMode);
  }

  using IVideoRenderer::setMirror;
  virtual int setMirrorEx(uintptr_t handle, bool mirror) {
    (void) handle;
    return setMirror(mirror);
  }

  virtual void attachUserInfo(uid_t uid, uint64_t state_space) {
    (void) uid;
    (void) state_space;
  }

  virtual int getViewMetaInfo(PreviewMetaInfo& info) {
    (void) info;
    return -ERR_NOT_SUPPORTED;
  }

  virtual int getViewMetaInfo(uintptr_t handle, PreviewMetaInfo& info) {
    (void) handle;
    (void) info;
    return -ERR_NOT_SUPPORTED;
  }

  virtual int getViewCount() {
    return -ERR_NOT_SUPPORTED;
  }

  virtual int clearBuffer() {
    return -ERR_NOT_SUPPORTED;
  }
};

class IObservableVideoSink : public IVideoRendererEx {
 public:
  virtual void setVideoFrameObserver(agora::media::IVideoFrameObserver* observer) {}

 protected:
  ~IObservableVideoSink() {}
};

class IObservableVideoFilter : public IVideoFilterEx {
 public:
  virtual void setVideoFrameObserver(agora::media::IVideoFrameObserver* observer) {}

 protected:
  ~IObservableVideoFilter() {}
};

struct VideoEncodedImageData : public RefCountInterface {
  std::string image;
  VIDEO_FRAME_TYPE frameType;
  int width;
  int height;
  int framesPerSecond;
  // int64_t renderTimeInMs;
  VIDEO_ORIENTATION rotation;
  VIDEO_CODEC_TYPE codec;
  VIDEO_STREAM_TYPE streamType;
  int64_t captureTimeMs;
  int64_t decodeTimeMs;
};

struct CameraInfo {
  bool inUse;
  std::string deviceName;
  std::string deviceId;
  std::string deviceType;
};
using CameraInfoList = std::vector<CameraInfo>;

class IVideoEncodedImageCallback {
 public:
  virtual ~IVideoEncodedImageCallback() {}
  virtual void OnVideoEncodedImage(agora_refptr<VideoEncodedImageData> data) = 0;
};

class IVideoEncodedImageSenderEx : public IVideoEncodedImageSender {
 public:
  virtual ~IVideoEncodedImageSenderEx() {}
  virtual void RegisterEncodedImageCallback(IVideoEncodedImageCallback* dataCallback,
                                            VIDEO_STREAM_TYPE stream_type) = 0;
  virtual void DeRegisterEncodedImageCallback(IVideoEncodedImageCallback* dataCallback,
                                              VIDEO_STREAM_TYPE stream_type) = 0;
  virtual void AttachStatSpace(uint64_t stats_space) = 0;
  virtual void DetachStatSpace(uint64_t stats_space) = 0;

  virtual int getWidth() const = 0;
  virtual int getHeight() const = 0;
};

class IVideoFrameSenderEx : public IVideoFrameSender {
 public:
  using IVideoFrameSender::sendVideoFrame;

  virtual ~IVideoFrameSenderEx() {}

  virtual int sendVideoFrame(const webrtc::VideoFrame& videoFrame) = 0;

  virtual void RegisterVideoFrameCallback(
      ::rtc::VideoSinkInterface<webrtc::VideoFrame>* dataCallback) = 0;
  virtual void DeRegisterVideoFrameCallback() = 0;

  virtual int getVideoFrame(webrtc::VideoFrame& videoFrame) = 0;
  virtual bool pushMode() = 0;
};

class IVideoMixerSourceEx : public IVideoMixerSource {
 public:
  virtual ~IVideoMixerSourceEx() = default;
  virtual void registerMixedFrameCallback(
        ::rtc::VideoSinkInterface<webrtc::VideoFrame>* dataCallback) = 0;
  virtual void deRegisterMixedFrameCallback(::rtc::VideoSinkInterface<webrtc::VideoFrame>* dataCallback) = 0;
  virtual void onFrame(const std::string& uid, const webrtc::VideoFrame& frame) = 0;
  virtual void startMixing() = 0;
  virtual void stopMixing() = 0;
  virtual bool hasVideoTrack(const std::string& id) = 0;
};

class IVideoFrameTransceiverEx : public IVideoFrameTransceiver {
 public:
  virtual int onFrame(const webrtc::VideoFrame& videoFrame) = 0;
  virtual void registerFrameCallback(
      ::rtc::VideoSinkInterface<webrtc::VideoFrame>* dataCallback) = 0;
  virtual void deRegisterFrameCallback(::rtc::VideoSinkInterface<webrtc::VideoFrame>* dataCallback) = 0;
  virtual void observeTxDelay(ILocalVideoTrack* track) = 0;
};

static const char* const GLFW_RESOURCE = "glfw_resource";
struct GlobalResourceMetaInfo {
  const char* resource_name = nullptr;
  int (*init_func)(void*) = nullptr;
  int (*deinit_func)(void*) = nullptr;
  void* context = nullptr;
  bool fixed_thread = true;
  bool init_once = false;
};

class IExtensionVideoFilterControlEx : public IExtensionVideoFilter::Control {
 public:
  virtual ~IExtensionVideoFilterControlEx() = default;
  virtual int ReportCounter(int32_t counter_id, int32_t value) = 0;
  virtual int ReportEvent(int32_t event_id, void* event) = 0;
  virtual int DeclareGlobalResource(const GlobalResourceMetaInfo& meta_info, int& resource_count) = 0;
  virtual int ReleaseGlobalResource(const GlobalResourceMetaInfo& meta_info, int& resource_count) = 0;
  virtual void NotifySrDelay(int sr_delay_ms) = 0;
};

}  // namespace rtc
}  // namespace agora
