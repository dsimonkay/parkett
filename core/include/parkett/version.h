#ifndef PARKETT_CORE_VERSION_H_
#define PARKETT_CORE_VERSION_H_

#include <string_view>

namespace parkett
{

/// @brief Provides simple version information.
/// @return the version of the Parkett system.
[[nodiscard]] std::string_view version() noexcept;

} // namespace parkett

#endif // PARKETT_CORE_VERSION_H_
