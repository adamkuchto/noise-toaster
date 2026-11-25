#pragma once

class Parameter final {
public:
  Parameter(float minimum, float maximum, float initial);

  void setValue(float value) noexcept;

  [[nodiscard]] float value() const noexcept;
  [[nodiscard]] float minimum() const noexcept;
  [[nodiscard]] float maximum() const noexcept;

private:
  float minimum_;
  float maximum_;
  float value_;
};
