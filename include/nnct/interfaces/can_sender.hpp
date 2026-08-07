#pragma once

#include <cstdint>
#include <nnct/types/can.hpp>
#include <nnct/constants/can_data_empty.hpp>

namespace nnct::interfaces {
    
class CanSender {
    public:
        virtual void send(const types::can::Frame& frame) = 0;

        void sendStandard(uint16_t id, const types::can::Data& data, uint8_t dlc) { send({id, data, dlc, false}); }
        void sendExtended(uint32_t id, const types::can::Data& data, uint8_t dlc) { send({id, data, dlc, true}); }

        void sendStandard(uint16_t id) { sendStandard(id, constants::can::EMPTY, 0); }
        void sendExtended(uint32_t id) { sendExtended(id, constants::can::EMPTY, 0); }
};

}
