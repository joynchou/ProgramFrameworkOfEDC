#ifndef _USER_H_
#define _USER_H_
#include "config.h"

//debug模式，注释此行代码则退出总debug
#define DEBUG
#ifdef DEBUG
//#define MOTOR_DEBUG
//#define DISPLAY_DEBUG
//#define BUTTON_DEBUG
//#define PID_DEBUG
#endif
//初始化常量宏定义
#define UART1_BANDRATE 115200ul
#define PWM_PERIOD 5000
#define ANGLE_PIN ADC_P10//adc io口
#define ANGLE_Speed ADC_90T//adc转换速度

void loop(void);
void setup(void);
void setAngle(void);
void sendScopeData(void);    
void uiDraw(void);
void UART1_init(unsigned long BandRate);

#endif
