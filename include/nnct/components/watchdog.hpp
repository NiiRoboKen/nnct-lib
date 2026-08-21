#pragma once

#include <cstdint>

namespace nnct::components {
    
class Watchdog {
    public:
        const uint16_t TIMEOUT_;

        explicit Watchdog(uint16_t timeout);
        ~Watchdog() = default;
        
        bool update(uint16_t now);
        void kick();
        uint8_t count() const;
        
    private:
        uint16_t       timestamp_       { 0 };
        uint8_t        timeout_count_   { 0 };
        bool           kicked_          { false };
};
    
}
