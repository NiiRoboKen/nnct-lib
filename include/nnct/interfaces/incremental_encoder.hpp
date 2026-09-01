#pragma once

#include <ESP32Encoder.h>
#include <cstdint>

using pin_t = uint8_t;

namespace nnct::interfaces {

class IncrementalEncoder {
    public:
        IncrementalEncoder(pin_t A_pin, pin_t B_pin) : A_pin(A_pin), B_pin(B_pin) { enc.attachFullQuad(A_pin, B_pin); }

        int64_t getCount() { return enc.getCount(); }
        void    setCount(int64_t count) { enc.setCount(count); }

        inline void clear() { setCount(0); }

        pin_t        A_pin, B_pin;
        ESP32Encoder enc;
};

} // namespace nnct::interfaces