#ifndef PARKETT_CORE_STRONG_TYPE_H_
#define PARKETT_CORE_STRONG_TYPE_H_

#include <compare>
#include <concepts>

template <typename T>
concept UnderlyingStrongType = std::integral<T> && !std::same_as<T, bool>;

template <UnderlyingStrongType U, typename Tag, template <typename> class... Features>
class StrongType : public Features<StrongType<U, Tag, Features...>>...
{
  public:
    using underlying_type = U;
    using tag = Tag;

    StrongType() = default;
    constexpr explicit StrongType(U value) noexcept : value_{value} {}

    [[nodiscard]] constexpr U value() const noexcept
    {
        return value_;
    }

    [[nodiscard]] constexpr bool operator==(const StrongType& other) const noexcept = default;

  private:
    U value_{}; // losing trivially default constructibility, but it's not needed anyway
};

// ---------------------------------------------------------------------------
// Concept: T is exactly StrongType<U, Tag, Features...>.
// It works with an incomplete type too, which matters: when the mixin
// is instantiated, Derived (i.e. StrongType itself) is not complete yet.
// ---------------------------------------------------------------------------
template <typename T> struct is_strong_type : std::false_type
{
};

template <UnderlyingStrongType U, typename Tag, template <typename> class... Features>
struct is_strong_type<StrongType<U, Tag, Features...>> : std::true_type
{
};

template <typename T>
concept StrongTypeImplementation = is_strong_type<std::remove_cvref_t<T>>::value;

// ---------------------------------------------------------------------------
// Mixins. They are not constrained in the template head, because a constrained
// template cannot be passed to StrongType's unconstrained
// `template <typename> class...` parameter.
// That's why the check is a static_assert.
// ---------------------------------------------------------------------------
template <typename Derived> class Additive
{
  public:
    // Hidden friend: its body is only instantiated when used, by which time Derived is complete.
    [[nodiscard]] friend constexpr Derived operator+(const Derived& lhs,
                                                     const Derived& rhs) noexcept
    {
        return Derived{static_cast<typename Derived::underlying_type>(lhs.value() + rhs.value())};
    }

    [[nodiscard]] friend constexpr Derived operator-(const Derived& lhs,
                                                     const Derived& rhs) noexcept
    {
        return Derived{static_cast<typename Derived::underlying_type>(lhs.value() - rhs.value())};
    }

  private:
    static_assert(StrongTypeImplementation<Derived>,
                  "Additive can only be used as a StrongType feature");
};

template <typename Derived> class TotallyOrdered
{
  public:
    [[nodiscard]] friend constexpr auto operator<=>(const Derived& lhs, const Derived& rhs) noexcept
    {
        return lhs.value() <=> rhs.value();
    }

  private:
    static_assert(StrongTypeImplementation<Derived>,
                  "TotallyOrdered can only be used as a StrongType feature");
};

#endif // PARKETT_CORE_STRONG_TYPE_H_
