#include "parkett/version.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("version string is not empty", "[version]")
{
    REQUIRE(!parkett::version().empty());
}
