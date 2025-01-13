//  Agora SDK
//
//  Copyright (c) 2019 Agora.io. All rights reserved.
//  Reference from WebRTC project
//
#pragma once

#include <string>

#include "AgoraOptional.h"

#define SET_FROM(X) SetFrom(&X, change.X)

#define BEGIN_COMPARE() bool b = true
#define ADD_COMPARE(X) b = (b && (X == o.X))
#define END_COMPARE_AND_RETURN() \
  ;                              \
  return b

#define UNPUBLISH(X) X.reset()

namespace agora {
namespace rtc {

/**
 * OpenSL mode
 */
enum OPENSL_MODE {
  /**
   * always on
   */
  ALWAYS_ON,

  /**
   * always off
   */
  ALWAYS_OFF,

  /**
   * on with headset
   */
  ON_WITH_HEADSET,
};

// Options that can be applied to an audio track or audio engine.
struct AudioOptions {
  AudioOptions() = default;
  ~AudioOptions() = default;

  void SetAll(const AudioOptions& change) {
    SET_FROM(audio_scenario);
    SET_FROM(audio_routing);
    SET_FROM(opensl_mode);
    SET_FROM(adm_enable_estimated_device_delay);
    SET_FROM(adm_device_delay_calc_period);
    SET_FROM(audio_routing_version);
    SET_FROM(adm_enable_preferred_aec_delay);
    SET_FROM(adm_enable_lowlatency_capture);
    SET_FROM(adm_duck_others);
    SET_FROM(adm_mix_with_others);
    SET_FROM(adm_restart_when_interrupted);
    SET_FROM(adm_specify_category);
    SET_FROM(adm_enable_oboe);
    SET_FROM(adm_enable_fallback);
    SET_FROM(adm_record_audio_session_call_stack);
    SET_FROM(has_remote_peers);
    SET_FROM(has_enabled_ear_monitor);

    SET_FROM(adm_input_sample_rate);
    SET_FROM(adm_output_sample_rate);
    SET_FROM(adm_enable_exclusive_mode);
    SET_FROM(adm_input_channels);
    SET_FROM(adm_output_channels);
    SET_FROM(adm_has_recorded);
    SET_FROM(adm_enable_mic_selection);
    SET_FROM(adm_force_use_bluetooth_a2dp);
    SET_FROM(adm_use_bluetooth_hfp);
    SET_FROM(adm_use_hw_aec);
    SET_FROM(adm_enable_hardware_ear_monitor);
    SET_FROM(adm_force_restart);
    SET_FROM(adm_audio_layer);
    SET_FROM(adm_audio_source);
    SET_FROM(adm_playout_bufsize_factor);
    SET_FROM(adm_enable_builtin3a);
    SET_FROM(adm_extra_playout_latency);
    SET_FROM(adm_extra_record_latency);
    SET_FROM(adm_opensl_output_bufs);
    SET_FROM(adm_opensl_input_bufs);
    SET_FROM(apm_process_channels);
    SET_FROM(downlink_peq_enable);
    SET_FROM(apm_enable_aec);
    SET_FROM(apm_enable_aec_external);
    SET_FROM(apm_aec_nlp_size);
    SET_FROM(apm_aec_delay_search_method);
    SET_FROM(apm_aec_fixed_delay);
    SET_FROM(apm_aec_extra_delay_bias);
    SET_FROM(adm_ext_recording_source_delay_ms);
    SET_FROM(apm_aec_nlp_plan);
    SET_FROM(apm_aec_audio_mixing);
    SET_FROM(apm_aec_saturated);
    SET_FROM(apm_aec_ainlp_reset_period);
    SET_FROM(apm_aec_ainlp_reset_ratio);
    SET_FROM(apm_aec_ainlp_fallback_period);
    SET_FROM(apm_aec_ainlp_postprocessing_method);
    SET_FROM(apm_aec_linear_filter_type);
    SET_FROM(apm_enable_ns);
    SET_FROM(apm_ains_mode);
    SET_FROM(apm_ains_gain_control);
    SET_FROM(apm_ains_speech_enhance);
    SET_FROM(apm_enable_agc);
    SET_FROM(apm_enable_md);
    SET_FROM(apm_aimd_value);
    SET_FROM(apm_enable_highpass_filter);
    SET_FROM(apm_enable_tone_remover);
    SET_FROM(apm_enable_pitch_smoother);
    SET_FROM(apm_enable_howling_control);
    SET_FROM(apm_delay_offset_ms);
    SET_FROM(apm_aec_nlp_aggressiveness);
    SET_FROM(apm_aec_complexity);
    SET_FROM(apm_aec_farend_energythreshold);
    SET_FROM(apm_aec_ref_gain);
    SET_FROM(apm_aec_sw_processing_mode);
    SET_FROM(apm_aec_linear_filter_length_ms);
    SET_FROM(apm_aec_split_srate_for_32k);
    SET_FROM(apm_aec_split_srate_for_48k);
    SET_FROM(apm_agc_target_level_dbfs);
    SET_FROM(apm_agc_compression_gain_db);
    SET_FROM(apm_agc_curve_slope);
    SET_FROM(apm_agc_mode);
    SET_FROM(apm_ns_enable_ns_follow_agc);
    SET_FROM(apm_ns_level);
    SET_FROM(apm_ns_noiseGateThres);
    SET_FROM(apm_ns_complexity);
    SET_FROM(apm_enable_record_boost);
    // AINS
    SET_FROM(apm_ains_fft_size);
    SET_FROM(apm_ains_maxtolerant_ms);
    SET_FROM(apm_ains_attack_factor);
    SET_FROM(apm_ains_release_factor);
    SET_FROM(apm_ains_upper_bound);
    SET_FROM(apm_ains_upper_mask);
    SET_FROM(apm_ains_lower_bound);
    SET_FROM(apm_ains_lower_mask);
    SET_FROM(apm_nsng_end_start_up_long);
    SET_FROM(apm_nsng_end_start_up_short);
    SET_FROM(apm_nsng_quantile);
    SET_FROM(apm_nsng_noise_update_factor);
    SET_FROM(apm_nsng_speech_update_factor);
    SET_FROM(apm_nsng_overdrive);
    SET_FROM(apm_nsng_noise_ref_protect);
    SET_FROM(apm_nsng_vad_threshold);
    SET_FROM(apm_nsng_md_threshold);
    SET_FROM(apm_ains_reset_frame);
    SET_FROM(apm_ains_kill_highband);
    SET_FROM(apm_ains_triangle_1);
    SET_FROM(apm_ains_triangle_2);
    SET_FROM(apm_ains_triangle_3);
    SET_FROM(apm_ains_threshold_ai);
    SET_FROM(apm_ains_threshold_stastical);
    SET_FROM(apm_ains_enh_factor_ai);
    SET_FROM(apm_ains_enh_factor_stastical);
    SET_FROM(apm_ains_noise_over_estimate);
    SET_FROM(apm_ains_statistical_bound);
    SET_FROM(apm_ains_gain_boost_frq1);
    SET_FROM(apm_ains_gain_boost_gain1);
    SET_FROM(apm_ains_gain_boost_frq2);
    SET_FROM(apm_ains_gain_boost_gain2);
    SET_FROM(apm_ains_gain_boost_frq3);
    SET_FROM(apm_ains_gain_boost_gain3);
    SET_FROM(apm_ains_final_lower_mask);
    SET_FROM(apm_ains_noise_pow_floor);
    SET_FROM(apm_ains_cng_base_magnitude);
    SET_FROM(apm_ains_strategy);
    SET_FROM(apm_ains_postfilter_margin);
    SET_FROM(apm_ains_delaymode);
    SET_FROM(apm_ains_aggressive);
    SET_FROM(apm_farend_gain_threshold);
    SET_FROM(adm_mac_use_audio_unit_hal);
    SET_FROM(apm_farend_gain);
    SET_FROM(acm_bitrate);
    SET_FROM(acm_codec);
    SET_FROM(acm_dtx);
    SET_FROM(acm_plc);
    SET_FROM(acm_complex_level);
    SET_FROM(acm_ptime);
    SET_FROM(acm_hw_encode_opus);
    SET_FROM(acm_hw_decode_opus);
    SET_FROM(acm_opus_celt_only);
    SET_FROM(acm_opus_voice_threshold);
    SET_FROM(acm_opus_enable_volume_based_bitrate_reduction);
    SET_FROM(acm_opus_voice_up_coef);
    SET_FROM(acm_opus_voice_down_coef);
    SET_FROM(acm_opus_voice_hold_window_ms);
    SET_FROM(acm_opus_silence_bitrate);
    SET_FROM(audio_resend);
    SET_FROM(audio_rsfec_frame_num);
    SET_FROM(audio_rsfec_interleave_num);
    SET_FROM(audio_fec_frame_num);
    SET_FROM(audio_fec_interleave_num);
    SET_FROM(neteq_live_min_delay);
    SET_FROM(neteq_jitter_buffer_max_packets);
    SET_FROM(neteq_jitter_buffer_fast_accelerate);
    SET_FROM(neteq_jitter_max_target_delay);
    SET_FROM(neteq_filter_target_loss);
    SET_FROM(neteq_max_filter_window);
    SET_FROM(neteq_enable_expired_peak_detector);
    SET_FROM(neteq_enable_peak_detector);
    SET_FROM(neteq_max_exceed_time_ms);
    SET_FROM(neteq_max_filter_dup_num);
    SET_FROM(neteq_enable_voice_volume_level);
    SET_FROM(neteq_enable_individuality_delay);
    SET_FROM(neteq_enable_improve_burst);
    SET_FROM(neteq_low_latency_burst_control_window_ms);
    SET_FROM(neteq_low_latency_burst_control_platform_ms);
    SET_FROM(neteq_low_latency_burst_peak_num_threshold);
    SET_FROM(neteq_low_latency_burst_trend_threshold);
    SET_FROM(neteq_low_latency_burst_peak_trend_increased_threshold);
    SET_FROM(neteq_low_latency_burst_overuse_limited_quantile);
    SET_FROM(neteq_low_latency_burst_comb_window_second);
    SET_FROM(neteq_low_latency_burst_max_jitter_limit_ms);
    SET_FROM(neteq_high_latency_burst_control_window_ms);
    SET_FROM(neteq_high_latency_burst_control_platform_ms);
    SET_FROM(neteq_high_latency_burst_peak_num_threshold);
    SET_FROM(neteq_high_latency_burst_trend_threshold);
    SET_FROM(neteq_high_latency_burst_peak_trend_increased_threshold);
    SET_FROM(neteq_high_latency_burst_overuse_limited_quantile);
    SET_FROM(neteq_high_latency_burst_comb_window_second);
    SET_FROM(neteq_high_latency_burst_max_jitter_limit_ms);
    SET_FROM(neteq_targetlevel_offset);
    SET_FROM(neteq_enable_stable_playout);
    SET_FROM(neteq_drop_window_threshold_ms);
    SET_FROM(neteq_drop_distance_threshold_ms);
    SET_FROM(neteq_prebuffer_window_threshold_ms);
    SET_FROM(neteq_prebuffer_distance_threshold_ms);
    SET_FROM(neteq_max_packets_stable_playout);
    SET_FROM(neteq_normal_recv_rate_ratio_threshold);
    SET_FROM(neteq_target_level_optimization);
    SET_FROM(neteq_aqm_voice_threshold);
    SET_FROM(neteq_dump_level);
    SET_FROM(neteq_dump_path);
    SET_FROM(neteq_limit_prob);
    SET_FROM(neteq_pre_dump);
    SET_FROM(neteq_lower_limit_probability);
    SET_FROM(neteq_plc_mode);
    SET_FROM(dwlink_gain);
    SET_FROM(uplink_gain);
    SET_FROM(derived_headset_black_list_device);
    SET_FROM(use_media_volume_in_headset);
    SET_FROM(use_media_volume_in_audience);
    SET_FROM(use_media_volume_in_solo);
    SET_FROM(use_media_volume_in_bluetooth);
  }

