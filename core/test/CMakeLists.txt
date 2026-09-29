add_executable(parkett_core_tests
    types_test.cpp
    version_test.cpp
)

target_link_libraries(parkett_core_tests
    PRIVATE
        parkett::core
        parkett_warnings
        Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(parkett_core_tests TEST_PREFIX "core.")
