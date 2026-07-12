#pragma once

#include <cstdint>
#include <array>

namespace nnct::types::can {
    
using Data = std::array<uint8_t, 8>;

struct Frame {
    uint32_t id;
    Data data;
    uint8_t dlc;
    bool extd;
};

}
