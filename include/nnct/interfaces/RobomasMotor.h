#pragma once

#include <Arduino.h>
#include <CAN.h>

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

        void setDuty(int16_t duty, int8_t sign = 1) {
            duty                  = constrain(duty, -255, 255);
            const int32_t current = static_cast<int32_t>(duty) * sign * maxCurrent_ / 255;
            setCurrent(static_cast<int16_t>(current));
        }

        void Stop() { targetCurrent_ = 0; }

    private:
        friend class RobomasCAN;

        uint8_t motorId_;
        int16_t maxCurrent_;
        int16_t targetCurrent_ = 0;

        int16_t angle_       = 0;
        int16_t rpm_         = 0;
        int16_t current_     = 0;
        uint8_t temperature_ = 0;
};

class RobomasCAN {
    public:
        RobomasCAN(int rxPin, int txPin) : rxPin_(rxPin), txPin_(txPin) {}

        bool begin() {
            CAN.setPins(rxPin_, txPin_);

            if (!CAN.begin(1000000)) {
                Serial.println("can failed");
                return false;
            }

            instance_ = this;
            CAN.onReceive(onReceive);

            volatile uint32_t* pREG_IER = (volatile uint32_t*)0x3ff6b010;
            *pREG_IER &= ~(uint8_t)0x10;

            return true;
        }

        bool send(RobomasMotor* m1 = nullptr, RobomasMotor* m2 = nullptr, RobomasMotor* m3 = nullptr,
                  RobomasMotor* m4 = nullptr) {
            motors_[0] = m1;
            motors_[1] = m2;
            motors_[2] = m3;
            motors_[3] = m4;

            CAN.beginPacket(0x200);

            for (uint8_t i = 0; i < 4; ++i) {
                const int16_t current = motors_[i] ? motors_[i]->targetCurrent_ : 0;
                CAN.write(static_cast<uint8_t>(current >> 8));
                CAN.write(static_cast<uint8_t>(current & 0xff));
            }

            return CAN.endPacket() == 1;
        }

    private:
        int rxPin_;
        int txPin_;

        RobomasMotor*      motors_[4] = {};
        static RobomasCAN* instance_;

        static void onReceive(int packetSize) {
            if (instance_ == nullptr || packetSize < 7) {
                return;
            }

            const int id         = CAN.packetId();
            const int motorIndex = id - 0x201;

            // 範囲外のデータは読み捨てる
            if (motorIndex < 0 || motorIndex >= 4 || instance_->motors_[motorIndex] == nullptr) {
                while (CAN.available()) {
                    CAN.read();
                }
                return;
            }

            uint8_t   data[8] = {};
            const int length  = min(packetSize, 8);

            for (int i = 0; i < length; ++i) {
                data[i] = static_cast<uint8_t>(CAN.read());
            }

            while (CAN.available()) {
                CAN.read();
            }

            RobomasMotor& motor = *instance_->motors_[motorIndex];

            motor.angle_       = readInt16(data, 0);
            motor.rpm_         = readInt16(data, 2);
            motor.current_     = readInt16(data, 4);
            motor.temperature_ = data[6];
        }

        static int16_t readInt16(const uint8_t* data, uint8_t index) {
            return static_cast<int16_t>((static_cast<uint16_t>(data[index]) << 8) | data[index + 1]);
        }
};

} // namespace nnct::interfaces