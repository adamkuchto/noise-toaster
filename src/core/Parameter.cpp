#include "Parameter.h"

#include <algorithm>
#include <stdexcept>

Parameter::Parameter(float minimum, float maximum, float initial)
    : minimum_(minimum), maximum_(maximum), value_(initial) {
  if (minimum_ > maximum_) {
    throw std::invalid_argument("Invalid parameter range");
  }

  setValue(initial);
}

void Parameter::setValue(float value) noexcept {
  value_ = std::clamp(value, minimum_, maximum_);
}

float Parameter::value() const noexcept { return value_; }

float Parameter::minimum() const noexcept { return minimum_; }

float Parameter::maximum() const noexcept { return maximum_; }
