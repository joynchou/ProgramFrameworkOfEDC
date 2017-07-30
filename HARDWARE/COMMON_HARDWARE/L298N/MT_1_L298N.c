/**********************************
* 文件名称：L298N模块控制
* 作者：夏志强
* 版本：1.0
* 日期：2017/07/08
* 描述：
* 1.0：编写了舵机的主要控制函数，包括：舵机开关控制、舵机角度读取与设定
* 详情见MT_1_L298N.H中的注释
************************************/

#include "MT_1_L298N.H"//头文件

void setCarForward(void)//前进
{
	IN1=1;
	IN2=0;
	IN3=0;
	IN4=1;
} 

void setCarBack(void)//后退
{
	IN1=0;
	IN2=1;
	IN3=1;
	IN4=0;
} 

void setCarStop(void)//停止
{
	IN1=0;
	IN2=0,
	IN3=0,
	IN4=0;
}

void setCarRightForward(void)//前进右转弯
{
	IN1=1;
	IN2=0;
	IN3=0;
	IN4=0;
}

void setCarRightBack(void)//后退右转弯
{
	IN1=0;
	IN2=1;
	IN3=0;
	IN4=0;
}	  

void setCarRightTurn(void)//原地右旋转
{
	IN1=1;
	IN2=0;
	IN3=1;
	IN4=0;	
}

void setCarLeftForward(void)//前进左转弯
{
	IN1=0;
	IN2=0;
	IN3=0;
	IN4=1;
}

void setCarLeftBack(void)//后退左转弯
{
	IN1=0;
	IN2=0;
	IN3=1;
	IN4=0;
} 

void setCarLeftTurn(void)//原地左旋转
{
	IN1=0;
	IN2=1;
	IN3=0;
	IN4=1;
}