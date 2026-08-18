cmake_minimum_required(VERSION 3.28)
project(parkett LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

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
