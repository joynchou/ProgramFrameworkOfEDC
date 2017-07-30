/*用于直流有刷电机的控制，此函数主要用于小车控制*/
#ifndef __MT_1_L298N_H__
#define __MT_1_L298N_H__

#include "../BSP/BSP.H"

/*
MT-1 L298N输出端连接方式
OUT1 -> Left Motor Positive electrode
OUT2 -> Left Motor Negative electrode
OUT3 -> Right Motor Positive electrode
OUT4 -> Right Motor Negative electrode
*/

sbit IN1=P0^0;
sbit IN2=P0^1;
sbit IN3=P0^2;
sbit IN4=P0^3;

extern void setCarForward(void);//前进
extern void setCarBack(void);//后退
extern void setCarStop(void);//停止
extern void setCarRightForward(void);//前进右转弯
extern void setCarRightBack(void);//后退右转弯
extern void setCarRightTurn(void);//原地右旋转
extern void setCarLeftForward(void);//前进左转弯
extern void setCarLeftBack(void);//后退左转弯
extern void setCarLeftTurn(void);//原地左旋转