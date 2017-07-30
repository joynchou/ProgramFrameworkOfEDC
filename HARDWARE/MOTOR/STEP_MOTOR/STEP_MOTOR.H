#ifndef _STEP_MOTOR_H_
#define _STEP_MOTOR_H_

#include "../../COMMON_HARDWARE/common_HD.h"

#define CW 0	//转向，顺时针
#define CCW 1	//转向，逆时针
#define LOCK 0	//电机被锁，同时受到控制器的控制
#define FREE 1  //电机被解锁，同时不受控制器的控制
//如有需要可更改电机的名称
#define	STEP_MOTOR_1 0
#define	STEP_MOTOR_2 1
#define	STEP_MOTOR_3 2
#define	STEP_MOTOR_4 3
#define	STEP_MOTOR_5 4
#define	STEP_MOTOR_6 5
//步进电机的3中状态，运行，解锁（），锁住
enum StepMotorState
	{
	 RUNNING,UNLOCKED,LOCKED
};

typedef struct
{
	u8 speed;//旋转速度
	float DIV;//步进电机单步角度值 ，如1.8°
	u8 driverDiv;//步进电机驱动板上所选的角度细分值 2，4，8，16等
	u16 maxPeriod; 	//步进电机所能承受的最大频率
	u8 diversion;//电机转向
	float  bearingDia;//旋转传动齿轮或轴承的直径，单位cm
	enum StepMotorState state;//电机状态

}StepMotor;
//控制引脚定义
sbit StepMotor_1_DiversionControl =P2^7; 
sbit StepMotor_1_LockControl     = P2^6;
sbit StepMotor_2_DiversionControl =P2^5;
sbit StepMotor_2_LockControl     = P2^4;

extern void setStepMotorState(u8 motor, enum StepMotorState state);

extern bit setStepMotorWithPulse(u8 motor, u32 pulse, u16 speed);
extern bit setStepMotorWithDistance(u8 motor, float distance, u16 speed);//旋转指定长度脉冲发生器需要产生的脉冲数,;
extern bit setStepMotorWithAngle(u8 motor, float angle, u16 speed);
extern bit setStepMotorWithRound(u8 motor, u16 round, u16 speed);
extern u8 getStepMotorState(u8 motor);
extern void close_StepMotor(u8 motor);
extern void open_StepMotor(u8 motor);
extern void stepMotor_Init(u8 motor,float div,u8 driverDiv,u16 maxPeriod,float bearingDia);
extern bit freeStepMotor(u8 motor);
extern bit setStepMotorDiversion(u8 motor,bit diversion);

#endif
