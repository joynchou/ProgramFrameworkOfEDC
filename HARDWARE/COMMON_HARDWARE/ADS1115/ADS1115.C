#include "ADS1115.H"
#include "../BSP/GPIO/GPIO.h"
#include "../BSP/delay/delay.h"
#include <stdio.h>
#define ADS1115_ADDR 1001000//������ַ��addr�ӵ�
#define CONFIG_REGISTER 00000001//���üĴ����ĵ�ַ
#define CONVERSION_REGISTER 00000000//ת������Ĵ�����ַ
static void writeConfigRegister()
{
	IIC_Start();
	InputOneByte(0x90);//������ַ��дģʽ
	IIC_RdAck();            // ��Ӧ���ź�

	InputOneByte(0x01);//ָ�����üĴ���
	IIC_RdAck();            // ��Ӧ���ź�

	InputOneByte(0xc2);//����ģʽ
	IIC_RdAck();            // ��Ӧ���ź�

	InputOneByte(0xe3);//����ģʽ
	IIC_RdAck();            // ��Ӧ���ź�

	IIC_Stop();

}
static void changeRegister()
{
	IIC_Start();
	InputOneByte(0x90);
	IIC_RdAck();            // ��Ӧ���ź�

	InputOneByte(0x00);		//ָ��ת������Ĵ���
	IIC_RdAck();            // ��Ӧ���ź�

	IIC_Stop();
}
static u16 readConversionRegister()
{
	u8 str[10];
	u16 result;
	u8 resultH=0, resultL=0;
	IIC_Start();
	InputOneByte(0x91);
	IIC_RdAck();            // ��Ӧ���ź�
	resultH = OutputOneByte();
 	IIC_Ack();
	resultL = OutputOneByte();
 	//IIC_Ack();
	//IIC_Nack();

	IIC_Stop();
	result = (((u16)resultH)<<8 ) | resultL;//�߰�λ����8���ϵװ�λ���16λresult
//	sprintf(str,"H %d\r\n",resultH);
//	PrintString1(str);
//		sprintf(str,"L %d\r\n",resultL);
//	PrintString1(str);

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
	//delay_ms(15);
	changeRegister();
	//delay_ms(15);
	//Data =;
	return  readConversionRegister();
}