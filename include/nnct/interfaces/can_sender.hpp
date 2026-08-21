#pragma once

#include <cstdint>
#include <nnct/types/can.hpp>
#include <nnct/constants/can_data_empty.hpp>

namespace nnct::interfaces {
    
class CanSender {
    public:
        virtual void send(const types::can::Frame& frame) = 0;

        void sendStandard(types::can::std_id_t id, const types::can::data_t& data, uint8_t len) { send({id, data, len, false}); }
        void sendExtended(types::can::std_id_t id, const types::can::data_t& data, uint8_t len) { send({id, data, len, true}); }

        void sendStandard(types::can::std_id_t id) { sendStandard(id, constants::can::EMPTY, 0); }
        void sendExtended(types::can::ext_id_t id) { sendExtended(id, constants::can::EMPTY, 0); }
};

}
