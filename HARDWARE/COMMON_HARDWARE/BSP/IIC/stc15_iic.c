
/************************************************************
* 文件名称: 电子大赛程序框架\HARDWARE\COMMON_HARDWARE\BSP\IIC\STC15_IIC.C
* 作者:
* 版本:
* 日期:     2017/08/03
* 描述:iic的软件驱动程序
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
*
***********************************************************/

#include    "stc15_iic.h"
#include <stdio.h>
#include "../USART1/USART1.h"
/* ***************************************************** */
// 函数名称：Delay5US()
// 函数功能：5微秒延时,如果自己的主频有变，请自行修改
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void Delay5US(void)     //@24MHz
{

	unsigned char i;

	_nop_();
	_nop_();
	i = 57;
	while (--i);
}
/* ***************************************************** */
// 函数名称：IIC_Start()
// 函数功能：IIC起动
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void IIC_Start(void)
{
	SDA = 1;
	Delay5US();
	SCL = 1;
	Delay5US();
	SDA = 0;
	Delay5US();
}
/* ***************************************************** */
// 函数名称：IIC_Stop()
// 函数功能：IIC停止
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void IIC_Stop(void)
{
	SDA = 0;
	Delay5US();
	SCL = 1;
	Delay5US();
	SDA = 1;
}
/* ***************************************************** */
// 函数名称：IIC_Ack()
// 函数功能：IIC应答
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void IIC_Ack(void)
{
	SCL = 0;                // 为产生脉冲准备
	SDA = 0;                // 产生应答信号
	Delay5US();             // 延时你懂得
	SCL = 1;
	Delay5US();
	SCL = 0;
	Delay5US();     // 产生高脉冲
	SDA = 1;                // 释放总线
}
/* ***************************************************** */
// 函数名称：IIC_RdAck()
// 函数功能：读IIC应答
// 入口参数：无
// 出口参数：是否应答真值
/* ***************************************************** */
BOOL IIC_RdAck(void)
{
	BOOL AckFlag;
	u8 uiVal = 0;
	SCL = 0;
	Delay5US();
	SDA = 1;
	SCL = 1;
	Delay5US();
	while ((1 == SDA) && (uiVal < 255))
	{
		uiVal++;
		AckFlag = SDA;
	}
	SCL = 0;
	return AckFlag;     // 应答返回：0;不应答返回：1
}
/* ***************************************************** */
// 函数名称：IIC_Nack()
// 函数功能：IIC不应答
// 入口参数：无
// 出口参数：无
/* ***************************************************** */
void IIC_Nack(void)
{
	SDA = 1;
	SCL = 0;
	Delay5US();
	SCL = 1;
	Delay5US();
	SCL = 0;
}
/* ***************************************************** */
// 函数名称：OutputOneByte()
// 函数功能：从IIC器件中读出一个字节
// 入口参数：无
// 出口参数：读出的一个字节（uByteVal）
/* ***************************************************** */
u8 OutputOneByte(void)
{
	//    u8 uByteVal = 0;
	//    u8 iCount;
	//    SDA = 1;
	//    for (iCount = 0; iCount < 8; iCount++)
	//    {
	//        SCL = 0;
	//        Delay5US();
	//        SCL = 1;
	//        Delay5US();
	//        uByteVal <<= 1;
	//        if(SDA)
	//        {
	//            uByteVal |= 0x01;
	//        }
	//    }
	//    SCL = 0;
	//    return(uByteVal);
	u8 str[8];
	unsigned char i;
	unsigned char Data = 0;       //定义一个缓冲寄存器。
	for (i = 0; i < 8; i++)//有8位数据
	{
		SCL = 1;//拉高时钟线，为读取下一位数据做准备。
		Delay5US();
		Data = Data << 1;//将缓冲字节的数据左移一位，准备读取数据。
		Delay5US();
		if (SDA == 1)//如果数据线为高平电平。
		{
			Data = Data | 0x1;//则给缓冲字节的最低位写1。
		}
		else
		{
			Data = Data | 0x0;//
		}

		SCL = 0;//拉低时钟线，为读取下一位数据做准备。
		Delay5US();
	}

	return Data;//返回读取的一个字节数据。
}
/* ***************************************************** */
// 函数名称：InputOneByte()
// 函数功能：向IIC器件写入一个字节
// 入口参数：待写入的一个字节（uByteVal）
// 出口参数：无
/* ***************************************************** */
void InputOneByte(u8 uByteVal)
{
	u8 iCount;
	for (iCount = 0; iCount < 8; iCount++)
	{
		SCL = 0;
		Delay5US();
		SDA = (uByteVal & 0x80) >> 7;
		Delay5US();
		SCL = 1;
		Delay5US();
		uByteVal <<= 1;
	}
	SCL = 0;
}
/* ***************************************************** */
// 函数名称：IIC_WrDevAddAndDatAdd()
// 函数功能：向IIC器件写入器件和数据地址
// 入口参数：器件地址（uDevAdd），数据地址（uDatAdd）
// 出口参数：写入是否成功真值
/* ***************************************************** */
BOOL IIC_WrDevAddAndDatAdd(u8 uDevAdd, u8 uDatAdd)
{
	IIC_Start();            // 发送开始信号
	InputOneByte(uDevAdd);  // 输入器件地址
	IIC_RdAck();            // 读应答信号
	InputOneByte(uDatAdd);  // 输入数据地址
	IIC_RdAck();            // 读应答信号
	return TRUE;
}
/* ***************************************************** */
// 函数名称：IIC_WrDatToAdd()
// 函数功能：向IIC器件写数据
// 入口参数：器件ID(uDevID)、数据存储起始地址(uStaAddVal)
//           待存数据(*p)、连续存储数据的个数(uiLenVal)
// 出口参数：无
/* ***************************************************** */
void IIC_WrDatToAdd(u8 uDevID, u8 uStaAddVal, u8 *p, u8 ucLenVal)
{
	u8 iCount;
	IIC_WrDevAddAndDatAdd(uDevID | IIC_WRITE, uStaAddVal);
	// IIC_WRITE 为写命令后缀符
	for (iCount = 0; iCount < ucLenVal; iCount++)
	{
		InputOneByte(*p++);
		IIC_RdAck();
	}
	IIC_Stop();
}
/* ***************************************************** */
// 函数名称：IIC_RdDatFromAdd()
// 函数功能：向IIC器件读数据
// 入口参数：器件ID(uDevID)、数据存储地址(uStaAddVal)
//           待存数据(*p)、连续存储数据的个数(uiLenVal)
// 出口参数：无
/* ***************************************************** */
void IIC_RdDatFromAdd(u8 uDevID, u8 uStaAddVal, u8 *p, u8 uiLenVal)
{
	u8 iCount;
	IIC_WrDevAddAndDatAdd(uDevID | IIC_WRITE, uStaAddVal);
	IIC_Start();
	InputOneByte(uDevID | IIC_READ);
	// IIC_READ 为写命令后缀符
	IIC_RdAck();
	for (iCount = 0; iCount < uiLenVal; iCount++)
	{
		*p++ = OutputOneByte();
		if (iCount != (uiLenVal - 1))
		{
			IIC_Ack();
		}
	}
	IIC_Nack();
	IIC_Stop();
}

