/************************************************************
* 组织名称：电子大赛小组
* 文件名称: PID.c
* 作者:     电子大赛小组
* 版本 :    1.0
* 日期:     10/06/17
* 描述: 	 
* 历史修改记录: 
* <作者> <时间> <版本 > <描述>
***********************************************************/
#include "PID.h"
#ifdef PID_ALG
#include <math.h>
#define  INTEGRAL_SEPARATE //使用积分分离法
static float Ki_temp,Kp_temp,Kd_temp; //保存pid三个参数的静态变量

//pid算法的静态结构体

static struct
{
  float setParameter;//设定角度值
  float actualParameter;//实际角度值
  float err;//偏差值
  float err_last;//上一次偏差值
  float Kp,Ki,Kd;//比例，积分，微分系数
  float integral;//积分值,位置式pid算法
  float output;  //实际输出因子
} pid;
/*************************************************
* 函数名称: bit setBoardWithAngleAndPID(unsigned char angle)
* 描述: 带pid算法的风摆角度调整函数
* 输入: 无
* 返回值: 执行一次角度调整后，执行成功返回1
*             其他说明:
* 调用此函数会进入循环，只有当误差第一次小于允许误差之后才会退出循环，
* 但是无法保证退出循环后风板是否能一直稳定。
* 如果想让风板一直保持稳定，必须不停的调用此函数。
*               注意：
* 请使用pid设置函数setPID_data（）来设置角度，之后在调用此函数。
***函数更新****
  作者  |  时间  |  说明
*周晨阳	   5/16		请使用pid设置函数setPID_data（）
									设置需要稳定的角度，不要向此函数传值*
									 无效
*************************************************/
bit PID(void)
{


  if(pid.setParameter >145.0f)
    {
      pid.setParameter =145.0f;
#ifdef MOTOR_DEBUG
      PrintString1("angle is over maximum adjusting\n");
#endif
    }
  if(pid.setParameter <35.0f)
    {
      pid.setParameter =35.0f;
#ifdef MOTOR_DEBUG
      PrintString1("angle is over miximum adjusting\n");
#endif
    }


  //  pid.setParameter      =           ANGLE; //不使用此函数去设置角度，此函数只稳定不设定。
  pid.actualParameter   =           getAngle(LAST_ANGLE);
  pid.err           =           pid.setParameter-pid.actualParameter;
#ifdef  INTEGRAL_SEPARATE //是否使用积分分离法
  if(abs(pid.err)<15.0f)//积分分离法，防止误差过大时积分累积过大造成震荡，同时减小比例和微分
    {
      pid.Ki        =        Ki_temp;
      pid.integral  +=       pid.err;
      pid.Kp        =        Kp_temp-0.7f;
      pid.Kd        =        Kd_temp-0.5f;
    }
  else//误差过大时去除积分项和累计误差 ，仅使用比例和微分 ，同时在原基础上加大微分的作用
    {
      pid.Ki        =        0;
      pid.integral  =        0;
      pid.Kd        =        Kd_temp+0.5f;
    }
#else
  pid.integral  +=       pid.err;
#endif
  pid.output        =    pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
  pid.err_last=pid.err;


  return 1;

}
/*************************************************
* 函数名称:float getPID_data(u8 DATA)
* 描述: 读取pid参数
* 输入: 见宏定义
* 返回值: 相应pid参数
* 其他说明: 若没有设置pid参数就直接读取，则结果未知。
*************************************************/

float getPID_data(u8 DATA)
{
  switch(DATA)
    {
      case SET_PARAMETER:
        return pid.setParameter;
        break;
      case ERR:
        return pid.err;
        break;
      case ERR_LAST:
        return pid.err_last;
        break;
      case KP:
        return pid.Kp;
        break;
      case KI:
        return pid.Ki;
        break;
      case KD:
        return pid.Kd;
        break;
      case INTEGRAL:
        return pid.integral;
        break;
      case OUTPUT:
        return pid.output;
        break;
      default:
        return 0;
        break;
    }
}
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
void setPID_data(u8 DATA,float value)
{
  switch(DATA)
    {
      case KP:
        pid.Kp=value;
        Kp_temp=value;
        break;
      case KI:
        pid.Ki=value;
        Ki_temp=value;
        break;
      case KD:
        pid.Kd=value;
        Kd_temp=value;
        break;
      case SET_PARAMETER:
        pid.setParameter=value;
      default:
        break;
    }
}
//PID算法初始化函数  .
/*************************************************
* 函数名称: void PID_config(float kp,float ki,float kd)
* 描述:   pid算法初始化函数，参数是三个，P,I,D,
*         此函数只能作为初始化，不能作为调整这三个值的接口
          如果需要调整这三个值，请使用setPID_data()函数
* 输入: float kp,float ki,float kd
* 输出: 无
* 返回值: 无
* 其他说明: 无
*************************************************/
void PID_config(float kp,float ki,float kd)//pid算法初始化函数，参数是三个，PID
{
  pid.setParameter=70;//若最终没有设置角度则默认70度
  pid.actualParameter=30;
  pid.err=0;
  pid.err_last=0;
  pid.output=0;
  pid.integral=0;
  pid.Kp=kp;
  pid.Ki=ki;
  pid.Kd=kd;
  Kp_temp=pid.Kp;
  Ki_temp=pid.Ki;
  Kd_temp=pid.Kd;
}
#endif

