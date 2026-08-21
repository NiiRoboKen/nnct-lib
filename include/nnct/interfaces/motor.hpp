#pragma once

#include <cstdint>

namespace nnct::interfaces {

class Motor {
    public:
        virtual void setDuty(int16_t duty) = 0;
        inline void  stopMotor() { setDuty(0); };
};

} // namespace nnct::interfaces
