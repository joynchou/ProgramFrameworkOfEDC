/************************************************************
* 文件名称: timer.c
* 作者: 周晨阳
* 版本: 1.0
* 创建日期: 2017/4/29
* 描述: 定义单片机片上定时器的使用、分配
* 主要函数及其功能 :
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
* 周晨阳 2017/4/29 添加了此文件说明注释
* 周晨阳 2017/7/27 1.2 重新设计了定时器的使用，现在的定时器分配如下：
* Timer 0 OS
* Timer 1 串口1
* Timer 2 pulser1
* Timer 3 pulser2
* Timer 4 用户定时器 //暂时还无法使用
* 由于os和串口这两个定时器必须使用，所以先暂时这样定
* 另外，经测试发现除了timer4 的高速脉冲无法使用其他的定时器都可以输出高速脉冲
* 但是要注意使用的时候由于timer2的高速脉冲引脚是串口1的 rx引脚，所以在下载的时候请尽量让此引脚不要接线
* 否则可能会下载失败
***********************************************************/
//////////////////////定时器典型应用/////////////////////////////////////// 
/*


				setTimeout(Timer1,5000); //设置定时器定时长度 ,5秒
				while(1)
				{
					if(isExpiredTimer(Timer1))   //如果达到定时时间
					{
						 stopTimer(Timer1);//达到定时时间后一定要关闭定时器，否则会无法重复使用定时器
						//定时时间到，你的代码写在这
					}
					else//如果未达到定时时间或定时器未启动
					{


							restartTimer(Timer1);


					}
				}
*/
///////////////////////////////////////////////////////////////		 
#include	"timer.h"
#include "USART1.h"
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
enum
{
	ACTIVE, EXPIRED, STOPPED
}
Timer1_state = STOPPED,
Timer2_state = STOPPED;

static u16 Timer1_temp = 0;
static u16 Timer2_temp = 0;
static u16 micros = 0;//绝对时间获取变量
static u16 millis = 0;//绝对时间获取变量
static u8 seconds = 0;
static u8 minutes = 0;
static u8 hours = 0;
static u8 days = 0;




