#include "parkett/types.h"

#include <catch2/catch_test_macros.hpp>

namespace parkett::test
{

using SomeStrongType = StrongType<std::uint32_t, struct SomeTag>;

TEST_CASE("A strong type is trivially copiable", "[types]")
{
    REQUIRE(std::is_trivially_copyable_v<SomeStrongType>);
}

TEST_CASE("The size of a strong types corresponds to that of the stored underlying type", "[types]")
{
    REQUIRE(sizeof(SomeStrongType) == sizeof(SomeStrongType::underlying_type));
}

TEST_CASE(
    "Two StrongType instances instantiated using different tags are not convertible to one another",
    "[types]")
{
    using AnotherStrongType = StrongType<std::uint32_t, struct AnotherTag>;
    REQUIRE(!std::is_same_v<SomeStrongType, AnotherStrongType>);
    REQUIRE(!std::is_convertible_v<SomeStrongType, AnotherStrongType>);
}

// clang-format off
template <typename T> concept IsAdditive = requires(T a, T b) { a + b; };
template <typename T> concept CanBeOrdered = requires(T a, T b) { a <=> b; };
// clang-format on

TEST_CASE("Testing additivity", "[types]")
{
    REQUIRE(IsAdditive<Quantity>);
    REQUIRE(!IsAdditive<ClientId>);
    REQUIRE(!IsAdditive<OrderId>);
    REQUIRE(!IsAdditive<InstrumentId>);
}

TEST_CASE("Testing orderability", "[types]")
{
    REQUIRE(CanBeOrdered<Quantity>);
    REQUIRE(!CanBeOrdered<ClientId>);
    REQUIRE(CanBeOrdered<OrderId>);
    REQUIRE(CanBeOrdered<InstrumentId>);
    REQUIRE(CanBeOrdered<Timestamp>);
}

TEST_CASE("Testing Timestamp properties", "[types]")
{
    REQUIRE(std::is_trivially_copyable_v<Timestamp>);
    REQUIRE(sizeof(Timestamp) == 8);
    REQUIRE(!IsAdditive<Timestamp>);
    REQUIRE(std::is_same_v<decltype(Timestamp{} - Timestamp{}), Duration>);
    REQUIRE(std::is_same_v<decltype(Timestamp{} <=> Timestamp{}), std::strong_ordering>);
}

} // namespace parkett::test
