/************************************************************
* 组织名称：
* 文件名称: K:\单片机相关\电子大赛程序框架\HARDWARE\COMMON_HARDWARE\FIXEDPULSER.C
* 作者:   周晨阳
* 版本:  1.0
* 日期:     2017/07/18
* 描述:	用来产生固定脉冲数的软件,最多定义两个脉冲发生器，PULSER_1使用定时器3 p04，PULSER_2使用定时器4  p06
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
*  周晨阳 7/25  1.1  更改了定时器的定时时间，由原来最大能产生2500hz的脉冲变成可以产生5000hz的脉冲
*  周晨阳 7/27  1.2   重新定义了脉冲发生器的产生方式，使用两个定时器来产生两路脉冲，最小可以产生16hz的脉冲
***********************************************************/

#include "fixedPulser.h"
#define PULSER_NUM	2	//定义需要使用多少个脉冲发生器，最多可产生两路不同频率的脉冲
#define DEFAULT_PT	HIGH //脉冲发生器的起始电位

#define OPEN_TIMER3_CLKOUT() T4T3M |= 1
#define OPEN_TIMER4_CLKOUT() T4T3M |= (1 << 4)
#define CLOSE_TIMER3_CLKOUT() T4T3M &=(~ 1)
#define CLOSE_TIMER4_CLKOUT() T4T3M &=(~(1 << 4))


//#define DEFAULT_PT	LOW //
struct Pulser //脉冲发生器有关参数数据结构
{
	u32 count;  //脉冲个数
	u16 Hz;     //脉冲频率
	u8 state;   //脉冲发生器当前状态

};

static struct Pulser g_pulser[PULSER_NUM];  //脉冲发生器信息存储数组
static u16 tmp = 0;//软件定时器需要使用的变量，写在外面是为了减轻中断的计算量，增加定时精度
static bit timer2UseBit = 0;//是否需要使用计数变量来产生低于定时器最低可产生的频率的标志位
static bit timer3UseBit = 0;//是否需要使用计数变量来产生低于定时器最低可产生的频率的标志位
bool setPulse(u8 pulser_num, u16 Hz, u32 count)
{
	u16 timerTmp = 0;
	u16 TIM_Value;
	g_pulser[pulser_num].Hz = Hz;
	g_pulser[pulser_num].count = count;
	if (pulser_num == PULSER_1)
	{
		if (Hz > 20)//大于20hz直接使用定时器赋值
		{
			//PrintString1("hz >20\r\n");

			TIM_Value = (65536UL - ((MAIN_Fosc / 12) / Hz / 2));
			timer2UseBit = 0;
			INT_CLKO |= 0x04;	//输出时钟
			TH2 = (u8)(TIM_Value >> 8);
			TL2 = (u8)TIM_Value;

		}
		else//小于20hz则另外计算
		{
			timer2UseBit = 1;
			//	CLOSE_TIMER2_CLKOUT();
		}
	}
	else
	{
		if (Hz > 20)
		{
			TIM_Value = (65536UL - ((MAIN_Fosc / 12) / Hz / 2));
			timer3UseBit = 0;
			T4T3M |= 1;	//输出时钟
			TH3 = (u8)(TIM_Value >> 8);
			TL3 = (u8)TIM_Value;

		}
		else
		{
			timer3UseBit = 1;
		}
	}

	return 1;
}
bool openPulser(u8 pulser_num)
{
	g_pulser[pulser_num].state = ON;

	if (pulser_num == PULSER_1) //pulser2
	{
		Timer2_Run();
		//	PrintString1("pulser 1 is start\n");

	}
	else   //pulser1
	{
		Timer3_Run();
	}

	return OK;
}
bool closePulser(u8 pulser_num)
{
	if (pulser_num == PULSER_1)//pulser2
	{
		Timer2_Stop();


	}
	else //pulser1
	{
		Timer3_Stop();

	}
	g_pulser[pulser_num].state = OFF;
	return OK;

}
bool getPulserState(u8 pulser_num)
{

	return g_pulser[pulser_num].state;

}
void PulserInit(void)//初始化程序
{
	//PULSER_1 使用P30 PULSER_2 使用P04

	GPIO_InitTypeDef    GPIO_InitStructure;     //结构定义
	GPIO_InitStructure.Mode = GPIO_PullUp;       //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_InitStructure.Pin = GPIO_Pin_0;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作!!!!!!!GPIO初始化使用按位或不是逻辑或，之前因为这个被坑了
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);  //初始化
	GPIO_InitStructure.Pin = GPIO_Pin_4;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作!!!!!!!GPIO初始化使用按位或不是逻辑或，之前因为这个被坑了
	GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);  //初始化
	g_pulser[PULSER_1].state = OFF;
	g_pulser[PULSER_2].state = OFF;
