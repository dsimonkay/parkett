add_library(parkett_core STATIC
    src/version.cpp
)

add_library(parkett::core ALIAS parkett_core)

target_include_directories(parkett_core
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(parkett_core PUBLIC cxx_std_23)

target_link_libraries(parkett_core PRIVATE parkett_warnings)

if(PARKETT_BUILD_TESTS)
    add_subdirectory(test)
endif()
