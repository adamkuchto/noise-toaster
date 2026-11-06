cmake_minimum_required(VERSION 3.20)

project(NoiseToaster
    VERSION 0.1.0
    DESCRIPTION "Digital Audio Synthesis Engine"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(noise-toaster
    src/main.cpp
)

target_compile_options(noise-toaster PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
