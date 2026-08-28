#include "nnct/components/pid.hpp"

namespace {
double restrict(double in, double min, double max) {
  if (in < min) {
    return min;
  } else if (in > max) {
    return max;
  } else {
    return in;
  }
}
} // namespace

namespace nnct {

Pid::Pid(double kp, double ki, double kd, double out_min, double out_max,
         double integral_min, double integral_max)
    : kp(kp), ki(ki), kd(kd), out_min(out_min), out_max(out_max), integral(0.0),
      integral_min(integral_min), integral_max(integral_max), control(0.0),
      prev_meas(0.0), first(true) {}

double Pid::update(double target_pos, double now_pos, double dt) {
  if (dt <= 0.0)
    return control;

  error = target_pos - now_pos;

  integral += error * dt;
  integral = restrict(integral, integral_min, integral_max);

  double derivative = 0.0;
  if (!first) {
    const double dMeas = (now_pos - prev_meas) / dt;
    derivative = -dMeas;
  } else {
    first = false;
  }
  prev_meas = now_pos;

  control = kp * error + ki * integral + kd * derivative;
  control = restrict(control, out_min, out_max);
  return control;
}

double Pid::getError() const {
  return error;
}

void Pid::reset(double now_pos) {
  integral = 0.0;
  control = 0.0;
  prev_meas = now_pos;
  first = true;
}

} // namespace nnct
