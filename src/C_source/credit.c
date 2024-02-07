#include "Calc.h"

double per_month_ann(double sum, double precent, int time) {
  double res = 0;
  res =
      sum * ((precent * pow(1 + precent, time)) / (pow(1 + precent, time) - 1));
  return res;
}

double per_month_diff(double sum, double precent, int time, double *total) {
  double res = 0;
  double per_month = sum / time;
  for (int i = 0; i < time; i++) {
    res = per_month + (sum - per_month * i) * precent;
    *total += res;
  }
  return res;
}