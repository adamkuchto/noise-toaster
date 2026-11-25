#pragma once

#include <span>

class SineOscillator final {
public:
  SineOscillator(float sampleRate, float frequency, float amplitude = 0.5f);

  void setFrequency(float frequency);
  void setAmplitude(float amplitude);

  void reset() noexcept;

  [[nodiscard]] float nextSample() noexcept;

  void render(std::span<float> output) noexcept;

private:
  void updatePhaseIncrement() noexcept;

  float sampleRate_;
  float frequency_;
  float amplitude_;

  float phase_ = 0.0f;
  float phaseIncrement_ = 0.0f;
};
