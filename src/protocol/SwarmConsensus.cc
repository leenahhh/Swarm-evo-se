#include "SwarmConsensus.h"

#include <algorithm>
#include <cmath>

uint32_t SwarmConsensus::adaptiveThreshold(uint32_t neighbours) {
    if (neighbours > 100) {
        return static_cast<uint32_t>(std::ceil(0.67 * neighbours));
    }
    if (neighbours >= 10) {
        return static_cast<uint32_t>(std::ceil(0.51 * neighbours));
    }
    if (neighbours >= 3) {
        const auto threshold =
            static_cast<uint32_t>(std::ceil(0.34 * neighbours));
        return std::max<uint32_t>(3, threshold);
    }
    return 1;
}
