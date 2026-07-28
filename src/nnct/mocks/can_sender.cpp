#include <nnct/mocks/can_sender.hpp>

namespace nnct::mocks {
    
void CanSender::send(const types::can::Frame& frame) {
    called = true;
    latest_is_std = not frame.extd;
    latest_is_ext = frame.extd;
    latest_id = frame.id;
    latest_data = frame.data;
    latest_dlc = frame.dlc;
}
    
}
