#pragma once

#include <cstdint>

namespace nnct::interfaces {
    
class Motor {
    public:
        virtual void setDuty(int16_t duty) = 0;
};

}
