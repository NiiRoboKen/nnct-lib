#pragma once

#include <cstdint>
#include <nnct/types/can.hpp>

namespace nnct::interfaces {
    
class CanSender {
    public:
        virtual void sendStandard(uint16_t id, const types::can::Data& data, uint8_t dlc) = 0;
        virtual void sendExtended(uint32_t id, const types::can::Data& data, uint8_t dlc) = 0;
};

}