#ifdef DEBUG
	PrintString1("two pulser was initialized");
#endif
}


/***************！以下为私有函数，不建议更改！********************************/

/********************* Timer3中断函数，用于产生指定脉冲************************/
//200us产生一次中断，
static u16 pulser1Tmp = 0;
static u16 count1Tmp = 0;
//static void Pulser_1Int(void) interrupt TIMER2_VECTOR   //2.5ms产生一次中断
//{
//	//PrintString1("into timer inte\n");
////	if (timer2UseBit == 1)//如果设置的频率小于20hz再使用计数器累加的办法产生
////	{
////		if (++pulser1Tmp >= tmp)

////		{
////			//	PrintString1("p15 state changed\n");

////			pulser1Tmp = 0;
////			if (count1Tmp++ <= g_pulser[PULSER_1].count)
////			{
////				P30 = ~P30;

////				//	PrintString1("p15 state is changed\n");
////			}
////			else
////			{
////				closePulser(PULSER_1);
////				count1Tmp = 0;

////			}
////		}
////	}
////	else//如果频率大于20则直接用高速脉冲产生
//	{
//		if (++count1Tmp >= g_pulser[PULSER_1].count*2)
//		{
//			count1Tmp = 0;
//			closePulser(PULSER_1);
//		}
//	}
static void Pulser_1Int(void) interrupt TIMER2_VECTOR   //2.5ms产生一次中断
{
	if ((++pulser1Tmp) >= 2 * g_pulser[PULSER_1].count)
	{
		closePulser(PULSER_1);
		pulser1Tmp = 0;
	}

}
static u16 pulser2Tmp = 0;
static u16 count2Tmp = 0;

static void Pulser_2Int(void) interrupt TIMER3_VECTOR   //2.5ms产生一次中断
{
	if ((++pulser2Tmp) >= 2 * g_pulser[PULSER_2].count)
	{
		closePulser(PULSER_2);
		pulser2Tmp = 0;
	}

}


//static u32 g_PWM_7tmp = 0;//计数变量
////中断执行程序，用来记录脉冲的个数并及时关闭发生器
//static void PWM_Routine(void) interrupt 22   
//{

//	if (PWMIF ^ 5 == 1)//PWM_7第二反转中断
//	{

//		PWMIF &= (~(1 << 5));  //软件清零标志位
//	//	PrintString1(" pwm7 count++\n");

//		if (g_PWM_7tmp++ >= g_pulser[PULSER_1].count)
//		{
//			//			PrintString1("pwm7 temp >= count\n");
//			g_PWM_7tmp = 0;
//			closePulser(PULSER_1); //到了指定的脉冲数后就关闭脉冲发生器

//		}

//	}
//	//现在选择使用定时器模拟一路脉冲发生器了
//	//	if (PWMIF ^ 4 == 1)//PWM_6
//	//	{
//	//		PWMIF &= (~(1 << 4));  //软件清零标志位
//	////			PrintString1("pwm6 count++\n");
//	//		if (g_PWM_6tmp++ >= g_pulser[PULSER_2].count)
//	//		{
//	//			//					PrintString1(" pwm6 temp >= count\n");
//	//			g_PWM_6tmp = 0;
//	//			closePulser(PULSER_2);
//	//			close_PWM_ALL();
//	//		}
//	//
//	//	}
//}