  bool operator==(const AudioOptions& o) const {
    BEGIN_COMPARE();
    ADD_COMPARE(audio_scenario);
    ADD_COMPARE(audio_routing);
    ADD_COMPARE(opensl_mode);
    ADD_COMPARE(adm_enable_estimated_device_delay);
    ADD_COMPARE(adm_device_delay_calc_period);
    ADD_COMPARE(audio_routing_version);
    ADD_COMPARE(adm_enable_preferred_aec_delay);
    ADD_COMPARE(adm_enable_lowlatency_capture);
    ADD_COMPARE(adm_duck_others);
    ADD_COMPARE(adm_mix_with_others);
    ADD_COMPARE(adm_restart_when_interrupted);
    ADD_COMPARE(adm_specify_category);
    ADD_COMPARE(adm_enable_oboe);
    ADD_COMPARE(adm_enable_fallback);
    ADD_COMPARE(adm_record_audio_session_call_stack);
    ADD_COMPARE(has_remote_peers);
    ADD_COMPARE(has_enabled_ear_monitor);
    ADD_COMPARE(adm_input_sample_rate);
    ADD_COMPARE(adm_output_sample_rate);
    ADD_COMPARE(adm_enable_exclusive_mode);
    ADD_COMPARE(adm_input_channels);
    ADD_COMPARE(adm_output_channels);
    ADD_COMPARE(adm_has_recorded);
    ADD_COMPARE(adm_enable_mic_selection);
    ADD_COMPARE(adm_force_use_bluetooth_a2dp);
    ADD_COMPARE(adm_use_bluetooth_hfp);
    ADD_COMPARE(adm_use_hw_aec);
    ADD_COMPARE(adm_enable_hardware_ear_monitor);
    ADD_COMPARE(adm_force_restart);
    ADD_COMPARE(adm_audio_layer);
    ADD_COMPARE(adm_audio_source);
    ADD_COMPARE(adm_playout_bufsize_factor);
    ADD_COMPARE(adm_enable_builtin3a);
    ADD_COMPARE(downlink_peq_enable);
    ADD_COMPARE(adm_extra_playout_latency);
    ADD_COMPARE(adm_extra_record_latency);
    ADD_COMPARE(adm_opensl_output_bufs);
    ADD_COMPARE(adm_opensl_input_bufs);
    ADD_COMPARE(apm_process_channels);
    ADD_COMPARE(apm_enable_aec);
    ADD_COMPARE(apm_enable_aec_external);
    ADD_COMPARE(apm_aec_nlp_size);
    ADD_COMPARE(apm_aec_delay_search_method);
    ADD_COMPARE(apm_aec_fixed_delay);
    ADD_COMPARE(apm_aec_extra_delay_bias);
    ADD_COMPARE(adm_ext_recording_source_delay_ms);
    ADD_COMPARE(apm_aec_nlp_plan);
    ADD_COMPARE(apm_aec_audio_mixing);
    ADD_COMPARE(apm_aec_saturated);
    ADD_COMPARE(apm_aec_ainlp_reset_period);
    ADD_COMPARE(apm_aec_ainlp_reset_ratio);
    ADD_COMPARE(apm_aec_ainlp_fallback_period);
    ADD_COMPARE(apm_aec_ainlp_postprocessing_method);
    ADD_COMPARE(apm_aec_linear_filter_type);
    ADD_COMPARE(apm_enable_ns);
    ADD_COMPARE(apm_ains_mode);
    ADD_COMPARE(apm_ains_gain_control);
    ADD_COMPARE(apm_ains_speech_enhance);
    // AINS
    ADD_COMPARE(apm_ains_fft_size);
    ADD_COMPARE(apm_ains_maxtolerant_ms);
    ADD_COMPARE(apm_ains_attack_factor);
    ADD_COMPARE(apm_ains_release_factor);
    ADD_COMPARE(apm_ains_upper_bound);
    ADD_COMPARE(apm_ains_upper_mask);
    ADD_COMPARE(apm_ains_lower_bound);
    ADD_COMPARE(apm_ains_lower_mask);
    ADD_COMPARE(apm_nsng_end_start_up_long);
    ADD_COMPARE(apm_nsng_end_start_up_short);
    ADD_COMPARE(apm_nsng_quantile);
    ADD_COMPARE(apm_nsng_noise_update_factor);
    ADD_COMPARE(apm_nsng_speech_update_factor);
    ADD_COMPARE(apm_nsng_overdrive);
    ADD_COMPARE(apm_nsng_noise_ref_protect);
    ADD_COMPARE(apm_nsng_vad_threshold);
    ADD_COMPARE(apm_nsng_md_threshold);
    ADD_COMPARE(apm_ains_reset_frame);
    ADD_COMPARE(apm_ains_kill_highband);
    ADD_COMPARE(apm_ains_triangle_1);
    ADD_COMPARE(apm_ains_triangle_2);
    ADD_COMPARE(apm_ains_triangle_3);
    ADD_COMPARE(apm_ains_threshold_ai);
    ADD_COMPARE(apm_ains_threshold_stastical);
    ADD_COMPARE(apm_ains_enh_factor_ai);
    ADD_COMPARE(apm_ains_enh_factor_stastical);
    ADD_COMPARE(apm_ains_noise_over_estimate);
    ADD_COMPARE(apm_ains_statistical_bound);
    ADD_COMPARE(apm_ains_gain_boost_frq1);
    ADD_COMPARE(apm_ains_gain_boost_gain1);
    ADD_COMPARE(apm_ains_gain_boost_frq2);
    ADD_COMPARE(apm_ains_gain_boost_gain2);
    ADD_COMPARE(apm_ains_gain_boost_frq3);
    ADD_COMPARE(apm_ains_gain_boost_gain3);
    ADD_COMPARE(apm_ains_final_lower_mask);
    ADD_COMPARE(apm_ains_noise_pow_floor);
    ADD_COMPARE(apm_ains_cng_base_magnitude);
    ADD_COMPARE(apm_ains_strategy);
    ADD_COMPARE(apm_ains_postfilter_margin);
    ADD_COMPARE(apm_ains_delaymode);
    ADD_COMPARE(apm_ains_aggressive);
    ADD_COMPARE(apm_farend_gain_threshold);
    ADD_COMPARE(adm_mac_use_audio_unit_hal);
    ADD_COMPARE(apm_farend_gain);
    ADD_COMPARE(apm_enable_agc);
    ADD_COMPARE(apm_enable_md);
    ADD_COMPARE(apm_aimd_value);
    ADD_COMPARE(apm_enable_highpass_filter);
    ADD_COMPARE(apm_enable_tone_remover);
    ADD_COMPARE(apm_enable_pitch_smoother);
    ADD_COMPARE(apm_enable_howling_control);
    ADD_COMPARE(apm_delay_offset_ms);
    ADD_COMPARE(apm_aec_nlp_aggressiveness);
    ADD_COMPARE(apm_aec_complexity);
    ADD_COMPARE(apm_aec_farend_energythreshold);
    ADD_COMPARE(apm_aec_ref_gain);
    ADD_COMPARE(apm_aec_sw_processing_mode);
    ADD_COMPARE(apm_aec_linear_filter_length_ms);
    ADD_COMPARE(apm_aec_split_srate_for_32k);
    ADD_COMPARE(apm_aec_split_srate_for_48k);
    ADD_COMPARE(apm_agc_target_level_dbfs);
    ADD_COMPARE(apm_agc_compression_gain_db);
    ADD_COMPARE(apm_agc_curve_slope);
    ADD_COMPARE(apm_agc_mode);
    ADD_COMPARE(apm_ns_enable_ns_follow_agc);
    ADD_COMPARE(apm_ns_level);
    ADD_COMPARE(apm_ns_noiseGateThres);
    ADD_COMPARE(apm_ns_complexity);
    ADD_COMPARE(apm_enable_record_boost);
    ADD_COMPARE(acm_bitrate);
    ADD_COMPARE(acm_codec);
    ADD_COMPARE(acm_dtx);
    ADD_COMPARE(acm_plc);
    ADD_COMPARE(acm_complex_level);
    ADD_COMPARE(acm_ptime);
    ADD_COMPARE(acm_hw_encode_opus);
    ADD_COMPARE(acm_hw_decode_opus);
    ADD_COMPARE(acm_opus_celt_only);
    ADD_COMPARE(acm_opus_voice_threshold);
    ADD_COMPARE(acm_opus_enable_volume_based_bitrate_reduction);
    ADD_COMPARE(acm_opus_voice_up_coef);
    ADD_COMPARE(acm_opus_voice_down_coef);
    ADD_COMPARE(acm_opus_voice_hold_window_ms);
    ADD_COMPARE(acm_opus_silence_bitrate);
    ADD_COMPARE(audio_resend);
    ADD_COMPARE(audio_rsfec_frame_num);
    ADD_COMPARE(audio_rsfec_interleave_num);
    ADD_COMPARE(audio_fec_frame_num);
    ADD_COMPARE(audio_fec_interleave_num);
    ADD_COMPARE(neteq_live_min_delay);
    ADD_COMPARE(neteq_jitter_buffer_max_packets);
    ADD_COMPARE(neteq_jitter_buffer_fast_accelerate);
    ADD_COMPARE(neteq_jitter_max_target_delay);
    ADD_COMPARE(neteq_filter_target_loss);
    ADD_COMPARE(neteq_max_filter_window);
    ADD_COMPARE(neteq_enable_expired_peak_detector);
    ADD_COMPARE(neteq_enable_peak_detector);
    ADD_COMPARE(neteq_max_exceed_time_ms);
    ADD_COMPARE(neteq_max_filter_dup_num);
    ADD_COMPARE(neteq_enable_voice_volume_level);
    ADD_COMPARE(neteq_enable_individuality_delay);
    ADD_COMPARE(neteq_enable_improve_burst);
    ADD_COMPARE(neteq_low_latency_burst_control_window_ms);
    ADD_COMPARE(neteq_low_latency_burst_control_platform_ms);
    ADD_COMPARE(neteq_low_latency_burst_peak_num_threshold);
    ADD_COMPARE(neteq_low_latency_burst_trend_threshold);
    ADD_COMPARE(neteq_low_latency_burst_peak_trend_increased_threshold);
    ADD_COMPARE(neteq_low_latency_burst_overuse_limited_quantile);
    ADD_COMPARE(neteq_low_latency_burst_comb_window_second);
    ADD_COMPARE(neteq_low_latency_burst_max_jitter_limit_ms);
    ADD_COMPARE(neteq_high_latency_burst_control_window_ms);
    ADD_COMPARE(neteq_high_latency_burst_control_platform_ms);
    ADD_COMPARE(neteq_high_latency_burst_peak_num_threshold);
    ADD_COMPARE(neteq_high_latency_burst_trend_threshold);
    ADD_COMPARE(neteq_high_latency_burst_peak_trend_increased_threshold);
    ADD_COMPARE(neteq_high_latency_burst_overuse_limited_quantile);
    ADD_COMPARE(neteq_high_latency_burst_comb_window_second);
    ADD_COMPARE(neteq_high_latency_burst_max_jitter_limit_ms);
    ADD_COMPARE(neteq_targetlevel_offset);
    ADD_COMPARE(neteq_enable_stable_playout);
    ADD_COMPARE(neteq_drop_window_threshold_ms);
    ADD_COMPARE(neteq_drop_distance_threshold_ms);
    ADD_COMPARE(neteq_prebuffer_window_threshold_ms);
    ADD_COMPARE(neteq_prebuffer_distance_threshold_ms);
    ADD_COMPARE(neteq_max_packets_stable_playout);
    ADD_COMPARE(neteq_normal_recv_rate_ratio_threshold);
    ADD_COMPARE(neteq_target_level_optimization);
    ADD_COMPARE(neteq_aqm_voice_threshold);
    ADD_COMPARE(neteq_dump_level);
    ADD_COMPARE(neteq_dump_path);
    ADD_COMPARE(neteq_limit_prob);
    ADD_COMPARE(neteq_pre_dump);
    ADD_COMPARE(neteq_lower_limit_probability);
    ADD_COMPARE(neteq_plc_mode);
    ADD_COMPARE(dwlink_gain);
    ADD_COMPARE(uplink_gain);
    ADD_COMPARE(derived_headset_black_list_device);
    ADD_COMPARE(use_media_volume_in_headset);
    ADD_COMPARE(use_media_volume_in_audience);
    ADD_COMPARE(use_media_volume_in_solo);
    ADD_COMPARE(use_media_volume_in_bluetooth);
    END_COMPARE_AND_RETURN();
  }

