#pragma once

#include <cstdint>

namespace nnct::interfaces {

class SpeedEncoder {
    public:
        virtual double getSpeed();
};

} // namespace nnct::interfaces