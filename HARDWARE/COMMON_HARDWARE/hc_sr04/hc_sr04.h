#ifndef _HC_SR04_H_
#define _HC_SR04_H_
#include "../BSP/BSP.H"
#define HC_SR04_1  0
#define US_016_1   1

#define Trig P33
#define Echo P32
#define RISING_EDGE 1
#define FALLING_EDGE 0

void ultrasonicInit(void);
void open_Ultrasonic(u8 num);
void close_Ultrasonic(u8 num);
u8 getUltrasonicState(u8 num);
void setTimerValue(u8 num, u16 value);
void setDistance(u8 num, float value);
u16 getTimerValue(u8 num);
void updateDistance(u8 num);
double getdistance(u8 num);


#endif
