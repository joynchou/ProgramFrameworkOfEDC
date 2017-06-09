/************************************************************
* 组织名称： (C), 1988-1999, Tech. Co., Ltd.
* 文件名称: STC15_PWM.C
* 作者:  第三方
* 版本:  1.1
* 日期:  2017/4/27
* 描述:  硬件pwm的库函数
* 历史修改记录: // 历史修改记录
* <作者> <时间> <版本 > <描述>
* 周晨阳 2017/4/27 1.1 修改了一处代码错误，case参数错误
* 周晨阳 2017/5/6  1.2 增加了一些常用设置函数
***********************************************************/
#include    "stc15_pwm.h"
#include "../USER/GPIO.h"
//PWM信息存储
static struct
{
    u32  PWM_period;
    float PWM_2_duty;
    float PWM_3_duty;
    float PWM_4_duty;
    float PWM_5_duty;
    float PWM_6_duty;
    float PWM_7_duty;
} PWM_info;
static bit PWM_state=0;	//PWM状态寄存
//========================================================================
//u8    PWM_Inilize(PWM_InitTypeDef *PWM)
// 描述:PWM初始化程序
// 参数:u8 PWM_N:PWM路数标号(2~7) PWM: 结构参数,请参考pwm.h里的定义.
// 返回: 成功返回0, 错误返回1
//========================================================================
static void PWM_Inilize(u8 PWM_N,PWM_InitTypeDef *PWMx)
{
    P_SW2|=0X80;
    if(ENABLE==PWMx->PWM_GOTO_ADC)            //ENABLE=计数器归零时 触发ADC
    {
        PWMCFG|=(1<<7); //并的意思就是不会改变其他位的值
    }
    else
    {
        PWMCFG&=(~(1<<7)); //其实也可以用上边的办法，但是这样写的意思更直观
    }
    if(PWM_HIGHT==PWMx->PWM_V_INIT)              //PWM_HIGHT=初始高电平     PWM_LOW=初始低电平
    {
        PWMCFG|=(1<<PWM_N);
    }
    else
    {
        PWMCFG&=(~(1<<PWM_N));
    }
    if(ENABLE==PWMx->PWM_0ISR_EN)             //ENABLE=使能PWM计数器归零中断  DISABLE=关闭PWM计数器归零中断 但 CBIF仍然会被硬件置位
    {
        PWMCR|=(1<<6);
    }
    else
    {
        PWMCR&=(~(1<<6));
    }
    if(ENABLE==PWMx->PWM_OUT_EN)              //ENABLE=PWM通道x的端口为PWM波形输出口 受PWM波形发生器控制
    {
        PWMCR|=(1<<PWM_N);
    }
    else
    {
        PWMCR&=(~(1<<PWM_N));
    }
    if(ENABLE==PWMx->PWM_UNUSUAL_EN)          //ENABLE=使能PWM的外部异常检测功能
    {
        PWMFDCR=(1<<5);
    }
    else
    {
        PWMFDCR&=(~(1<<5));
    }
    if(ENABLE==PWMx->PWM_UNUSUAL_OUT)         //ENABLE=发生异常时，PWM对应的输出口会变成 高阻输入模式
    {
        PWMFDCR=(1<<4);
    }
    else
    {
        PWMFDCR&=(~(1<<4));
    }
    if(ENABLE==PWMx->PWM_UNUSUAL_ISR_EN)      //ENABLE=使能异常检测中断 DISABLE=关闭异常检测中断 但FDIF仍然会被硬件置位
    {
        PWMFDCR=(1<<3);
    }
    else
    {
        PWMFDCR&=(~(1<<3));
    }
    if(ENABLE==PWMx->PWM_UNUSUAL_CMP0_EN)     //ENABLE=异常检测源为比较器的输出 当比较结果为高时 触发PWM异常
    {
        PWMFDCR=(1<<2);
    }
    else
    {
        PWMFDCR&=(~(1<<2));
    }
    if(ENABLE==PWMx->PWM_UNUSUAL_P24_EN)      //ENABLE=异常检测源为P24/PWMFLT 当P24=1 触发PWM异常
    {
        PWMFDCR=(1<<1);
    }
    else
    {
        PWMFDCR&=(~(1<<1));
    }
    //  PWMCKS=0;
    if(PWM_Clock_NT==PWMx->PWM_CLOCK)               //PWM_Clock_NT=PWM的时钟源是系统时钟经分频后的时钟  PWM_Clock_Timer2_OF=PWM的时钟源是TMER2的溢出脉冲
    {
        PWMCKS&=(~(1<<4));
    }
    else
    {
        PWMCKS|=(1<<4);
    }
    // PWMCKS=0x00;
    PWMCKS|=PWMx->PWM_CLOCK_DIV;           //当PWM_CLOCK=PWM_Clock_NT时 PWM的时钟源是系统时钟/(PS[3:0]+1)
    switch(PWM_N)
    {
    case PWM_2:
    {
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
        {
            PWM2CR&=(~(1<<3));
        }
        else
        {
            PWM2CR|=(1<<3);
        }
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
        {
            PWM2CR|=(1<<2);
        }
        else
        {
            PWM2CR&=(~(1<<2));
        }
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=使能第一翻转中断
        {
            PWM2CR|=(1<<1);
        }
        else
        {
            PWM2CR&=(~(1<<1));
        }
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=使能第二翻转中断
        {
            PWM2CR|=(1<<0);
        }
        else
        {
            PWM2CR&=(~(1<<0));
        }
    }
    break;
    case PWM_3:
    {
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
        {
            PWM3CR&=(~(1<<3));
        }
        else
        {
            PWM3CR|=(1<<3);
        }
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
        {
            PWM3CR|=(1<<2);
        }
        else
        {
            PWM3CR&=(~(1<<2));
        }
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=使能第一翻转中断
        {
            PWM3CR|=(1<<1);
        }
        else
        {
            PWM3CR&=(~(1<<1));
        }
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=使能第二翻转中断
        {
            PWM3CR|=(1<<0);
        }
        else
        {
            PWM3CR&=(~(1<<0));
        }
    }
    break;
    case PWM_4:
    {
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
        {
            PWM4CR&=(~(1<<3));
        }
        else
        {
            PWM4CR|=(1<<3);
        }
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
        {
            PWM4CR|=(1<<2);
        }
        else
        {
            PWM4CR&=(~(1<<2));
        }
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=使能第一翻转中断
        {
            PWM4CR|=(1<<1);
        }
        else
        {
            PWM4CR&=(~(1<<1));
        }
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=使能第二翻转中断
        {
            PWM4CR|=(1<<0);
        }
        else
        {
            PWM4CR&=(~(1<<0));
        }
    }
    break;
    case PWM_5:
    {
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
        {
            PWM5CR&=(~(1<<3));
        }
        else
        {
            PWM5CR|=(1<<3);
        }
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
        {
            PWM5CR|=(1<<2);
        }
        else
        {
            PWM5CR&=(~(1<<2));
        }
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=使能第一翻转中断
        {
            PWM5CR|=(1<<1);
        }
        else
        {
            PWM5CR&=(~(1<<1));
        }
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=使能第二翻转中断
        {
            PWM5CR|=(1<<0);
        }
        else
        {
            PWM5CR&=(~(1<<0));
        }
    }
    break;
    case PWM_6:
    {
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
        {
            PWM6CR&=(~(1<<3));
        }
        else
        {
            PWM6CR|=(1<<3);
        }
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
        {
            PWM6CR|=(1<<2);
        }
        else
        {
            PWM6CR&=(~(1<<2));
        }
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=使能第一翻转中断
        {
            PWM6CR|=(1<<1);
        }
        else
        {
            PWM6CR&=(~(1<<1));
        }
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=使能第二翻转中断
        {
            PWM6CR|=(1<<0);
        }
        else
        {
            PWM6CR&=(~(1<<0));
        }
    }
    break;
    case PWM_7:
    {
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
        {
            PWM7CR&=(~(1<<3));
        }
        else
        {
            PWM7CR|=(1<<3);
        }
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
        {
            PWM7CR|=(1<<2);
        }
        else
        {
            PWM7CR&=(~(1<<2));
        }
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=使能第一翻转中断
        {
            PWM7CR|=(1<<1);
        }
        else
        {
            PWM7CR&=(~(1<<1));
        }
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=使能第二翻转中断
        {
            PWM7CR|=(1<<0);
        }
        else
        {
            PWM7CR&=(~(1<<0));
        }
    }
    break;
    default:
//      return 1;
        break;
    }
    if(ENABLE==PWMx->PWM_EN)                  //ENABLE=PWM使能 在其他PWM参数设置好后最后设置 如果被关闭后在打开，则PWM计数器重新从0计数
    {
        PWMCR|=(1<<7);
    }
    else
    {
        PWMCR&=(~(1<<7));
    }
}
/*************************************************
* 函数名称: void    PWM_config(u8 PWM_N)
* 描述: 配置需要使用的pwm通道
* 输入: u8 PWM_N，N的范围是2~7
* 返回值: 无
* 其他说明: 将会自动初始化相应的io引脚
*************************************************/
void    PWM_config(u8 PWM_N)
{
    GPIO_InitTypeDef    GPIO_InitStructure;     //结构定义
    PWM_InitTypeDef  PWM_InitStructure;
    switch(PWM_N)
    {
    case PWM_2:
    {
        GPIO_InitStructure.Pin  = GPIO_Pin_7 ;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
        GPIO_InitStructure.Mode = GPIO_PullUp;
        GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);  //初始化
        P37=1;
    };
    break;
    case PWM_3:
    {
        GPIO_InitStructure.Pin  = GPIO_Pin_1 ;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
        GPIO_InitStructure.Mode = GPIO_PullUp;       //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);  //初始化
        P21=1;
    };
    break;
    case PWM_4:
    {
        GPIO_InitStructure.Pin  = GPIO_Pin_2 ;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
        GPIO_InitStructure.Mode = GPIO_PullUp;       //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);  //初始化
        P22=1;
    };
    break;
    case PWM_5:
    {
        GPIO_InitStructure.Pin  = GPIO_Pin_3 ;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
        GPIO_InitStructure.Mode = GPIO_PullUp;       //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);  //初始化
        P23=1;
    };
    break;
    case PWM_6:
    {
        GPIO_InitStructure.Pin  = GPIO_Pin_6;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
        GPIO_InitStructure.Mode = GPIO_PullUp;       //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);  //初始化
        P16=1;
    };
    break;
    case PWM_7:
    {
        GPIO_InitStructure.Pin  = GPIO_Pin_7 ;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
        GPIO_InitStructure.Mode = GPIO_PullUp;       //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);  //初始化
        P17=1;
    };
    break;
    }
    PWM_UNLOCK;
    PWM_InitStructure.PWM_GOTO_ADC=DISABLE;
    PWM_InitStructure.      PWM_V_INIT= PWM_LOW;
    PWM_InitStructure.      PWM_0ISR_EN=  DISABLE;
    PWM_InitStructure.      PWM_OUT_EN=ENABLE;
    PWM_InitStructure.     PWM_UNUSUAL_EN= DISABLE;
    PWM_InitStructure.     PWM_UNUSUAL_OUT=  DISABLE;
    PWM_InitStructure.     PWM_UNUSUAL_ISR_EN=DISABLE;
    PWM_InitStructure.     PWM_UNUSUAL_CMP0_EN=DISABLE;
    PWM_InitStructure.     PWM_UNUSUAL_P24_EN=DISABLE;
    PWM_InitStructure.       PWM_CLOCK=PWM_Clock_NT;
    PWM_InitStructure.       PWM_CLOCK_DIV=0x00;
    PWM_InitStructure.       PWM_SELECTx_IO=PWM_SELECT_N;
    PWM_InitStructure.     PWM_ISRx_EN=  DISABLE;
    PWM_InitStructure.       PWM_T1x_EN=   DISABLE;
    PWM_InitStructure.       PWM_T2x_EN=    DISABLE;
    PWM_InitStructure.       PWM_EN=  DISABLE;
    PWM_Inilize(PWM_N,&PWM_InitStructure) ;
    PWM_LOCK;
    
  
}
//void PCA_PWM_config(void)//PCA备用pwm
//{
////      PCA_InitStructure.PCA_Clock    = PCA_Clock_12T;     //PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
////    PCA_InitStructure.PCA_IoUse    = PCA_P24_P25_P26_P27;   //PCA_P12_P11_P10_P37, PCA_P34_P35_P36_P37, PCA_P24_P25_P26_P27
////    PCA_InitStructure.PCA_Interrupt_Mode = ENABLE;     //ENABLE, DISABLE
////    PCA_InitStructure.PCA_Polity   = PolityLow;         //????? Polityduty,PolityLow
////    PCA_Init(PCA_Counter,&PCA_InitStructure);
////    PCA_InitStructure.PCA_Mode     = PCA_Mode_HighPulseOutput;      //PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_dutyPulseOutput
////    PCA_InitStructure.PCA_PWM_Wide = 0;      //PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit
////    PCA_InitStructure.PCA_Interrupt_Mode = ENABLE;     //PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
////    PCA_InitStructure.PCA_Value    = 100;         //??PWM,?8??PWM???
////    PCA_Init(PCA0,&PCA_InitStructure);
////    PCA_InitStructure.PCA_Mode     = PCA_Mode_HighPulseOutput;      //PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_dutyPulseOutput
////    PCA_InitStructure.PCA_PWM_Wide = 0;      //PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit
////    PCA_InitStructure.PCA_Interrupt_Mode = ENABLE;     //PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
////    PCA_InitStructure.PCA_Value    = 100;         //??PWM,?8??PWM???
////    PCA_Init(PCA1,&PCA_InitStructure);
//}

