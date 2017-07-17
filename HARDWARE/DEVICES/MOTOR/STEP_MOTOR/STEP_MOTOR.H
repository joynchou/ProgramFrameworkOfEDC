#ifndef _STEP_MOTOR_H_
#define _STEP_MOTOR_H_
#include "../../../BSP/config.h"
#define STEP_MOTOR_NUM 2
#define	STEP_MOTOR_1 0
#define	STEP_MOTOR_2 1

extern bit setStepMotorWithAngle(u8 motor, float angle, u8 speed);
extern bit setStepMotorWithRound(u8 motor, u16 round, u8 speed);
extern u8 getStepMotorState(u8 motor);
extern void close_StepMotor(u8 motor);
extern void open_StepMotor(u8 motor);
extern void stepMotor_Init();
extern bit freeStepMotor(u8 motor);
#endif
