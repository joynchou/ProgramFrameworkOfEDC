#include "ANGLE.h"
//ADC初始化函数 p1^0
/*************************************************
* 函数名称:void    ADC_config(u8 pin,u8 speed)
* 描述: 初始化adc
* 输入：u8 pin:需要使用的adc引脚
*       u8 speed: adc的转换速度
* 其他说明:
* pin:
*                ADC_P10
*                ADC_P11
*                ADC_P12
*                ADC_P13
*                ADC_P14
*                ADC_P15
*                ADC_P16
*                ADC_P17
* speed:
*                ADC_90T
*                ADC_180T
*                ADC_360T
*                ADC_540T
*************************************************/
void    ADC_config(u8 pin, u8 speed)
{
    ADC_InitTypeDef     ADC_InitStructure;
    ADC_InitStructure.ADC_Px = pin;
    ADC_InitStructure.ADC_Speed = speed;
    ADC_InitStructure.ADC_Power = ENABLE;
    ADC_InitStructure.ADC_AdjResult = ADC_RES_H8L2;
    ADC_InitStructure.ADC_Polity = PolityLow;
    ADC_InitStructure.ADC_Interrupt = DISABLE;
    ADC_Inilize(&ADC_InitStructure);
    //ADC_PowerControl(ENABLE);
}
/*************************************************
* 函数名称: float getAngle(bit whichAngle)
* 描述:  读取当前风摆角度或者上一次读取的角度
* 输入:  bit whichAngle
* 返回值: float 角度
* 其他说明:
  接线方法已经固定，不能再改变
whichAngle:
                        PRESENT_ANGLE
            LAST_ANGLE
*************************************************/

#define AVERAGE  //若要取平均数，则去掉此注释
float getAngle(bit whichAngle)
{
		
    static float presentAngle, lastAngle;  //此函数还可以返回上一次的角度值，不需要读取时间 ，是静态的数据，因为需要保存
    if (whichAngle)  //返回当前结果
    {
        
#ifdef AVERAGE  //中位值平均滤波法（又称防脉冲干扰平均滤波法）
		u8 angleDataloopTemp1;
	  u8 angleDataloopTemp2;
	  u16 angleData[11]; 
	  u16 maxValue = 0;
    u16 minValue = 1024;
					{
								angleData[10] = 0;//清除之前的数据
							for(angleDataloopTemp1 = 0; angleDataloopTemp1 < 10; angleDataloopTemp1++) //读取10次数据并保存在数组中
								{
									angleData[angleDataloopTemp1] =  Get_ADC10bitResult(ADC_CH0);
								}
								
							for (angleDataloopTemp2 = 0; angleDataloopTemp2 < 10; angleDataloopTemp2++) //找出最大值和最小值
								{
								if (angleData[angleDataloopTemp2] > maxValue) //去掉最大值最小值
								{
									maxValue = angleData[angleDataloopTemp2];
								}
								if (angleData[angleDataloopTemp2] < minValue) //去掉最大值最小值
								{
									minValue = angleData[angleDataloopTemp2];
								}
							}
							for (angleDataloopTemp2 = 0; angleDataloopTemp2 < 10; angleDataloopTemp2++)//将10个结果累加 
							{
								angleData[10] += angleData[angleDataloopTemp2]; 
							}
							angleData[10] -= (maxValue + minValue);  //去掉最大值最小值
							angleData[10] /= 8;	 //取平均值
							presentAngle= (-0.344811f*angleData[10])+ 277.95f ;//最终结果
			   }
#else
				 
		   presentAngle = (-0.344811f* Get_ADC10bitResult(ADC_CH0)) + 277.95f;  //每次的电阻改变后都需要重新测量
	
				 	
#endif
        
        lastAngle = presentAngle;
        return presentAngle;
    }
    else  //返回上一次结果
    {
        return  lastAngle;
    }
}
