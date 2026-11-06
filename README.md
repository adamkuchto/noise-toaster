# Noise Toaster

Syntezator szumów C++20.

## Technologie

- C++20
- CMake
- Ninja
- JUCE 
- JACK / PipeWire

## Budowa

```bash
cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug

cmake --build build
```

## Uruchomienie

```bash
./build/noise-toaster
```
