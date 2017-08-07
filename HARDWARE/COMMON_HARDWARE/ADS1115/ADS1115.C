/************************************************************
* 组织名称：
* 文件名称: K:\单片机相关\电子大赛程序框架\HARDWARE\COMMON_HARDWARE\ADS1115\ADS1115.C
* 作者:
* 版本:
* 日期:     2017/08/03
* 描述:  打开相应的通道后使用get函数获取相应通道的值
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
*
***********************************************************/

#include "ADS1115.H"
#include "../BSP/GPIO/GPIO.h"
#include "../BSP/delay/delay.h"
#include <stdio.h>
#define ADS1115_ADDR 1001000//器件地址，addr接地
#define CONFIG_REGISTER 00000001//配置寄存器的地址
#define CONVERSION_REGISTER 00000000//转换结果寄存器地址

typedef struct
{
	u16 value;
	u8 speed;
	u8 state;
}ADS1115;
static ADS1115 ADCchannel[4];

//************************************
// Method:    writeConfigRegister
// FullName:  writeConfigRegister
// Access:    public static 
// Returns:   void
// Qualifier:
//************************************
static void writeConfigRegister(u8 channel)
{
	IIC_Start();
	InputOneByte(0x90);//器件地址，写模式
	IIC_RdAck();            // 读应答信号

	InputOneByte(0x01);//指向配置寄存器
	IIC_RdAck();            // 读应答信号

	switch (channel)
	{
	case CHANNEL_1:
	{
		InputOneByte(0xc2);//配置模式
	};
	break;
	case CHANNEL_2:
	{
		InputOneByte(0xD2);//配置模式
	};
	break;
	case CHANNEL_3:
	{
		InputOneByte(0xE2);//配置模式
	};
	break;
	case CHANNEL_4:
	{
		InputOneByte(0xF2);//配置模式
	};
	break;

	}
	IIC_RdAck();            // 读应答信号

	InputOneByte(0xe3);//配置模式
	IIC_RdAck();            // 读应答信号

	IIC_Stop();

}
//************************************
// Method:    changeRegister
// FullName:  changeRegister
// Access:    public static 
// Returns:   void
// Qualifier:
//************************************
static void changeRegister(void)
{
	IIC_Start();
	InputOneByte(0x90);
	IIC_RdAck();            // 读应答信号

	InputOneByte(0x00);		//指向转换结果寄存器
	IIC_RdAck();            // 读应答信号

	IIC_Stop();
}
//************************************
// Method:    readConversionRegister
// FullName:  readConversionRegister
// Access:    public static 
// Returns:   u16
// Qualifier:
//************************************
static u16 readConversionRegister(void)
{
	u8 str[10];
	u16 result;
	u8 resultH = 0, resultL = 0;
	IIC_Start();
	InputOneByte(0x91);
	IIC_RdAck();            // 读应答信号
	resultH = OutputOneByte();
	IIC_Ack();
	resultL = OutputOneByte();
	IIC_Stop();
	result = (((u16)resultH) << 8) | resultL;
	return result;
}


//************************************
// Method:    ADS1115_Config
// FullName:  ADS1115_Config
// Access:    public 
// Returns:   void
// Qualifier: 器件初始化
// Parameter: u8 speed
// Parameter: u8 mode
//************************************
void ADS1115_Config(u8 speed, u8 mode)
{
	GPIO_InitTypeDef IIC_GPIO_Init;
	IIC_GPIO_Init.Mode = GPIO_PullUp;
	IIC_GPIO_Init.Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Inilize(GPIO_P3, &IIC_GPIO_Init);

}
//************************************
// Method:    getADS1115ConvsionData
// FullName:  getADS1115ConvsionData
// Access:    public 
// Returns:   u16
// Qualifier: 读取值
// Parameter: u8 channl
//************************************
u16 getADS1115ConvsionData(u8 channel)
{
	u16 Data;

	if (!ADCchannel[channel].state)
	{
		return 0;
	}
	writeConfigRegister(channel);
	changeRegister();
	return  readConversionRegister();
}
void open_ADS1115(u8 channel)
{
	ADCchannel[channel].state = ON;
}
void close_ADS1115(u8 channel)
{
	ADCchannel[channel].state = OFF;
}
