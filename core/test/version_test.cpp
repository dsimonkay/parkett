#include "parkett/version.h"

#include <catch2/catch_test_macros.hpp>

namespace parkett::test
{

TEST_CASE("The version string is not empty.", "[version]")
{
    REQUIRE(!version().empty());
}

} // namespace parkett::test
