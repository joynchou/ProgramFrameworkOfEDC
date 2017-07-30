/************************************************************
* 组织名称：电子大赛小组
* 文件名称: PID.c
* 作者:     电子大赛小组
* 版本 :    1.0
* 日期:     10/06/17
* 描述:
* 历史修改记录:
*  1.新增了增量式PID算法，在结构体中加入了前两次的误差计算
*
* <作者> <时间> <版本 > <描述>
***********************************************************/
 #include <math.h>

#include "PID.h"
#include "PID.h"
#include <math.h>
#define POSITION 					 0// 位置式PID
#define INCREMENTAL				 1//增量式PID
#define INTEGRAL_SEPARATE  2//积分分离法PID
#define ANTI_WINDUP 			 3//抗积分饱和PID
#define TRAPEZOIDAL    		 4//梯形积分PID
//pid算法的静态结构体

typedef  struct
{
	float setParameter;//设定角度值
	float actualParameter;//实际角度值
	float err;//偏差值
	float err_last;//上一次偏差值
	float err_prev;//err_last上一次的偏差
	float Kp;
	float Ki;
	float Kd;//比例，积分，微分系数
	float integral;//积分值,位置式pid算法
	float output;  //实际输出因子
	float Ki_temp;//保存pid三个参数的静态变量
	float Kp_temp;//保存pid三个参数的静态变量
	float Kd_temp; //保存pid三个参数的静态变量
	float parameterUpperLimit;//参数上限
	float parameterInferiorLimit;//参数下限
	float err_max;//Be allowed max error
	u8 state;//pid工作状态
} pid_info;

static pid_info g_pid_n_info[PID_NUM];

/*************************************************
* 函数名称:PID_config
* 描述: pid初始化函数
* 输入:u8 PID_N, float kp, float ki, float kd
* 输出:
* 返回值:
* 其他说明:
*************************************************/
void PID_config(u8 PID_N, float kp, float ki, float kd)//pid算法初始化函数，参数是三个，PID
{
	g_pid_n_info[PID_N].err = 0;
	g_pid_n_info[PID_N].err_last = 0;
	g_pid_n_info[PID_N].err_prev = 0;
	g_pid_n_info[PID_N].output = 0;
	g_pid_n_info[PID_N].integral = 0;
	g_pid_n_info[PID_N].Kp = kp;
	g_pid_n_info[PID_N].Ki = ki;
	g_pid_n_info[PID_N].Kd = kd;
	g_pid_n_info[PID_N].Kp_temp = g_pid_n_info[PID_N].Kp;
	g_pid_n_info[PID_N].Ki_temp = g_pid_n_info[PID_N].Ki;
	g_pid_n_info[PID_N].Kd_temp = g_pid_n_info[PID_N].Kd;
}
//************************************
// Method:    openPID
// FullName:  openPID
// Access:    public 
// Returns:   void
// Qualifier: 打开pid
// Parameter: u8 PID_N
//************************************
void openPID(u8 PID_N)
{
	g_pid_n_info[PID_N].state = ON;
	//add the code here
}
//************************************
// Method:    closePID
// FullName:  closePID
// Access:    public 
// Returns:   void
// Qualifier:关闭pid
// Parameter: u8 PID_N
//************************************
void closePID(u8 PID_N)
{
	g_pid_n_info[PID_N].state = OFF;
	//add the code here

}

//************************************
// Method:    Position_PID
// FullName:  Position_PID
// Access:    public 
// Returns:   bit
// Qualifier: 设置好参数后使用此函数进行pid运算，之后使用get**函数获取计算后的值，需要先打开pid再使用此函数
// Parameter: u8 PID_N
//************************************
bit Position_PID(u8 PID_N)
{
	if (g_pid_n_info[PID_N].state)
	{
		g_pid_n_info[PID_N].err = g_pid_n_info[PID_N].setParameter - g_pid_n_info[PID_N].actualParameter;
		g_pid_n_info[PID_N].integral += g_pid_n_info[PID_N].err;//误差积累
		g_pid_n_info[PID_N].output  = g_pid_n_info[PID_N].Kp * g_pid_n_info[PID_N].err		  //kp * error//误差
																+ g_pid_n_info[PID_N].Ki * g_pid_n_info[PID_N].integral     //ki * error_integral//误差积分
																+ g_pid_n_info[PID_N].Kd * (g_pid_n_info[PID_N].err - g_pid_n_info[PID_N].err_last);//kd * error_differential//误差微分
		g_pid_n_info[PID_N].err_last = g_pid_n_info[PID_N].err;
		return 1;
	}
	return 0;
}



