/*
" Copyright 2020 CHLee "
*/
#include "pid.h"

double PIDController::calculate(double target, double actual) {
  double error = target - actual;

  // PID
  double p_out = _kp * error;
  double i_out = _ki * integral(error);
  double d_out = _kd * derivate(error);

  _b_error = error;

  return p_out + i_out + d_out;
}

double PIDController::integral(double err) {
  // return err * _dt;
  _integral += err;

  // clipping - max,min 이상 안넘어가게하는 것.
  if (_integral >= _clipping) _integral = _clipping;
  else if (_integral <= (_clipping * -1)) _integral = -1 * _clipping;

  return _integral;
}

double PIDController::derivate(double err) {
  // return (err - _b_error) / _dt;
  return err - _b_error;
}