  AudioOptions& Filter() {
    UNPUBLISH(derived_headset_black_list_device);
    return *this;
  }

  bool operator!=(const AudioOptions& o) const { return !(*this == o); }

  Optional<uint32_t> audio_scenario;  // agora::rtc::AUDIO_SCENARIO_TYPE
  Optional<uint32_t> audio_routing;  // agora::rtc::AudioRoute
  Optional<uint32_t> opensl_mode;  // agora::rtc::OPENSL_MODE
  Optional<bool> adm_enable_estimated_device_delay;
  Optional<int32_t> adm_device_delay_calc_period;
  Optional<int32_t>audio_routing_version;
  Optional<bool> adm_enable_preferred_aec_delay;
  Optional<bool> adm_enable_lowlatency_capture;
  Optional<bool> adm_duck_others;
  // ios::AVAudioSessionCategoryOptionMixWithOthers
  Optional<bool> adm_mix_with_others;
  Optional<bool> adm_restart_when_interrupted;
  Optional<int> adm_specify_category;
  Optional<bool> adm_enable_oboe;
  Optional<bool> adm_enable_fallback;
  Optional<bool> adm_record_audio_session_call_stack;
  Optional<bool> has_remote_peers;
  Optional<bool> has_enabled_ear_monitor;
  Optional<uint32_t> adm_input_sample_rate;
  Optional<uint32_t> adm_output_sample_rate;
  Optional<bool> adm_enable_exclusive_mode;
  Optional<uint32_t> adm_input_channels;
  Optional<uint32_t> adm_output_channels;
  Optional<bool> adm_has_recorded;
  Optional<bool> adm_enable_mic_selection;
  // ios::AVAudioSessionCategoryOptionAllowBluetoothA2DP
  Optional<bool> adm_force_use_bluetooth_a2dp;
  Optional<bool> adm_use_bluetooth_hfp;
  Optional<bool> adm_use_hw_aec;
  Optional<bool> adm_enable_hardware_ear_monitor;
  Optional<bool> adm_force_restart;
  Optional<uint32_t> adm_audio_layer;
  Optional<uint32_t> adm_audio_source;  // for android
  Optional<uint32_t> adm_playout_bufsize_factor;  // for android
  Optional<bool> adm_enable_builtin3a;
  Optional<bool> downlink_peq_enable;
  Optional<int> adm_extra_playout_latency; // for android
  Optional<int> adm_extra_record_latency; // for android
  Optional<int> adm_opensl_output_bufs;
  Optional<int> adm_opensl_input_bufs;
  Optional<int> apm_process_channels;  // agora::media::base::AUDIO_PROCESS_CHANNELS
  Optional<bool> apm_enable_aec;
  Optional<bool> apm_enable_aec_external;
  Optional<int> apm_aec_nlp_plan;
  Optional<int> apm_aec_audio_mixing;
  Optional<bool> apm_aec_saturated;
  Optional<int> apm_aec_nlp_size;
  Optional<int> apm_aec_delay_search_method;
  Optional<int> apm_aec_fixed_delay;
  Optional<int> apm_aec_extra_delay_bias;
  Optional<int> adm_ext_recording_source_delay_ms;
  Optional<int> apm_aec_ainlp_reset_period;
  Optional<int> apm_aec_ainlp_reset_ratio;
  Optional<int> apm_aec_ainlp_fallback_period;
  Optional<int> apm_aec_ainlp_postprocessing_method;
  Optional<int> apm_aec_linear_filter_type;
  Optional<bool> apm_enable_ns;
  Optional<int> apm_ains_mode;
  Optional<int> apm_ains_gain_control;
  Optional<int> apm_ains_speech_enhance;
  Optional<bool> apm_enable_agc;
  Optional<bool> apm_enable_md;
  Optional<int> apm_aimd_value;
  Optional<bool> apm_enable_highpass_filter;
  Optional<bool> apm_enable_tone_remover;
  Optional<bool> apm_enable_pitch_smoother;
  Optional<bool> apm_enable_howling_control;
  Optional<uint32_t> apm_delay_offset_ms;
  Optional<int32_t> apm_aec_nlp_aggressiveness;
  Optional<int32_t> apm_aec_complexity;
  Optional<int32_t> apm_aec_farend_energythreshold;
  Optional<int32_t> apm_aec_ref_gain;
  Optional<int32_t> apm_aec_sw_processing_mode;
  Optional<int32_t> apm_aec_linear_filter_length_ms;
  Optional<int32_t> apm_aec_split_srate_for_32k;
  Optional<int32_t> apm_aec_split_srate_for_48k;
  Optional<uint32_t> apm_agc_target_level_dbfs;
  Optional<uint32_t> apm_agc_compression_gain_db;
  Optional<uint32_t> apm_agc_curve_slope;
  Optional<uint32_t> apm_agc_mode;
  Optional<uint32_t> apm_ns_enable_ns_follow_agc;
  Optional<int32_t>  apm_ns_level;
  Optional<uint32_t> apm_ns_noiseGateThres;
  Optional<int32_t> apm_ns_complexity;
  // AINS
  // che.audio.nsng.anasize , che.audio.nsng.fftsize
  Optional<int32_t> apm_ains_fft_size;
  // che.audio.nsng.maxtime
  Optional<int32_t> apm_ains_maxtolerant_ms;
  // che.audio.nsng.attackfactor
  Optional<int32_t> apm_ains_attack_factor;
  // che.audio.nsng.releasefactor
  Optional<int32_t> apm_ains_release_factor;
  // che.audio.nsng.upperbound
  Optional<int32_t> apm_ains_upper_bound;
  // che.audio.nsng.uppermask
  Optional<int32_t> apm_ains_upper_mask;
  // che.audio.nsng.lowerBound
  Optional<int32_t> apm_ains_lower_bound;
  // che.audio.nsng.lowerMask
  Optional<int32_t> apm_ains_lower_mask;
  //che.audio.ns.end_startup_long
  Optional<int32_t> apm_nsng_end_start_up_long;
  //che.audio.ns.end_startup_short
  Optional<int32_t> apm_nsng_end_start_up_short;
  //che.audio.ns.quntile
  Optional<int32_t> apm_nsng_quantile;
  //che.audio.ns.noise_update_factor
  Optional<int32_t> apm_nsng_noise_update_factor;
  //che.audio.ns.speech_update_factor
  Optional<int32_t> apm_nsng_speech_update_factor;
  //che.audio.ns.overdrive
  Optional<int32_t> apm_nsng_overdrive;
  //che.audio.vad.threshold
  Optional<int32_t> apm_nsng_vad_threshold;
  //che.audio.md.threshold
  Optional<int32_t> apm_nsng_md_threshold;
  //che.audio.nsng.ains_reset_frame
  Optional<int32_t> apm_ains_reset_frame;
  //che.audio.nsng.ains_kill_highband
  Optional<int32_t> apm_ains_kill_highband;
  //che.audio.ns.noise_ref_protect
  Optional<int32_t> apm_nsng_noise_ref_protect;
  // che.audio.nsng.triangle_1
  Optional<int32_t> apm_ains_triangle_1;
  // che.audio.nsng.triangle_2
  Optional<int32_t> apm_ains_triangle_2;
  // che.audio.nsng.triangle_3
  Optional<int32_t> apm_ains_triangle_3;
  // che.audio.nsng.thresholdai
  Optional<int32_t> apm_ains_threshold_ai;
  // che.audio.nsng.thresholdstastical
  Optional<int32_t> apm_ains_threshold_stastical;
  // che.audio.nsng.enhfactorai
  Optional<int32_t> apm_ains_enh_factor_ai;
  // che.audio.nsng.enhfactorstastical
  Optional<int32_t> apm_ains_enh_factor_stastical;
  // che.audio.nsng.noiseoverestimate
  Optional<int32_t> apm_ains_noise_over_estimate;
  // che.audio.nsng.statisticalbound
  Optional<int32_t> apm_ains_statistical_bound;
  // che.audio.nsng.gainboostfreq1
  Optional<int32_t> apm_ains_gain_boost_frq1;
  // che.audio.nsng.gainboostval1
  Optional<int32_t> apm_ains_gain_boost_gain1;
  // che.audio.nsng.gainboostfreq2
  Optional<int32_t> apm_ains_gain_boost_frq2;
  // che.audio.nsng.gainboostval2
  Optional<int32_t> apm_ains_gain_boost_gain2;
  // che.audio.nsng.gainboostfreq3
  Optional<int32_t> apm_ains_gain_boost_frq3;
  // che.audio.nsng.gainboostval3
  Optional<int32_t> apm_ains_gain_boost_gain3;
  // che.audio.nsng.finallowermask
  Optional<int32_t> apm_ains_final_lower_mask;
  // che.audio.nsng.noisepowfloor
  Optional<int32_t> apm_ains_noise_pow_floor;
  // che.audio.nsng.pinkfactor , che.audio.nsng.cngbasemagnitude
  Optional<int32_t> apm_ains_cng_base_magnitude;
  // che.audio.nsng.strategy
  Optional<int32_t> apm_ains_strategy;
  // che.audio.nsng.postfiltermargin
  Optional<int32_t> apm_ains_postfilter_margin;
  // che.audio.nsng.delaymode
  Optional<int32_t> apm_ains_delaymode;
  // che.audio.nsng.aggressive
  Optional<int32_t> apm_ains_aggressive;

