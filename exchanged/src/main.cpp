#include "parkett/version.h"

#include <iostream>

int main()
{
    const auto version = parkett::version();
    std::cout << "Parkett Exchange Daemon version " << version << " running.\n";

    return 0;
}
