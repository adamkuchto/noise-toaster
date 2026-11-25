#include "dsp/SineOscillator.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>
#include <span>
#include <stdexcept>
#include <vector>

namespace {

void writeU16LE(std::ostream &output, std::uint16_t value) {
  const char bytes[2] = {static_cast<char>(value & 0xFFu),
                         static_cast<char>((value >> 8) & 0xFFu)};

  output.write(bytes, 2);
}

void writeU32LE(std::ostream &output, std::uint32_t value) {
  const char bytes[4] = {static_cast<char>(value & 0xFFu),
                         static_cast<char>((value >> 8) & 0xFFu),
                         static_cast<char>((value >> 16) & 0xFFu),
                         static_cast<char>((value >> 24) & 0xFFu)};

  output.write(bytes, 4);
}

void writeWav16Mono(const char *path, std::uint32_t sampleRate,
                    std::span<const float> samples) {
  constexpr std::uint32_t bytesPerSample = 2;
  constexpr std::uint32_t headerSize = 44;

  if (sampleRate == 0 ||
      sampleRate > std::numeric_limits<std::uint32_t>::max() / 2u) {
    throw std::invalid_argument("Invalid WAV sample rate");
  }

  if (samples.size() >
      (std::numeric_limits<std::uint32_t>::max() - 36u) / bytesPerSample) {
    throw std::length_error("WAV file is too large");
  }

  const auto dataSize =
      static_cast<std::uint32_t>(samples.size() * bytesPerSample);

  const auto fileSize = 36u + dataSize;

  std::ofstream output(path, std::ios::binary);

  if (!output) {
    throw std::runtime_error("Cannot create WAV file");
  }

  output.write("RIFF", 4);
  writeU32LE(output, fileSize);
  output.write("WAVE", 4);

  output.write("fmt ", 4);
  writeU32LE(output, 16);
  writeU16LE(output, 1);
  writeU16LE(output, 1);
  writeU32LE(output, sampleRate);
  writeU32LE(output, sampleRate * 2u);
  writeU16LE(output, 2);
  writeU16LE(output, 16);

  output.write("data", 4);
  writeU32LE(output, dataSize);

  for (float sample : samples) {
    const float bounded = std::clamp(sample, -1.0f, 1.0f);

    const auto pcm = static_cast<std::int16_t>(std::lrint(bounded * 32767.0f));

    writeU16LE(output, static_cast<std::uint16_t>(pcm));
  }

  if (!output) {
    throw std::runtime_error("Failed while writing WAV file");
  }
}

} // namespace

int main() {
  try {
    constexpr std::uint32_t sampleRate = 48000;
    constexpr std::size_t durationSeconds = 2;

    constexpr float frequency = 1800.5f;
    constexpr float amplitude = 0.5f;

    const std::size_t sampleCount =
        static_cast<std::size_t>(sampleRate) * durationSeconds;

    std::vector<float> audioBuffer(sampleCount, 0.0f);

    SineOscillator oscillator(static_cast<float>(sampleRate), frequency,
                              amplitude);

    // Dzielimy bufor na dwie połowy
    const std::size_t splitPoint = sampleCount / 2;
    std::span<float> buffer{audioBuffer};

    // Pierwsza połowa bufora
    oscillator.render(buffer.first(splitPoint));

    // Resetujemy fazę oscylatora
    oscillator.reset();

    // Druga połowa bufora - faza zaczyna się od zera
    oscillator.render(buffer.subspan(splitPoint));

    // Zapisujemy cały bufor do pliku WAV
    writeWav16Mono("build/noise-toaster.wav", sampleRate,
                   std::span<const float>{audioBuffer});

    std::cout << "Noise Toaster - DSP test\n";
    std::cout << "Sample rate: " << sampleRate << " Hz\n";
    std::cout << "Frequency: " << frequency << " Hz\n";
    std::cout << "Amplitude: " << amplitude << "\n";
    std::cout << "Generated samples: " << sampleCount << "\n";
    std::cout << "Output: build/noise-toaster.wav\n";

  } catch (const std::exception &error) {
    std::cerr << "Error: " << error.what() << '\n';
    return 1;
  }

  return 0;
}
