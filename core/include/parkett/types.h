#ifndef PARKETT_CORE_TYPES_H_
#define PARKETT_CORE_TYPES_H_

#include "parkett/strong_type.h"

#include <chrono>
#include <cstdint>

namespace parkett
{

/// @brief Describing transaction side
enum class Side : std::uint8_t
{
    Buy,
    Sell
};

/// @brief Classifying order type
enum class OrderType : std::uint8_t
{
    Limit,
    Market
};

/// @brief Rejecting an order
enum class RejectReason : std::uint8_t
{
    UnknownClient,
    WrongInstrument,
    ZeroQuantity,
    NegativeQuantity,
    PriceOffTickGrid
};

// The clock is deliberately a single alias: M4 replaces it with a
// clock abstraction (real vs. accelerated simulated time).
using Clock = std::chrono::system_clock;
using Duration = std::chrono::nanoseconds;
using Timestamp = std::chrono::time_point<Clock, Duration>;

/// @brief The main domain model types
// clang-format off
struct OrderIdTag {};
struct ClientIdTag {};
struct QuantityTag {};
struct InstrumentIdTag {};
// clang-format on

using OrderId = StrongType<std::uint64_t, OrderIdTag, TotallyOrdered>;
using ClientId = StrongType<std::uint64_t, ClientIdTag>;
using Quantity = StrongType<std::int64_t, QuantityTag, Additive, TotallyOrdered>;
using InstrumentId = StrongType<std::uint64_t, InstrumentIdTag, TotallyOrdered>;

struct Order
{
    OrderId id{};
    Timestamp received_at{};
    ClientId client{};
    InstrumentId instrument{};
    Side side{};
    OrderType type{};
    Quantity quantity{};
    // Price price{};

    [[nodiscard]] constexpr bool operator==(const Order&) const = default;
};

} // namespace parkett

#endif // PARKETT_CORE_TYPES_H_
