cmake_minimum_required(VERSION 3.28)
project(parkett LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14)
    message(FATAL_ERROR "Parkett requires GCC 14 or newer (found ${CMAKE_CXX_COMPILER_VERSION})")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)   # error instead of silent fallback
set(CMAKE_CXX_EXTENSIONS OFF)         # -std=c++23, not -std=gnu++23
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(parkett_warnings INTERFACE)
target_compile_options(parkett_warnings INTERFACE
    -Wall -Wextra -Wpedantic -Werror
)

# Everything about testing
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.7.1
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(Catch2)
enable_testing()
option(PARKETT_BUILD_TESTS "Build tests" ON)

add_subdirectory(core)
add_subdirectory(exchanged)
