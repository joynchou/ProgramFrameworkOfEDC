#include "STEP_MOTOR.H"
#include "../../../COMMON_HARDWARE/fixedPulser.h"

#define STEP_MOTOR_NUM 2
#define	STEP_MOTOR_1 0
#define	STEP_MOTOR_2 1
typedef struct
{
	u16 angle;//旋转角度
	u8 state;//电机状态
	u16 round;//旋转圈数
	u8 speed;//旋转速度

}StepMotor;
static  StepMotor g_stepMotor[STEP_MOTOR_NUM];

bit setStepMotorWithAngle(u8 motor, u16 angle, u8 speed)
{
//	setPulse(motor, speed, angle);
	return 1;
}
bit setStepMotorWithRound(u8 motor, u16 round, u8 speed)
{
	while (round--)
	{
		setStepMotorWithAngle(motor, 360, speed);
	}
	return 1;
}
bit getStepMotorState(u8 motor)
{
	return g_stepMotor[motor].state;
}
void close_StepMotor(u8 motor)
{
	closePulser(motor);
	g_stepMotor[motor].state = OFF;

}
void open_StepMotor(u8 motor)
{
	openPulser(motor);
	g_stepMotor[motor].state = ON;
}