//************************************
// Method:    Integral_Separa_PID
// FullName:  Integral_Separa_PID
// Access:    public 
// Returns:   bit
// Qualifier: 积分分离PID设置好参数后使用此函数进行pid运算，之后使用get**函数获取计算后的值，需要先打开pid再使用此函数
// Parameter: u8 PID_N
//************************************
bit Integral_Separa_PID(u8 PID_N)
{
	unsigned int multiple;
	g_pid_n_info[PID_N].err = g_pid_n_info[PID_N].setParameter - g_pid_n_info[PID_N].actualParameter;
	if (g_pid_n_info[PID_N].state)
	{
		if(g_pid_n_info[PID_N].err > g_pid_n_info[PID_N].err_max)
		{
			multiple = 0;
		}
		else
		{
			multiple = 1;
			g_pid_n_info[PID_N].integral += g_pid_n_info[PID_N].err;//误差积累
		}
/*************PID算法部分*****************/
		g_pid_n_info[PID_N].output  = g_pid_n_info[PID_N].Kp * g_pid_n_info[PID_N].err		  //kp * error//误差
																+ g_pid_n_info[PID_N].Ki * g_pid_n_info[PID_N].integral * multiple    //ki * error_integral//误差积分
																+ g_pid_n_info[PID_N].Kd * (g_pid_n_info[PID_N].err - g_pid_n_info[PID_N].err_last);//kd * error_differential//误差微分
		g_pid_n_info[PID_N].err_last = g_pid_n_info[PID_N].err;
		return 1;
	}
	return 0;
}

//************************************
// Method:    Anti_Windup_PID
// FullName:  Anti_Windup_PID
// Access:    public 
// Returns:   bit
// Qualifier: 抗积分饱和PID设置好参数后使用此函数进行pid运算，之后使用get**函数获取计算后的值，需要先打开pid再使用此函数
// Parameter: u8 PID_N
//************************************
bit Anti_Windup_PID(u8 PID_N)
{
	unsigned int multiple;
	g_pid_n_info[PID_N].err = g_pid_n_info[PID_N].setParameter - g_pid_n_info[PID_N].actualParameter;
	if (g_pid_n_info[PID_N].state)
	{
		if(g_pid_n_info[PID_N].actualParameter > g_pid_n_info[PID_N].parameterUpperLimit)
		{
			if(abs(g_pid_n_info[PID_N].err) > g_pid_n_info[PID_N].err_max)
			{
				multiple = 0;
			}
			else
			{
				multiple = 1;
				if(g_pid_n_info[PID_N].err < 0)
				{
					g_pid_n_info[PID_N].integral += g_pid_n_info[PID_N].err;//误差积累
				}
			}
		}
		else if(g_pid_n_info[PID_N].actualParameter < g_pid_n_info[PID_N].parameterUpperLimit)
		{
			if(abs(g_pid_n_info[PID_N].err) > g_pid_n_info[PID_N].err_max)
			{
				multiple = 0;
			}
			else
			{
				multiple = 1;
				if(g_pid_n_info[PID_N].err > 0)
				{
					g_pid_n_info[PID_N].integral += g_pid_n_info[PID_N].err;//误差积累
				}
			}
		}
		else
		{
			if(abs(g_pid_n_info[PID_N].err) > g_pid_n_info[PID_N].err_max)
			{
				multiple = 0;
			}
			else
			{
				multiple = 1;
				g_pid_n_info[PID_N].integral += g_pid_n_info[PID_N].err;//误差积累
			}
		}
/*************PID算法部分*****************/
		g_pid_n_info[PID_N].output  = g_pid_n_info[PID_N].Kp * g_pid_n_info[PID_N].err		 //kp * error//误差
																+ g_pid_n_info[PID_N].Ki * g_pid_n_info[PID_N].integral * multiple    //ki * error_integral//误差积分
																+ g_pid_n_info[PID_N].Kd * (g_pid_n_info[PID_N].err - g_pid_n_info[PID_N].err_last);//kd * error_differential//误差微分
		g_pid_n_info[PID_N].err_last = g_pid_n_info[PID_N].err;
		return 1;
	}
	return 0;
}

