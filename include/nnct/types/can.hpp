#pragma once

#include <cstdint>
#include <array>

namespace nnct::types::can {
    
using id_t = uint32_t;
using ext_id_t = uint32_t;
using std_id_t = uint16_t;

using data_t = std::array<uint8_t, 8>;

struct Frame {
    uint32_t    id;
    data_t      data;
    uint8_t     len;
    bool        extd;
};

struct FilterdFrame {
    data_t  data;
    uint8_t len;

    static FilterdFrame fromFrame(const Frame& frame) { return {frame.data, frame.len}; }
};

}