struct TimerInfo
{
	u16 Timeout;
	u16 Hz;
}
timer1_struct = { 0,0 },
timer2_struct = { 0,0 };
//************************************
// Method:    timerInit
// FullName:  timerInit
// Access:    public 
// Returns:   void
// Qualifier: 定时器初始化函数，使用用户定时器和绝对时间获取函数之前请再setup中调用此函数完成初始化
//************************************
void timerInit()
{
	TIM_InitTypeDef		USER_Timer;	//用户自定义定时器使用
	TIM_InitTypeDef		Pulser_1_Timer;	//
	TIM_InitTypeDef   Pulser_2_Timer;
	u8 Error_Code = 0;
	//	
	//  	//用户自定义定时器		
	USER_Timer.TIM_Mode = TIM_16BitAutoReload;	//指定工作模式,16位自动重装模式    TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,\\																																																								TIM_16BitAutoReloadNoMask
	USER_Timer.TIM_Polity = PolityLow;			//指定中断优先级, PolityHigh,PolityLow
	USER_Timer.TIM_Interrupt = DISABLE;				//中断是否允许,   ENABLE或DISABLE
	USER_Timer.TIM_ClkSource = TIM_CLOCK_1T;	//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	USER_Timer.TIM_ClkOut = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	USER_Timer.TIM_Run = DISABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
	USER_Timer.TIM_Value = 65536UL - (MAIN_Fosc / 1000);		//初值,1000us
  //脉冲发生器1的定时器
	Pulser_1_Timer.TIM_Mode = TIM_16BitAutoReload;	//指定工作模式,16位自动重装模式   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,\\ 																																																									TIM_16BitAutoReloadNoMask
	Pulser_1_Timer.TIM_Polity = PolityHigh;			//指定中断优先级, PolityHigh,PolityLow
	Pulser_1_Timer.TIM_Interrupt = ENABLE;				//中断是否允许,   ENABLE或DISABLE
	Pulser_1_Timer.TIM_ClkSource = TIM_CLOCK_12T;	//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	//Pulser_1_Timer.TIM_ClkOut = ENABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	Pulser_1_Timer.TIM_Run = DISABLE;				//是否初始化后启动定时器, ENABLE或DISABLE

	//脉冲发生器2的定时器
	Pulser_2_Timer.TIM_Mode = TIM_16BitAutoReload;	//指定工作模式,16位自动重装模式   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload												  																																																									//TIM_16BitAutoReloadNoMask
	Pulser_2_Timer.TIM_Polity = PolityHigh;			//指定中断优先级, PolityHigh,PolityLow
	Pulser_2_Timer.TIM_Interrupt = ENABLE;				//中断是否允许,   ENABLE或DISABLE
	Pulser_2_Timer.TIM_ClkSource = TIM_CLOCK_12T;	//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	//Pulser_2_Timer.TIM_ClkOut = ENABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	Pulser_2_Timer.TIM_Run = DISABLE;				//是否初始化后启动定时器, ENABLE或DISABLE

	Timer_Inilize(Timer2, &Pulser_1_Timer);
	Timer_Inilize(Timer3, &Pulser_2_Timer);

	//  	//用户自定义定时器		
	//			if (!(Error_Code = Timer_Inilize(Timer4, &USER_Timer)))//==0
	//			{
	//				//PrintString1("USER_Timer initializing succeed \r\n");
	//			}
	//			else if (Error_Code) //==1
	//			{
	//				//PrintString1("USER_Timer initializing failed \r\n");
	//			}
	//			else
	//			{
	//				//PrintString1("USER_Timer initializing failed \r\n");
	//			}

	//  //脉冲发生器1的定时器
	//	if (!(Error_Code = Timer_Inilize(Timer1, &TIM_InitStructure)))//==0
	//	{
	//		//PrintString1("Pulser_1_Timer initializing succeed \r\n" );
	//	}
	//	else if (Error_Code) //==1
	//	{
	//		//PrintString1("Pulser_1_Timer initializing failed \r\n");
	//	}
	//	else
	//	{
	//		//PrintString1("Pulser_1_Timer initializing failed \r\n");
	//	}
	//	//脉冲发生器2的定时器
	//	if (!(Error_Code = Timer_Inilize(Timer3, &Pulser_2_Timer)))//==0
	//	{
	//		//PrintString1("Pulser_2_Timer initializing succeed \r\n");
	//	}
	//	else if (Error_Code) //==1
	//	{
	//		//PrintString1("Pulser_2_Timer initializing failed \r\n");
	//	}
	//	else
	//	{
	//		//PrintString1("Pulser_2_Timer initializing failed \r\n");
	//	}



}

