#include "core/Parameter.h"

#include <iostream>
#include <memory>
#include <vector>

namespace {
void printFrequency(const Parameter &frequency) {
  std::cout << "Frequency: " << frequency.value() << " Hz\n";
}

void setFrequency(Parameter &frequency, float value) {
  frequency.setValue(value);
}
} // namespace

int main() {
  Parameter frequency{20.0f, 20000.0f, 440.0f};

  printFrequency(frequency);

  setFrequency(frequency, 880.0f);
  printFrequency(frequency);

  setFrequency(frequency, 25000.0f);
  printFrequency(frequency);

  return 0;
}
