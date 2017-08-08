#ifndef _PHSENSOR_H_
#define _PHSENSOR_H_
#include "../../COMMON_HARDWARE/common_HD.h"
#define PH_NUM 2
#define PH_1 0
#define PH_2 1

void PH_config(u8 PH_N, float k, float b);
void setPHCoefficient(u8 PH_N,float k,float b);
float getPH_Value(u8 PH_N,bit whichPHvalue);
#endif