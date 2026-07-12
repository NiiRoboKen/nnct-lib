#include <nnct/mocks/can_sender.hpp>

namespace nnct::mocks {
    
void CanSender::sendStandard(uint16_t id, const types::can::Data& data, uint8_t dlc) {
    called = true;
    latest_is_std = true;
    latest_is_ext = false;
    latest_id = id;
    latest_data = data;
    latest_dlc = dlc;
}

void CanSender::sendExtended(uint32_t id, const types::can::Data& data, uint8_t dlc) {
    called = true;
    latest_is_std = false;
    latest_is_ext = true;
    latest_id = id;
    latest_data = data;
    latest_dlc = dlc;
}
    
}
