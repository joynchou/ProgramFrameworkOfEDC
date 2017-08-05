#include "ADS1115.H"
#include "../BSP/GPIO/GPIO.h"
#include "../BSP/delay/delay.h"
#include <stdio.h>
#define ADS1115_ADDR 1001000//器件地址，addr接地
#define CONFIG_REGISTER 00000001//配置寄存器的地址
#define CONVERSION_REGISTER 00000000//转换结果寄存器地址
static void writeConfigRegister()
{
	IIC_Start();
	InputOneByte(0x90);//器件地址，写模式
	IIC_RdAck();            // 读应答信号

	InputOneByte(0x01);//指向配置寄存器
	IIC_RdAck();            // 读应答信号

	InputOneByte(0xc2);//配置模式
	IIC_RdAck();            // 读应答信号

	InputOneByte(0xe3);//配置模式
	IIC_RdAck();            // 读应答信号

	IIC_Stop();

}
static void changeRegister()
{
	IIC_Start();
	InputOneByte(0x90);
	IIC_RdAck();            // 读应答信号

	InputOneByte(0x00);		//指向转换结果寄存器
	IIC_RdAck();            // 读应答信号

	IIC_Stop();
}
static u16 readConversionRegister()
{
	u8 str[10];
	u16 result;
	u8 resultH=0, resultL=0;
	IIC_Start();
	InputOneByte(0x91);
	IIC_RdAck();            // 读应答信号
	resultH = OutputOneByte();
 	IIC_Ack();
	resultL = OutputOneByte();
	IIC_Stop();
	result = (((u16)resultH)<<8 ) | resultL;
	return result;
}


void ADS1115_Config(u8 speed, u8 mode)
{
	GPIO_InitTypeDef IIC_GPIO_Init;
	IIC_GPIO_Init.Mode = GPIO_PullUp;
	IIC_GPIO_Init.Pin = GPIO_Pin_4 | GPIO_Pin_3;
	GPIO_Inilize(GPIO_P2, &IIC_GPIO_Init);

}
u16 getADS1115ConvsionData(u8 channl)
{
	u16 Data;
	writeConfigRegister();
	changeRegister();
	return  readConversionRegister();
}