/////////////////////////////////////////
//设置PWM周期
u8 PWM_SET_PERIOD(u16 period)
{
    if(0x8000>period)
    {
        PWMCL=(u8)(period);
        PWMCH=(u8)(period>>8);
        return 0;
    }
    else
    {
        return 1;
    }
}
/////////////////////////////////////////
//设置PWM第一次和第二次翻转周期
//这个库函数的错误：全都是设置的pwm2
static u8 PWM_SET_T12_PERIOD(u8 PWM_N,u16 period1,u32 period2)
{
    switch(PWM_N)
    {
    case PWM_2:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
    case PWM_3:
        PWM3T1L=(u8)(period1);
        PWM3T1H=(u8)(period1>>8);
        PWM3T2L=(u8)(period2);
        PWM3T2H=(u8)(period2>>8);
        return 0;
        break;
    case PWM_4:
        PWM4T1L=(u8)(period1);
        PWM4T1H=(u8)(period1>>8);
        PWM4T2L=(u8)(period2);
        PWM4T2H=(u8)(period2>>8);
        return 0;
        break;
    case PWM_5:
        PWM5T1L=(u8)(period1);
        PWM5T1H=(u8)(period1>>8);
        PWM5T2L=(u8)(period2);
        PWM5T2H=(u8)(period2>>8);
        return 0;
        break;
    case PWM_6:
        PWM6T1L=(u8)(period1);
        PWM6T1H=(u8)(period1>>8);
        PWM6T2L=(u8)(period2);
        PWM6T2H=(u8)(period2>>8);
        return 0;
        break;
    case PWM_7:
        PWM7T1L=(u8)(period1);
        PWM7T1H=(u8)(period1>>8);
        PWM7T2L=(u8)(period2);
        PWM7T2H=(u8)(period2>>8);
        return 0;
        break;
    default:
        return 1;
        break;
    }
}
/*************************************************
* 函数名称: u32 getPWM_period(void )
* 描述: 返回所设置的pwm频率信息
* 输入: 无
* 输出: 无
* 返回值: pwm频率
* 其他说明: 若没有设置pwm的频率就调用此函数则会返回0；
*************************************************/
u32 getPWM_period(void )
{
    return PWM_info.PWM_period;
}
/*************************************************
* 函数名称: float getPWM_n_duty(u8 PWM_N)
* 描述: 返回PWM_N的占空比信息
* 输入: u8 PWM_N
* 输出: 无
* 返回值: PWM_N的占空比信息,float形式
* 其他说明: 若没有设置pwm的占空比就调用此函数则会返回0；
*************************************************/
float getPWM_N_duty(u8 PWM_N)
{
    switch(PWM_N)
    {
    case PWM_2:
        return PWM_info.PWM_2_duty;
        break;
    case PWM_3:
        return PWM_info.PWM_3_duty;
        break;
    case PWM_4:
        return PWM_info.PWM_4_duty;
        break;
    case PWM_5:
        return PWM_info.PWM_5_duty;
        break;
    case PWM_6:
        return PWM_info.PWM_6_duty;
        break;
    case PWM_7:
        return PWM_info.PWM_7_duty;
        break;
    }
}


