#pragma once

namespace nnct {

class RawPid {
  public:
    RawPid(double kp, double ki, double kd);
    void setTarget(double target);
    // dt[s]
    double update(double currentValue, double dt);

  private:
    double kp, ki, kd;      // ゲイン
    double target{0};       // 目標値
    double currentValue{0}; // 実際の値
    double error{0};        // 偏差
    double prevError{0};    // 前回の偏差
    double integral{0};     // 積分項
    double derivative{0};   // 微分項
    double output{0};       // 出力
};

} // namespace nnct
