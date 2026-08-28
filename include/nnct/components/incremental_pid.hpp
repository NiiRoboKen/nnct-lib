#pragma once

namespace nnct {

class IncrementalPid {
  public:
    IncrementalPid(double kp, double ki, double kd, double out_min,
                   double out_max, double INTEGRAL_MAX, double INTEGRAL_MIN);

    double update(double target, double measurement, double dt);
    double getError() const;
    void reset();

  private:
    double kp, ki, kd;
    double out_min, out_max;
    double prev_error, prev_delta_error;
    double output;
    double error;
    double filt_deriv = 0.0; // メンバにする
    double integral_max, integral_min;
};

} // namespace nnct