/*************************************************
* 函数名称:void PWM_period(u16 Hz)
* 描述: 设置硬件pwm的同一频率 ，并保存频率数据
* 被本函数调用的函数:
* 1.PWM_SET_PERIOD
* 调用本函数的函数:
* 输入:
* 1.u16 Hz:要输出的pwm的频率，作为计数器的参数值，由于硬件所限，将会改变所有6个pwm的频率
* 输出: 无
* 返回值: 无
* 其他: 此函数只能设置pwm的计数器初始值，从而完成pwm不同频率的输出，
        但是由于单片机硬件所限，不可以单独对每路pwm的频率进行修改，
        只能一改全改。
*************************************************/
void PWM_period(u16 Hz)
{
    PWM_info.PWM_period= (u16)(MAIN_Fosc/Hz);
    PWM_UNLOCK;
    PWM_SET_PERIOD(PWM_info.PWM_period);
    PWM_LOCK;
}
/*************************************************
* 函数名称: void PWM_duty(u8 PWM_N,float duty)
* 描述: 修改某一路pwm的占空比 ，并保存占空比数据
* 被本函数调用的函数:
* 调用本函数的函数:
* 输入:
* 1.u8 PWM_N ： 哪一路pwm
* 2.float duty：占空比，使用小数，如0.8代表80%的占空比
* 输出: 无
* 返回值: 无
* 其他说明:
*************************************************/
void PWM_duty(u8 PWM_N,float duty)
{
    u32 period2;
    if(duty>0.95f)
    {
        duty=0.95f;
#ifdef PID_DEBUG
        PrintString1("duty is over the maximum\n");
#endif
    }
    if(duty<0.05f)
    {
        duty=0.05f;
#ifdef PID_DEBUG
        PrintString1("duty is over the miximum\n");
#endif
    }
    switch(PWM_N)
    {
    case PWM_2:
        PWM_info.PWM_2_duty=duty;
        period2=(u32)(PWM_info.PWM_2_duty*PWM_info.PWM_period ) ;
        break;
    case PWM_3:
        PWM_info.PWM_3_duty=duty;
        period2=(u32)(PWM_info.PWM_3_duty*PWM_info.PWM_period ) ;
        break;
    case PWM_4:
        PWM_info.PWM_4_duty=duty;
        period2=(u32)(PWM_info.PWM_4_duty*PWM_info.PWM_period ) ;
        break;
    case PWM_5:
        PWM_info.PWM_5_duty=duty;
        period2=(u32)(PWM_info.PWM_5_duty*PWM_info.PWM_period ) ;
        break;
    case PWM_6:
        PWM_info.PWM_6_duty=duty;
        period2=(u32)(PWM_info.PWM_6_duty*PWM_info.PWM_period ) ;
        break;
    case PWM_7:
        PWM_info.PWM_7_duty=duty;
        period2=(u32)(PWM_info.PWM_6_duty*PWM_info.PWM_period ) ;
        break;
    }
    PWM_UNLOCK;
    PWM_SET_T12_PERIOD(PWM_N,0,period2);
    PWM_LOCK;
}
void OPEN_PWM(void)
{
	PWM_UNLOCK;	
	PWM_ALL_EN;
	PWM_state=ON;
  PWM_LOCK;
}
void CLOSE_PWM(void)
{
	PWM_UNLOCK;	
	PWM_ALL_NO;
	PWM_state=OFF;
  PWM_LOCK;
	
}
bit getPWM_state(void)
{
	
return PWM_state;	
}

