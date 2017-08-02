/************************************************************
* 组织名称：
* 文件名称: BUTTON.c
* 作者:  周晨阳
* 版本 : v1.0
* 日期:
* 描述: 按键初始化及相关函数
* 主要函数及其功能 : 

* 历史修改记录: // 历史修改记录
* <作者> <时间> <版本 > <描述>
* 周晨阳
***********************************************************/
#include "BUTTON.h"

#define BUTTON
#ifdef BUTTON
static u8 g_Button[BUTTON_NUM] = {0};
/*************************************************
* 函数名称: void Button_config()
* 描述: 用于初始单片机的I/O口引脚
* 其他说明: 用于初始单片机的I/O口引脚
*************************************************/
void Button_config(void)
{
	GPIO_InitTypeDef    GPIO_InitStructure;     //结构定义
	GPIO_InitStructure.Mode = GPIO_PullUp;  
	GPIO_InitStructure.Pin = GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);  //初始化  
}

/************************************************
* 函数名称: unsigned char getButtonState(u8 BUTTON_data)
* 描述: 按键状态读取
* 输入: 按键引脚宏
* 返回值: 按键状态，按下返回1，未按下返回0，一直按着按键则按键只显示单次点击
* 其他说明: 此函数为外界接口函数
*************************************************/
u8 getButtonState(u8 BUTTON_data)
{
	u8 ButtonState;
	ButtonState = g_Button[BUTTON_data];
	g_Button[BUTTON_data] = 0;
  return ButtonState;
}

/*************************************************
* 函数名称: void  buttonScan(void )//按键扫描函数
* 描述: 按键检测程序
* 输入: 无
* 输出: 无
* 返回值: 无
* 其他说明: 此按键检测程序没有使用到定时器，
*           将在后续的工程中改进此函数
*************************************************/
void  buttonScan(void )//按键扫描函数
{
	u8 i,num;
	num = getButtonNum();
	if(num > 0)
	{
		g_Button[num - 1] = 1;
		if(getButtonNum() != 0)
		{		
			while(getButtonNum() != 0);
		}
		else
		{
			g_Button[num - 1] = 0;
		}
	}
}
#endif
