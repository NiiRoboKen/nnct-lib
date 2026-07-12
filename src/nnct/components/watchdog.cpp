#include <nnct/components/watchdog.hpp>

namespace nnct::components {
    
Watchdog::Watchdog(uint16_t timeout) : TIMEOUT_(timeout) {}

bool Watchdog::update(uint16_t now) {
    if(kicked_) {
        kicked_ = false;
        timestamp_ = now;
        timeout_count_ = 0;
        return false;
    } else if((now - timestamp_) > TIMEOUT_) {
        timeout_count_++;
        timestamp_ = now;
        return true;
    }
    return false;
}

void Watchdog::kick() {
    kicked_ = true;
}

uint8_t Watchdog::count() const {
    return timeout_count_;
}
    
}