//
//************************************
// Method:    setTimeout
// FullName:  setTimeout
// Access:    public 
// Returns:   void
// Qualifier: 设置定时器的定时时间
// Parameter: u8 whichTimer：哪一个定时器
// Parameter: u16 time：需要定时的时间，单位ms
//************************************
void setTimeout(u8 whichTimer, u16 time)
{
	if (!(Timer1_state == ACTIVE || Timer2_state == ACTIVE))
	{
		switch (whichTimer)
		{

		case Timer1:
		{
			timer1_struct.Timeout = time;
		};
		case Timer2:
		{
			timer2_struct.Timeout = time;
		};
		default:
			break;
		}
	}
}
//************************************
// Method:    getTimerout
// FullName:  getTimerout
// Access:    public 
// Returns:   u16
// Qualifier:
// Parameter: u8 whichTimer
//************************************
u16 getTimerout(u8 whichTimer)
{
	switch (whichTimer)
	{

	case Timer1:
	{
		return timer1_struct.Timeout;
	};
	break;
	case Timer2:
	{
		return timer2_struct.Timeout;
	};
	break;

	default: return 0;
	}

}
//
//************************************
// Method:    setTimerHertz
// FullName:  setTimerHertz
// Access:    public 
// Returns:   void
// Qualifier: 设置定时器的发生频率
// Parameter: u8 whichTimer：哪一个定时器
// Parameter: u16 Hz：频率
//************************************
void setTimerHertz(u8 whichTimer, u16 Hz)
{
	switch (whichTimer)
	{

	case Timer1:
	{
		timer1_struct.Hz = Hz;
	};
	break;
	case Timer2:
	{
		timer2_struct.Hz = Hz;
	};
	break;

	}


}
u16 getTimerHertz(u8 whichTimer)
{
	switch (whichTimer)
	{

		break;
	case Timer1:
	{
		return timer1_struct.Hz;
	};
	break;
	case Timer2:
	{
		return timer2_struct.Hz;
	};
	break;
	default: return 0;
	}
}
//停用定时器
//************************************
// Method:    stopTimer
// FullName:  stopTimer
// Access:    public 
// Returns:   void
// Qualifier: 停止对应的定时器
// Parameter: u8 whichTimer
//************************************
void stopTimer(u8 whichTimer)
{
	switch (whichTimer)
	{
	case Timer1:
	{
		Timer4_Stop();
		Timer1_state = STOPPED;

	};
	break;
	case Timer2:
	{
		//		Timer3_Stop();//此处就是timer3，不是timer2，timer2跳过了，因为留给串口使用了		
		//		Timer2_state = STOPPED;

	};
	break;
	}

}
//若定时器已启动但未达到定时时间返回1
//************************************
// Method:    isActiveTimer
// FullName:  isActiveTimer
// Access:    public 
// Returns:   bit
// Qualifier: 若当前定时器正在定时着返回1，否则为0
// Parameter: u8 whichTimer
//************************************
bit isActiveTimer(u8 whichTimer)
{
	switch (whichTimer)
	{
	case Timer1:
	{
		return  Timer1_state == ACTIVE;

	};
	case Timer2:
	{
		return  Timer2_state == ACTIVE;

	};
	break;
	}
}
//当定时达到设定时间时返回1
//************************************
// Method:    isExpiredTimer
// FullName:  isExpiredTimer
// Access:    public 
// Returns:   bit
// Qualifier: 若定时器的定时时间已到则返回1
// Parameter: u8 whichTimer
//************************************
bit isExpiredTimer(u8 whichTimer)
{
	switch (whichTimer)
	{
	case Timer1:
	{
		return  Timer1_state == EXPIRED;
	};
	case Timer2:
	{
		return  Timer2_state == EXPIRED;
	};
	break;
	}


}
//当定时器被停止时返回1
//************************************
// Method:    isStopped
// FullName:  isStopped
// Access:    public 
// Returns:   bit
// Qualifier: 若定时器已经被停止则返回1
// Parameter: u8 whichtimer
//************************************
bit isStopped(u8 whichtimer)
{
	switch (whichtimer)
	{
	case Timer1:
	{
		return  Timer1_state == STOPPED;
	};
	case Timer2:
	{
		return  Timer2_state == STOPPED;
	};
	break;
	}
}

