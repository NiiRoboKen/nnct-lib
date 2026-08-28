#pragma once

namespace nnct {

class Pid {
  public:
    Pid(double kp, double ki, double kd, double out_min, double out_max,
        double integral_min, double integral_max);

    // dt[s]
    double update(double target_pos, double now_pos, double dt);
    double getError() const;
    void reset(double now_pos = 0.0);

  private:
    double kp, ki, kd;
    double out_min, out_max;

    double integral;
    double integral_max, integral_min;
    double control;

    double prev_meas;
    bool first;

    double error;
};

} // namespace nnct