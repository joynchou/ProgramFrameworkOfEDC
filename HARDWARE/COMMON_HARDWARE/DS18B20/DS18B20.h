#ifndef _DS18B20_H_
#define _DS18B20_H_
#include "../BSP/BSP.H"

float getDS18B20_Temperature(u8 which);
void DS18B20_Init(void);
#endif
