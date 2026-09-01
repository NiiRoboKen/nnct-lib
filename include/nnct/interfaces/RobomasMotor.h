#pragma once

#include <Arduino.h>
#include <esp_can.hpp>

using robomas_id_t = uint8_t;

namespace nnct::interfaces {

class RobomasMotor {
    public:
        RobomasMotor(robomas_id_t motorId, int16_t maxCurrent = 5000) : motorId_(motorId), maxCurrent_(maxCurrent) {}

        int16_t angle() const { return angle_; }
        int16_t rpm() const { return rpm_; }
        int16_t current() const { return current_; }
        uint8_t temperature() const { return temperature_; }

        void setCurrent(int16_t current) { targetCurrent_ = constrain(current, -maxCurrent_, maxCurrent_); }

        void run(int16_t duty, int8_t sign = 1) {
            duty                  = constrain(duty, -255, 255);
            const int32_t current = static_cast<int32_t>(duty) * sign * maxCurrent_ / 255;
            setCurrent(static_cast<int16_t>(current));
        }

        void stop() { targetCurrent_ = 0; }

    private:
        friend class RobomasCAN;

        robomas_id_t motorId_;
        int16_t      maxCurrent_;
        int16_t      targetCurrent_ = 0;

        int16_t angle_       = 0;
        int16_t rpm_         = 0;
        int16_t current_     = 0;
        uint8_t temperature_ = 0;
};

class RobomasCAN {
    public:
        RobomasCAN(int rxPin, int txPin) : rxPin_(rxPin), txPin_(txPin), can_() {}

        bool begin() {
            if (!can_.begin(1000000, txPin_, rxPin_)) {
                return false;
            }
            instance_ = this;
            can_.onReceive(canCallBack);
            return true;
        }

        bool send(RobomasMotor* m1 = nullptr, RobomasMotor* m2 = nullptr, RobomasMotor* m3 = nullptr,
                  RobomasMotor* m4 = nullptr) {
            motors_[0] = m1;
            motors_[1] = m2;
            motors_[2] = m3;
            motors_[3] = m4;

            uint8_t payload[8] = {0};

            for (int i = 0; i < 4; ++i) {
                if (motors_[i] == nullptr) continue;
                const int16_t current = motors_[i]->targetCurrent_;
                payload[i * 2]        = static_cast<uint8_t>((current >> 8) & 0xFF);
                payload[i * 2 + 1]    = static_cast<uint8_t>(current & 0xFF);
            }
            return can_.sendStandard(0x200, payload, 8);
        }

    private:
        uint8_t rxPin_;
        uint8_t txPin_;

        RobomasMotor*      motors_[4] = {};
        CanDriver          can_;
        static RobomasCAN* instance_;

        static void canCallBack(twai_message_t msg) {
            if (instance_ == nullptr) {
                return;
            }
            const int motorIndex = static_cast<int>(msg.identifier) - 0x201;

            if (motorIndex < 0 || motorIndex >= 4) {
                return;
            }

            if (instance_->motors_[motorIndex] == nullptr) {
                return;
            }
            if (msg.data_length_code < 7) {
                return;
            }

            RobomasMotor&  motor = *instance_->motors_[motorIndex];
            const uint8_t* data  = msg.data;

            motor.angle_       = readInt16BE(data, 0);
            motor.rpm_         = readInt16BE(data, 2);
            motor.current_     = readInt16BE(data, 4);
            motor.temperature_ = data[6];
        }

        static int16_t readInt16BE(const uint8_t* data, uint8_t index) {
            return static_cast<int16_t>((static_cast<uint16_t>(data[index]) << 8) | static_cast<uint16_t>(data[index + 1]));
        }
};

RobomasCAN* RobomasCAN::instance_ = nullptr;

} // namespace nnct::interfaces