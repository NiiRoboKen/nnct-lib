#pragma once

#include <cstdint>

namespace nnct::interfaces {

class SpeedEncoder {
    public:
        virtual int16_t getSpeed();
};

} // namespace nnct::interfaces