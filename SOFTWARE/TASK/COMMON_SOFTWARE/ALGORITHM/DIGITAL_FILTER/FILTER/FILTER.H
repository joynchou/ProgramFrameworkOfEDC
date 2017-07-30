#ifndef _FILTER_H_
#define _FILTER_H_
#include "../../../../../../HARDWARE/devices.h"
extern u16 filter(u16 *ary, u8 num, u16 MaxValue, u16 MinValue);
extern double KalmanFilter(const double ResrcData,
double ProcessNiose_Q, double MeasureNoise_R, double InitialPrediction);

#endif