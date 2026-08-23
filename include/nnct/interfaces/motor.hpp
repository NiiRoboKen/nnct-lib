#pragma once

#include <Arduino.h>
#include <cstdint>

using pin_t     = uint8_t;
using ch_t      = uint8_t;
using dc_duty_t = int16_t;

namespace nnct::interfaces {

class Motor {
    public:
        Motor(pin_t DIR, pin_t PWM, ch_t motor_ch) : DIR_PIN(DIR), PWM_PIN(PWM), MOTOR_CH(motor_ch) {
            pinMode(DIR_PIN, OUTPUT);

            ledcSetup(MOTOR_CH, 20000, 8);

            ledcAttachPin(PWM_PIN, MOTOR_CH);

            ledcWrite(MOTOR_CH, 0);
        }
        void setDuty(dc_duty_t duty, int8_t sign = 1) {
            const int16_t power = static_cast<int16_t>(duty) * sign;

            digitalWrite(DIR_PIN, power > 0 ? HIGH : LOW);
            const uint8_t output = static_cast<uint8_t>(abs(power));
            ledcWrite(MOTOR_CH, output);
        }
        void stopMotor() { setDuty(0); }

    private:
        pin_t DIR_PIN;
        pin_t PWM_PIN;
        ch_t  MOTOR_CH;

        static constexpr uint32_t PWM_FREQ       = 20000;
        static constexpr uint8_t  PWM_RESOLUTION = 8;
};

} // namespace nnct::interfaces
