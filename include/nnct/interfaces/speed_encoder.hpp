#pragma once

#include <cstdint>

namespace nnct::interfaces {

class SpeedEncoder {
    public:
        virtual void getSpeed();
};

} // namespace nnct::interfaces