  // Double talk detection switcher.
  // Android game streaming scenario should be true, all other cases should be false;
  Optional<bool> apm_enable_record_boost;
  Optional<int32_t> apm_farend_gain_threshold;
  Optional<bool> adm_mac_use_audio_unit_hal;
  Optional<uint32_t> apm_farend_gain;
  Optional<uint32_t> acm_bitrate;
  Optional<uint32_t> acm_codec;
  Optional<bool> acm_dtx;
  Optional<bool> acm_plc;
  Optional<uint32_t> acm_complex_level;
  Optional<uint32_t> acm_ptime;
  Optional<bool> acm_hw_encode_opus;
  Optional<bool> acm_hw_decode_opus;
  Optional<bool> acm_opus_celt_only;
  Optional<bool> acm_opus_enable_volume_based_bitrate_reduction;
  Optional<int32_t> acm_opus_voice_threshold;
  Optional<int32_t> acm_opus_voice_up_coef;
  Optional<int32_t> acm_opus_voice_down_coef;
  Optional<int32_t> acm_opus_voice_hold_window_ms;
  Optional<int32_t> acm_opus_silence_bitrate;
  Optional<bool> audio_resend;
  Optional<uint32_t> audio_rsfec_frame_num;
  Optional<uint32_t> audio_rsfec_interleave_num;
  Optional<uint32_t> audio_fec_frame_num;
  Optional<uint32_t> audio_fec_interleave_num;
  Optional<uint32_t> neteq_live_min_delay;
  Optional<uint32_t> neteq_jitter_buffer_max_packets;
  Optional<bool> neteq_jitter_buffer_fast_accelerate;
  Optional<int32_t> neteq_jitter_max_target_delay;
  Optional<int32_t> neteq_filter_target_loss;
  Optional<int32_t> neteq_max_filter_window;
  Optional<bool> neteq_enable_expired_peak_detector;
  Optional<bool> neteq_enable_peak_detector;
  Optional<int32_t> neteq_max_exceed_time_ms;
  Optional<uint32_t> neteq_max_filter_dup_num;
  Optional<bool> neteq_enable_voice_volume_level;
  Optional<bool> neteq_enable_individuality_delay;
  Optional<bool> neteq_enable_improve_burst;
  Optional<int32_t> neteq_low_latency_burst_control_window_ms;
  Optional<int32_t> neteq_low_latency_burst_control_platform_ms;
  Optional<int32_t> neteq_low_latency_burst_peak_num_threshold;
  Optional<int32_t> neteq_low_latency_burst_trend_threshold;
  Optional<int32_t> neteq_low_latency_burst_peak_trend_increased_threshold;
  Optional<int32_t> neteq_low_latency_burst_overuse_limited_quantile;
  Optional<int32_t> neteq_low_latency_burst_comb_window_second;
  Optional<int32_t> neteq_low_latency_burst_max_jitter_limit_ms;
  Optional<int32_t> neteq_high_latency_burst_control_window_ms;
  Optional<int32_t> neteq_high_latency_burst_control_platform_ms;
  Optional<int32_t> neteq_high_latency_burst_peak_num_threshold;
  Optional<int32_t> neteq_high_latency_burst_trend_threshold;
  Optional<int32_t> neteq_high_latency_burst_peak_trend_increased_threshold;
  Optional<int32_t> neteq_high_latency_burst_overuse_limited_quantile;
  Optional<int32_t> neteq_high_latency_burst_comb_window_second;
  Optional<int32_t> neteq_high_latency_burst_max_jitter_limit_ms;
  Optional<int32_t> neteq_targetlevel_offset;
  Optional<bool> neteq_enable_stable_playout;
  Optional<int32_t> neteq_drop_window_threshold_ms;
  Optional<int32_t> neteq_drop_distance_threshold_ms;
  Optional<int32_t> neteq_prebuffer_window_threshold_ms;
  Optional<int32_t> neteq_prebuffer_distance_threshold_ms;
  Optional<int32_t> neteq_max_packets_stable_playout;
  Optional<int32_t> neteq_normal_recv_rate_ratio_threshold;

  Optional<bool> neteq_target_level_optimization;
  Optional<uint32_t> neteq_aqm_voice_threshold;
  Optional<uint32_t> neteq_dump_level;
  Optional<std::string> neteq_dump_path;
  Optional<int> neteq_limit_prob;
  Optional<int> neteq_pre_dump;
  Optional<int> neteq_lower_limit_probability;
  Optional<int> neteq_plc_mode;
  Optional<uint32_t> dwlink_gain;
  Optional<uint32_t> uplink_gain;

  // derived options
  Optional<bool> derived_headset_black_list_device;
  Optional<int> use_media_volume_in_headset;
  Optional<int> use_media_volume_in_audience;
  Optional<int> use_media_volume_in_solo;
  Optional<int> use_media_volume_in_bluetooth;

 private:
  template <typename T>
  static void SetFrom(Optional<T>* s, const Optional<T>& o) {
    if (o) {
      *s = o;
    }
  }
};

}  // namespace rtc
}  // namespace agora
