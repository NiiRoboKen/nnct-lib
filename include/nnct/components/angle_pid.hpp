#pragma once

namespace nnct {

class AnglePid {
  public:
    AnglePid(double kp, double ki, double kd, double out_min, double out_max,
             double range, double INTEGRAL_MAX, double INTEGRAL_MIN);

    // dt[s]  msなら中で/1000して
    double update(long target_pos, long now_pos, double dt);
    double getError() const;
    void reset();

  private:
    double kp, ki, kd;
    double out_min, out_max;
    double range;
    double integral;
    double integral_max, integral_min;
    double control;
    double prev_error;

    long prev_now_pos;
    bool first;
};

} // namespace nnct