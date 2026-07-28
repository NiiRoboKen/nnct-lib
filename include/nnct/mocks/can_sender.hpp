#pragma once

#include "nnct/types/can.hpp"
#include <nnct/interfaces/can_sender.hpp>

namespace nnct::mocks {
    
class CanSender : public interfaces::CanSender {
    public:
        void send(const types::can::Frame& frame) override;
        
        bool called { false };
        bool latest_is_std;
        bool latest_is_ext;
        uint32_t latest_id;
        types::can::Data latest_data;
        uint8_t latest_dlc;
};
    
}
