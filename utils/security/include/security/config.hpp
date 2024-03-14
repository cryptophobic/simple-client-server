#pragma once
#include <string>

namespace security {
    constexpr uint32_t hashLength = 32;
    constexpr uint32_t timeCost = 5;         // 2-pass computation
    constexpr uint32_t memoryCost = (1<<16); // 64 mebibytes memory usage
    constexpr uint32_t threadsNumber = 1;    // number of threads and lanes
    constexpr unsigned int saltLength = 32;
}