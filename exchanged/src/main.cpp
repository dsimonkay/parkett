#include "parkett/version.h"

#include <print>

int main()
{
    const auto version = parkett::version();
    std::println("Parkett Exchange Daemon version {} running.", version);

    return 0;
}
