#include "nnct/components/raw_pid.hpp"

namespace nnct {

RawPid::RawPid(double kp, double ki, double kd) : kp(kp), ki(ki), kd(kd) {}

void RawPid::setTarget(double target) {
  this->target = target;
}

double RawPid::update(double currentValue, double dt) {
  this->error = this->target - currentValue;
  this->integral += this->error * dt;
  this->derivative = (this->error - this->prevError) / dt;
  this->output = this->kp * this->error + this->ki * this->integral +
                 this->kd * this->derivative;
  this->prevError = this->error;

  return output;
}

} // namespace nnct
