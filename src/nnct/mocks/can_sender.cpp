#include "nnct/constants/can_data_empty.hpp"
#include <nnct/mocks/can_sender.hpp>

namespace nnct::mocks {
    
void CanSender::send(const types::can::Frame& frame) {
    called          = true;
    latest_is_std   = not frame.extd;
    latest_is_ext   = frame.extd;
    latest_id       = frame.id;
    latest_data     = frame.data;
    latest_len      = frame.len;
}

void CanSender::clear() {
    called          = false;
    latest_is_std   = false;
    latest_is_ext   = false;
    latest_id       = 0;
    latest_data     = constants::can::EMPTY;
    latest_len      = 0;
}
    
}