//************************************
// Method:    Trapezoidal_Integral_PID
// FullName:  Trapezoidal_Integral_PID
// Access:    public 
// Returns:   bit
// Qualifier: 梯形积分PID设置好参数后使用此函数进行pid运算，之后使用get**函数获取计算后的值，需要先打开pid再使用此函数
// Parameter: u8 PID_N
//************************************
bit Trapezoidal_Integral_PID(u8 PID_N)
{
	unsigned int multiple;
	g_pid_n_info[PID_N].err = g_pid_n_info[PID_N].setParameter - g_pid_n_info[PID_N].actualParameter;
	if (g_pid_n_info[PID_N].state)
	{
		if(g_pid_n_info[PID_N].actualParameter > g_pid_n_info[PID_N].parameterUpperLimit)
		{
			if(abs(g_pid_n_info[PID_N].err) > g_pid_n_info[PID_N].err_max)
			{
				multiple = 0;
			}
			else
			{
				multiple = 1;
				if(g_pid_n_info[PID_N].err < 0)
				{
					g_pid_n_info[PID_N].integral += g_pid_n_info[PID_N].err;//误差积累
				}
			}
		}
		else if(g_pid_n_info[PID_N].actualParameter < g_pid_n_info[PID_N].parameterUpperLimit)
		{
			if(abs(g_pid_n_info[PID_N].err) > g_pid_n_info[PID_N].err_max)
			{
				multiple = 0;
			}
			else
			{
				multiple = 1;
				if(g_pid_n_info[PID_N].err > 0)
				{
					g_pid_n_info[PID_N].integral += g_pid_n_info[PID_N].err;//误差积累
				}
			}
		}
		else
		{
			if(abs(g_pid_n_info[PID_N].err) > g_pid_n_info[PID_N].err_max)
			{
				multiple = 0;
			}
			else
			{
				multiple = 1;
				g_pid_n_info[PID_N].integral += g_pid_n_info[PID_N].err;//误差积累
			}
		}
/*************PID算法部分*****************/
		g_pid_n_info[PID_N].output  = g_pid_n_info[PID_N].Kp * g_pid_n_info[PID_N].err		  //kp * error//误差
																+ g_pid_n_info[PID_N].Ki * g_pid_n_info[PID_N].integral * multiple / 2    //ki * error_integral//误差积分
																+ g_pid_n_info[PID_N].Kd * (g_pid_n_info[PID_N].err - g_pid_n_info[PID_N].err_last);//kd * error_differential//误差微分
		g_pid_n_info[PID_N].err_last = g_pid_n_info[PID_N].err;
		return 1;
	}	
	return 0;
}

//************************************
// Method:    Incremental_PID
// FullName:  Incremental_PID
// Access:    public 
// Returns:   void
// Qualifier: 增量式PID算法，设置好参数后使用此函数进行pid运算，之后使用get**函数获取计算后的值，需要先打开pid再使用此函数
// Parameter: u8 PID_N
//************************************
bit Incremental_PID(u8 PID_N)
{
	if(g_pid_n_info[PID_N].state)
	{
		g_pid_n_info[PID_N].err = g_pid_n_info[PID_N].setParameter - g_pid_n_info[PID_N].actualParameter;
		g_pid_n_info[PID_N].output = g_pid_n_info[PID_N].Kp * g_pid_n_info[PID_N].err// kp * err
																 - g_pid_n_info[PID_N].Ki * g_pid_n_info[PID_N].err_last// ki * err_last
																 + g_pid_n_info[PID_N].Kd * g_pid_n_info[PID_N].err_prev;//kd * err_prev
		g_pid_n_info[PID_N].err_prev = g_pid_n_info[PID_N].err_last;
		g_pid_n_info[PID_N].err_last = g_pid_n_info[PID_N].err;
		return 1;
	}
	return 0;
}

//************************************
// Method:    setParameterInferiorLimit
// FullName:  setParameterInferiorLimit
// Access:    public 
// Returns:   void
// Qualifier: 设置输入数值下限
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setParameterInferiorLimit(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].parameterInferiorLimit = value;
}

//************************************
// Method:    setParameterUpperLimit
// FullName:  setParameterUpperLimit
// Access:    public 
// Returns:   void
// Qualifier: 设置输入数值上限
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setParameterUpperLimit(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].parameterUpperLimit = value;

}

//************************************
// Method:    setActualParameter
// FullName:  setActualParameter
// Access:    public 
// Returns:   void
// Qualifier: 设置实际输入数值
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setActualParameter(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].actualParameter = value;

}

//************************************
// Method:    setKi
// FullName:  setKi
// Access:    public 
// Returns:   void
// Qualifier: 设置PID的Ki值
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setKi(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].Ki = value;
}

//************************************
// Method:    setKp
// FullName:  setKp
// Access:    public 
// Returns:   void
// Qualifier: 设置PID的Kp值
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setKp(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].Kp = value;
}

//************************************
// Method:    setKd
// FullName:  setKd
// Access:    public 
// Returns:   void
// Qualifier: 设置PID的Kd值
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setKd(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].Kd = value;
}

