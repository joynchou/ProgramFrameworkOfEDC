/************************************************************
* 组织名称： (C), 1988-1999, Tech. Co., Ltd.
* 文件名称: MOTOR.C
* 作者:  周晨阳
* 版本:  1.3
* 日期:  17/4/29
* 描述:  和电机有关的控制函数都在这里，还有pid算法控制也在其中
* 主要函数及其功能 : // 主要函数及其功能
* 1. -------
* 历史修改记录: // 历史修改记录
* <作者> <时间> <版本 > <描述>
* 周晨阳 17/6/216 1.0 创建此描述
***********************************************************/
#include "MOTOR.h"
#ifdef DC_MOTOR
#include "../ANGLE/ANGLE.h"
#include <math.h>
static bit MotorState=OFF;//电机状态标志位，OFF 为关闭，ON 为开启
//pid算法的静态结构体

bit getMotorState(Motor *motor)
{
	 return motor->MotorState;
	
}
void stopMotor(u8 motor)
{
  setMotorSpeed(LEFT_MOTOR,0.01f);
  setMotorSpeed(RIGHT_MOTOR,0.01f);
  MotorState=OFF;


}
void startMotor(u8 motor)
{
   OPEN_PWM();
	 MotorState=ON;
}
/*************************************************
* 函数名称: void setMotorSpeed(bit motor,float speed)
* 描述: 设置电机速度函数
* 输入: motor：电机，头文件中定义
				speed：速度 0~1   
* 其他说明: 
*若要关闭电机请使用电机关闭函数，此函数无法关闭电机
*************************************************/                                                          
void setMotorSpeed(bit motor,float speed)
{
	
		if(speed>0.95f)
			{
		   speed=0.95f;
	    }
		if(speed<0.05f)
		{
			
			speed=0.05f;
		}
		
		if(motor)
		{
		//	PWM_duty(PWM_2,speed*0.65f);//根据不同电机乘于不同的增益
			PWM_duty(PWM_2,speed);//根据不同电机乘于不同的增益
		}
		else
		{
		//	PWM_duty(PWM_4,speed*0.63f);
			PWM_duty(PWM_4,speed);
		}
}
#endif


