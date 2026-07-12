#pragma once

#include <nnct/interfaces/can_sender.hpp>

namespace nnct::mocks {
    
class CanSender : public interfaces::CanSender {
    public:
        void sendStandard(uint16_t id, const types::can::Data& data, uint8_t dlc) override;
        void sendExtended(uint32_t id, const types::can::Data& data, uint8_t dlc) override;
        
        bool called { false };
        bool latest_is_std;
        bool latest_is_ext;
        uint32_t latest_id;
        types::can::Data latest_data;
        uint8_t latest_dlc;
};
    
}
