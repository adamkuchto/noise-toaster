#include "SineOscillator.h"

#include <cmath>
#include <numbers>
#include <stdexcept>

namespace {
constexpr float twoPi = 2.0f * std::numbers::pi_v<float>;
}

SineOscillator::SineOscillator(float sampleRate, float frequency,
                               float amplitude)
    : sampleRate_(sampleRate), frequency_(frequency), amplitude_(amplitude) {
  if (!std::isfinite(sampleRate_) || sampleRate_ <= 0.0f) {
    throw std::invalid_argument("Invalid sample rate");
  }

  if (!std::isfinite(frequency_) || frequency_ < 0.0f ||
      frequency_ >= sampleRate_ / 2.0f) {
    throw std::invalid_argument("Invalid frequency");
  }

  if (!std::isfinite(amplitude_) || amplitude_ < 0.0f || amplitude_ > 1.0f) {
    throw std::invalid_argument("Invalid amplitude");
  }

  updatePhaseIncrement();
}

void SineOscillator::setFrequency(float frequency) {
  if (!std::isfinite(frequency) || frequency < 0.0f ||
      frequency >= sampleRate_ / 2.0f) {
    throw std::invalid_argument("Invalid frequency");
  }

  frequency_ = frequency;
  updatePhaseIncrement();
}

void SineOscillator::setAmplitude(float amplitude) {
  if (!std::isfinite(amplitude) || amplitude < 0.0f || amplitude > 1.0f) {
    throw std::invalid_argument("Invalid amplitude");
  }

  amplitude_ = amplitude;
}

void SineOscillator::reset() noexcept { phase_ = 0.0f; }

void SineOscillator::updatePhaseIncrement() noexcept {
  phaseIncrement_ = twoPi * (frequency_ / sampleRate_);
}

float SineOscillator::nextSample() noexcept {
  const float sample = amplitude_ * std::sin(phase_);

  phase_ += phaseIncrement_;

  if (phase_ >= twoPi) {
    phase_ -= twoPi;
  }

  return sample;
}

void SineOscillator::render(std::span<float> output) noexcept {
  for (float &sample : output) {
    sample = nextSample();
  }
}
