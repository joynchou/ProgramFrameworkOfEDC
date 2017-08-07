/************************************************************
* 文件名称: 电子大赛程序框架\HARDWARE\COMMON_HARDWARE\BSP\IIC\STC15_IIC.H
* 作者:     stc官方
* 版本:     v1.0
* 日期:     2017/08/03
* 描述:		软件模拟的iic程序
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
* 周晨阳 8/3    1.0     修改了iic引脚
***********************************************************/

#ifndef __STC15_IIC_H__
#define __STC15_IIC_H__
#include    "../config.h"
sbit SCL = P3 ^ 4;
sbit SDA = P3 ^ 5;
/* ***************************************************** */
#define IIC_WRITE 0x00
#define IIC_READ  0x01
//typedef enum{FALSE,TRUE} BOOL;
#define BOOL bit
extern void Delay5US(void);
extern void IIC_Start(void);
extern void IIC_Stop(void);
extern void IIC_Ack(void);
extern BOOL IIC_RdAck(void);
extern void IIC_Nack(void);
extern u8 OutputOneByte(void);
extern void InputOneByte(u8 uByteVal);
extern BOOL IIC_WrDevAddAndDatAdd(u8 uDevAdd, u8 uDatAdd);
extern void IIC_WrDatToAdd(u8 uDevID, u8 uStaAddVal, u8 *p, u8 ucLenVal);
extern void IIC_RdDatFromAdd(u8 uDevID, u8 uStaAddVal, u8 *p, u8 uiLenVal);
#endif
