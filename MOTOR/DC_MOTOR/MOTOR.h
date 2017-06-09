/************************************************************
* 组织名称：电子大赛小组
* 文件名称: MOTOR.H
* 作者:     周晨阳
* 版本 :    1.0
* 日期:
* 描述: 	 电机相关头文件
* 历史修改记录: // 历史修改记录
* <作者> <时间> <版本 > <描述>
***********************************************************/
#ifndef _MOTOR_H_
#define _MOTOR_H_
#include "../USER/STC15_PWM.H"                             /*********对外参数和接口函数***********/
/************************************
硬件PWMio引脚（没有pwm1）
PWM_N| io  | 第二组
PWM2 :P3.7 -> P2.7
PWM3 :P2.1 -> P4.5
PWM4 :P2.2 -> P4.4
PWM5 :P2.3 -> P4.2
PWM6 :P1.6 -> P0.7
PWM7 :P1.7 -> P0.6
************************************/
void stopMotor(void);
void startMotor(void);
bit getMotorState();
/*************************************************
* 函数名称:double getPID_data(u8 DATA)
* 描述: 读取pid参数      
* 输入: 见宏定义      
* 输出: 
* 返回值: 相应pid参数
* 其他说明: 若没有设置pid参数就直接读取，则结果未知。
*************************************************/
float getPID_data(u8 DATA);



/*************************************************
* 函数名称:void setPID_data(u8 DATA,float value)
* 描述:  设置pid三个参数的函数，一次性只能设置一个参数
*        可作为调整PID参数的接口。
* 输入: u8 DATA ：需要更改的参数名称，为宏定义,
        float value：参数值
* 输出: 无
* 返回值: 无
* 其他说明: 无
*************************************************/
void setPID_data(u8 DATA,float value);



/*************************************************
* 函数名称: void setMotorSpeed(bit motor,float speed)
* 描述: 设置电机速度函数
* 输入: motor：电机，头文件中定义
				speed：速度 0~1   0时电机停转
* 其他说明: 
*************************************************/
void setMotorSpeed(bit motor,float speed);



/*************************************************
* 函数名称: void PID_config(float kp,float ki,float kd)
*                    描述:
*************************************************
* pid算法初始化函数，参数是三个，P,I,D,
* 此函数只能作为初始化，不能作为调整这三个值的接口
* 如果需要调整这三个值，请使用setPID_data()函数
* ***********************************************
* 输入: float kp,float ki,float kd
* 输出:     无
* 返回值:   无
* 其他说明: 无
*************************************************/
void PID_config(float kp,float ki,float kd);//pid算法初始化函数，参数是三个，PID



/*************************************************
* 函数名称: bit setBoardWithAngleAndPID(float angle)
* 描述: 带pid算法的风摆角度调整函数
* 输入: 无
* 返回值: 执行一次角度调整后，返回1
* 其他说明: 若需一直调整需将此函数加入循环
*************************************************/
bit setBoardWithAngleAndPID(void);//风板角度设置函数,闭环控制，包含pid

#define LEFT_MOTOR   1
#define RIGHT_MOTOR  0
#define STOP         0
#define SET_ANGLE    0
#define ERR          1
#define ERR_LAST     2
#define KP 					 3
#define KI 					 4
#define KD           5
#define INTEGRAL     6
#define OUTPUT       7


#endif
