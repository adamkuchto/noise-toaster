#include <iostream>

#define STR(x) #x
#define XSTR(x) STR(x)

int main() {
  std::cout << "Noise Toaster " << XSTR(APP_VERSION) << "\n";
  std::cout << "Digital Audio Synthesis Engine\n";
  std::cout << "Build configuration: " << XSTR(BUILD_CONFIG) << "\n";
  return 0;
}
