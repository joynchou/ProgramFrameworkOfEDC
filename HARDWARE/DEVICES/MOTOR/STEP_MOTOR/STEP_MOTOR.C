/************************************************************
* 组织名称：
* 文件名称: K:\单片机相关\电子大赛程序框架\HARDWARE\DEVICES\MOTOR\STEP_MOTOR\STEP_MOTOR.C
* 作者:  周晨阳
* 版本:  1.0  
* 日期:  2017/07/11
* 描述: 步进电机的驱动程序
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
* 
***********************************************************/

#include "STEP_MOTOR.H"
#include "../../../COMMON_HARDWARE/fixedPulser.h"

typedef struct
{
	u16 angle;//旋转角度
	u8 state;//电机状态
	u16 round;//旋转圈数
	u8 speed;//旋转速度

}StepMotor;
static  StepMotor g_stepMotor[STEP_MOTOR_NUM];

//************************************
// Method:    setStepMotorWithAngle
// FullName:  setStepMotorWithAngle
// Access:    public 
// Returns:   bit
// Qualifier: 设置步进电机的旋转角度
// Parameter: u8 motor
// Parameter: u16 angle
// Parameter: u8 speed
//************************************
bit setStepMotorWithAngle(u8 motor, u16 angle, u8 speed)
{
	setPulse(motor, speed, angle); //暂时不能使用
	return 1;
}
//************************************
// Method:    setStepMotorWithRound
// FullName:  setStepMotorWithRound
// Access:    public 
// Returns:   bit
// Qualifier: 设置步进电机的旋转圈数
// Parameter: u8 motor
// Parameter: u16 round
// Parameter: u8 speed
//************************************
bit setStepMotorWithRound(u8 motor, u16 round, u8 speed)
{
	while (round--)
	{
		setStepMotorWithAngle(motor, 360, speed);
	}
	return 1;
}
//************************************
// Method:    getStepMotorState
// FullName:  getStepMotorState
// Access:    public 
// Returns:   bit
// Qualifier: 读取步进电机当前的状态
// Parameter: u8 motor
//************************************
bit getStepMotorState(u8 motor)
{
	return g_stepMotor[motor].state;
}
//************************************
// Method:    close_StepMotor
// FullName:  close_StepMotor
// Access:    public 
// Returns:   void
// Qualifier: 关闭步进电机
// Parameter: u8 motor
//************************************
void close_StepMotor(u8 motor)
{
	closePulser(motor);
	g_stepMotor[motor].state = OFF;

}
//************************************
// Method:    open_StepMotor
// FullName:  open_StepMotor
// Access:    public 
// Returns:   void
// Qualifier: 打开步进电机
// Parameter: u8 motor
//************************************
void open_StepMotor(u8 motor)
{
	openPulser(motor);
	g_stepMotor[motor].state = ON;
}
