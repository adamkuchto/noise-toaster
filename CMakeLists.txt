cmake_minimum_required(VERSION 3.20)

project(NoiseToaster
    VERSION 0.1.0
    DESCRIPTION "Digital Audio Synthesis Engine"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(noise_toaster
    src/main.cpp
    src/core/Parameter.cpp
    src/dsp/SineOscillator.cpp
)

target_compile_definitions(noise_toaster PRIVATE
    APP_NAME=NoiseToaster
    APP_VERSION=v${PROJECT_VERSION}
    APP_DESCRIPTION=DigitalAudioSynthesisEngine
    BUILD_CONFIG=$<IF:$<CONFIG:>,None,$<CONFIG>>
)

target_compile_options(noise_toaster PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