//
//************************************
// Method:    restartTimer
// FullName:  restartTimer
// Access:    public 
// Returns:   void
// Qualifier: 初始化并打开定时器，需要先设置好定时时间或频率
// Parameter: u8 whichTimer
//************************************
void restartTimer(u8 whichTimer)
{
	if (!isActiveTimer(whichTimer))
	{
		switch (whichTimer)
		{
		case Timer1:
		{
			Timer4_Run();
			Timer1_state = ACTIVE;
		};
		break;
		case Timer2:
		{
			//			Timer3_Run();
			//			Timer2_state = ACTIVE;
		};
		break;
		default:
			break;
		}



	}
}
//
//************************************
// Method:    onRestartTimer
// FullName:  onRestartTimer
// Access:    public 
// Returns:   bit
// Qualifier: 当定时器定时结束后返回1，并自动调用restart（），重新定时，并以此循环
// Parameter: u8 whichTimer
//************************************
bit onRestartTimer(u8 whichTimer)
{
	if (isExpiredTimer(whichTimer))
	{
		restartTimer(whichTimer);
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}


//获取从开机后的微秒数
u16 getMicros(void)
{

	return  micros;
}
//获取从开机后的毫秒数
u16 getMillis(void)
{
	return millis;
}
u8 getSeconds(void)
{
	return seconds;
}
u8 getMinutes(void)
{
	return minutes;
}
u8 getHours(void)
{
	return hours;
}
u8 getDays(void)
{
	return days;
}

//========================！！！以下私有函数，不需要了解也不要改动以下任何程序！！！=================//
/********************* Timer1中断函数************************/
//static void Timer1_ISR(void) interrupt TIMER1_VECTOR
//{

//	if ((++Timer1_temp) >= timer1_struct.Timeout)
//	{
//		Timer1_Stop();
//		Timer1_temp = 0;
//		Timer1_state = EXPIRED;
//	}



//}

// static void timer3_int(void) interrupt TIMER2_VECTOR
//{
//	if ((++Timer2_temp) >= 30)
//	{
//		Timer2_Stop();
//		Timer2_temp = 0;
//		Timer2_state = EXPIRED;
//	}

//}

/********************* Timer3中断函数************************/
//static void timer3_int(void) interrupt TIMER3_VECTOR
//{
//	if ((++Timer2_temp) >= timer2_struct.Timeout)
//	{
//		Timer3_Stop();
//		Timer2_temp = 0;
//		Timer2_state = EXPIRED;
//	}

//}
/********************* Timer4中断函数************************/
//问题遗留：
//问题解决，是sprintf函数的使用不当导致的输出错误，实际数值并没有错误
//static void timer4_int(void) interrupt TIMER4_VECTOR
//{


//	EA = 0;
//	if ((micros += 10) >= 1000)
//	{
//		micros = 0;
//		if ((++millis) >= 1000)
//		{
//			millis = 0;
//			if ((++seconds) >= 60)
//			{
//				seconds = 0;
//				if ((++minutes) >= 60)
//				{
//					minutes = 0;
//					if ((++hours) >= 24)
//					{
//						hours = 0;
//						if ((++days) == UCHAR_MAX)
//						{
//							days = 0;
//						}

//					}
//				}

//			}
//		}
//	}

//	EA = 1;
//}
/********************* Timer2中断函数************************/
//此定时器用作串口的定时器了
//void Timer2_ISR (void) interrupt TIMER2_VECTOR
//{
//	
//}


// 函数: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// 描述: 定时器初始化程序.
// 参数: TIMx: 结构参数,请参考timer.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
// 版本: V1.0, 2012-10-22
//========================================================================
static u8 Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if (TIM > Timer4)	return 1;	//空操作

	if (TIM == Timer0)
	{
		if (TIMx->TIM_Mode > TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TR0 = 0;		//停止计数
		ET0 = 0;	//禁止中断
		PT0 = 0;	//低优先级中断
		TMOD &= 0xf0;	//定时模式, 16位自动重装
		AUXR &= ~0x80;	//12T模式, 
		INT_CLKO &= ~0x01;	//不输出时钟
		if (TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//允许中断
		if (TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//高优先级中断
		TMOD |= TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 16位自动重装, 不可屏蔽中断
		if (TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |= 0x80;	//1T
		if (TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |= 0x04;	//对外计数或分频
		if (TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |= 0x01;	//输出时钟

		TH0 = (u8)(TIMx->TIM_Value >> 8);
		TL0 = (u8)TIMx->TIM_Value;
		if (TIMx->TIM_Run == ENABLE)	TR0 = 1;	//开始运行
		return	0;		//成功
	}

	if (TIM == Timer1)
	{
		TR1 = 0;		//停止计数
		if (TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//允许中断
		else									ET1 = 0;	//禁止中断
		if (TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//高优先级中断
		else									PT1 = 0;	//低优先级中断
		if (TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TMOD = (TMOD & ~0x30) | TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装
		if (TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x40;	//12T
		if (TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |= 0x40;	//1T
		if (TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |= 0x40;	//对外计数或分频
		else										TMOD &= ~0x40;	//定时
		if (TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |= 0x02;	//输出时钟
		else							INT_CLKO &= ~0x02;	//不输出时钟

		TH1 = (u8)(TIMx->TIM_Value >> 8);
		TL1 = (u8)TIMx->TIM_Value;
		if (TIMx->TIM_Run == ENABLE)	TR1 = 1;	//开始运行
		return	0;		//成功
	}

	if (TIM == Timer2)		//Timer2,固定为16位自动重装, 中断无优先级
	{
		AUXR &= ~(1 << 4);	//停止计数
		if (TIMx->TIM_Interrupt == ENABLE)			IE2 |= (1 << 2);	//允许中断
		else										IE2 &= ~(1 << 2);	//禁止中断
		if (TIMx->TIM_ClkSource > TIM_CLOCK_Ext)	return 2;
		if (TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~(1 << 2);	//12T
		if (TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |= (1 << 2);	//1T
		if (TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |= (1 << 3);	//对外计数或分频
		else										AUXR &= ~(1 << 3);	//定时
		if (TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |= 0x04;	//输出时钟
		else							INT_CLKO &= ~0x04;	//不输出时钟

		TH2 = (u8)(TIMx->TIM_Value >> 8);
		TL2 = (u8)TIMx->TIM_Value;
		if (TIMx->TIM_Run == ENABLE)	AUXR |= (1 << 4);	//开始运行
		return	0;		//成功
	}

	if (TIM == Timer3)		//Timer3,固定为16位自动重装, 中断无优先级
	{
		if (TIMx->TIM_ClkSource > TIM_CLOCK_Ext)	return 2;
		T4T3M &= 0xf0;		//停止计数, 定时模式, 12T模式, 不输出时钟
		IE2 &= ~(1 << 5);	//禁止中断
		if (TIMx->TIM_Interrupt == ENABLE)			IE2 |= (1 << 5);	//允许中断
		if (TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T4T3M |= (1 << 1);	//1T
		if (TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T4T3M |= (3 << 1);	//对外计数或分频
		if (TIMx->TIM_ClkOut == ENABLE)	T4T3M |= 1;	//输出时钟

		TH3 = (u8)(TIMx->TIM_Value >> 8);
		TL3 = (u8)TIMx->TIM_Value;
		if (TIMx->TIM_Run == ENABLE)	T4T3M |= (1 << 3);	//开始运行
		return	0;		//成功
	}

	if (TIM == Timer4)		//Timer4,固定为16位自动重装, 中断无优先级
	{
		if (TIMx->TIM_ClkSource > TIM_CLOCK_Ext)	return 2;
		T4T3M &= 0x0f;		//停止计数, 定时模式, 12T模式, 不输出时钟
		IE2 &= ~(1 << 6);	//禁止中断
		if (TIMx->TIM_Interrupt == ENABLE)			IE2 |= (1 << 6);	//允许中断
		if (TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T4T3M |= (1 << 5);	//1T
		if (TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T4T3M |= (3 << 5);	//对外计数或分频

		TH4 = (u8)(TIMx->TIM_Value >> 8);
		TL4 = (u8)TIMx->TIM_Value;
		if (TIMx->TIM_Run == ENABLE)	T4T3M |= (1 << 7);	//开始运行
		if (TIMx->TIM_ClkOut == ENABLE)	T4T3M |= (1 << 4);	//输出时钟

		return	0;		//成功
	}

	return 2;	//错误
}