//************************************
// Method:    setParameter
// FullName:  setParameter
// Access:    public 
// Returns:   void
// Qualifier: 设置PID的目标数值
// Parameter: u8 PID_N
// Parameter: float value
//************************************
void setParameter(u8 PID_N, float value)
{
	g_pid_n_info[PID_N].setParameter = value;
}


//************************************
// Method:    getParameter
// FullName:  getParameter
// Access:    public 
// Returns:   float
// Qualifier: 读取PID的目标数值
// Parameter: u8 PID_N
//************************************
float	getParameter(u8 PID_N)
{
	return  g_pid_n_info[PID_N].setParameter;
}

//************************************
// Method:    getErr
// FullName:  getErr
// Access:    public 
// Returns:   float
// Qualifier: 读取PID的这一次误差值
// Parameter: u8 PID_N
//************************************
float getErr(u8 PID_N)
{
	return  g_pid_n_info[PID_N].err;
}

//************************************
// Method:    getErrLast
// FullName:  getErrLast
// Access:    public 
// Returns:   float
// Qualifier: 读取PID的上一次误差值
// Parameter: u8 PID_N
//************************************
float getErrLast(u8 PID_N)
{
	return  g_pid_n_info[PID_N].err_last;
}
//************************************
// Method:    getKp
// FullName:  getKp
// Access:    public 
// Returns:   float
// Qualifier: 读取PID的Kp值
// Parameter: u8 PID_N
//************************************
float getKp(u8 PID_N)
{
	return  g_pid_n_info[PID_N].Kp;
}

//************************************
// Method:    getKi
// FullName:  getKi
// Access:    public 
// Returns:   float
// Qualifier: 读取PID的Ki值
// Parameter: u8 PID_N
//************************************
float getKi(u8 PID_N)
{
	return  g_pid_n_info[PID_N].Ki;
}

//************************************
// Method:    getKd
// FullName:  getKd
// Access:    public 
// Returns:   float
// Qualifier: 读取pid的Kd参数值
// Parameter: u8 PID_N
//************************************
float getKd(u8 PID_N)
{
	return  g_pid_n_info[PID_N].Kd;
}

//************************************
// Method:    getOutput
// FullName:  getOutput
// Access:    public 
// Returns:   float
// Qualifier: 读取pid输出值
// Parameter: u8 PID_N
//************************************
float getOutput(u8 PID_N)
{
	return  g_pid_n_info[PID_N].output;
}

//************************************
// Method:    getIntegral
// FullName:  getIntegral
// Access:    public 
// Returns:   float
// Qualifier: 读取pid积分值
// Parameter: u8 PID_N
//************************************
float getIntegral(u8 PID_N)
{
	return  g_pid_n_info[PID_N].integral;
}

//************************************
// Method:    setMaxError
// FullName:  setMaxError
// Access:    public 
// Returns:   float
// Qualifier: set max error of pid calculate can be awlloed
// Parameter: u8 PID_N
//************************************
void setMaxError(u8 PID_N,float err_max)
{
	g_pid_n_info[PID_N].err_max = err_max;
}

//************************************
// Method:    PID
// FullName:  PID
// Access:    public 
// Returns:   bit
// Qualifier: 设置好参数后使用此函数进行pid运算，之后使用get**函数获取计算后的值，需要先打开pid再使用此函数
//            仅提供位置类PID算法
// Parameter: u8 PID_N
//************************************
void PosClassPID(u8 PID_N,u8 PID_MODE)
{
	if(g_pid_n_info[PID_N].state)
	{
		switch(PID_MODE)
		{
			case POSITION:
				Position_PID(PID_N);
				break;
			case INTEGRAL_SEPARATE:
				Integral_Separa_PID(PID_N);
				break;
			case ANTI_WINDUP:
				Anti_Windup_PID(PID_N);
				break;
			case TRAPEZOIDAL:
				Trapezoidal_Integral_PID(PID_N);
				break;
		}
	}
}

//************************************
// Method:    IncClassPID
// FullName:  IncClassPID
// Access:    public 
// Returns:   bit
// Qualifier: 设置好参数后使用此函数进行pid运算，之后使用get**函数获取计算后的值，需要先打开pid再使用此函数
//            仅提供增量类PID算法
// Parameter: u8 PID_N
//************************************
void IncClassPID(u8 PID_N,u8 PID_MODE)
{
	if(g_pid_n_info[PID_N].state)
	{
		switch(PID_MODE)
		{
			case INCREMENTAL:
				Incremental_PID(PID_N);
				break;
		}
	}
}