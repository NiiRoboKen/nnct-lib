#pragma once

using pin_t = uint8_t;
namespace nnct::interfaces {

class LimitSwitch {
    public:
        LimitSwitch(pin_t pin) : pin(pin) { pinMode(pin, INPUT); }
        bool active() { return digitalRead(pin); }

    private:
        pin_t pin;
};
} // namespace nnct::interfaces
