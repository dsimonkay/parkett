add_executable(exchanged
    src/main.cpp
)

target_include_directories(exchanged
    PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(exchanged PUBLIC cxx_std_23)

target_link_libraries(exchanged PRIVATE parkett_warnings)
target_link_libraries(exchanged PRIVATE parkett::core)
