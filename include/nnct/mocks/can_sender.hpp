#pragma once

#include <nnct/interfaces/can_sender.hpp>

namespace nnct::mocks {
    
class CanSender : public interfaces::CanSender {
    public:
        void send(const types::can::Frame& frame) override;
        void clear();
        
        bool called                     { false };
        bool latest_is_std              { false };
        bool latest_is_ext              { false };
        uint32_t latest_id              { 0 };
        types::can::Data latest_data    { constants::can::EMPTY };
        uint8_t latest_dlc              { 0 };
};
    
}
