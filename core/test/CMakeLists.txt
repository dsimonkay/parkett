add_executable(parkett_tests
    version_test.cpp
)

target_link_libraries(parkett_tests
    PRIVATE
        parkett::core
        parkett_warnings
        Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(parkett_tests)
