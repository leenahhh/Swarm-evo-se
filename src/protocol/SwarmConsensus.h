#ifndef SWARMCONSENSUS_H
#define SWARMCONSENSUS_H

#include <cstdint>

class SwarmConsensus {
public:
    static uint32_t adaptiveThreshold(uint32_t neighbours);
};

#endif // SWARMCONSENSUS_H
