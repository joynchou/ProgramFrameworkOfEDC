/************************************************************
* 组织名称： (C), 1988-1999, Tech. Co., Ltd.
* 文件名称: test.cpp
* 作者:
* 版本 :
* 日期:
* 描述: // 模块描述
* 主要函数及其功能 : // 主要函数及其功能
  1. -------
* 历史修改记录: // 历史修改记录
* <作者> <时间> <版本 > <描述>
* David 96/10/12 1.0 build this moudle
***********************************************************/
//------------------------------------------------
//头文件
#include "stc15_spi.h"
#include "../DELAY/DELAY.H"

static u8 	bdata sta;   //状态标志
sbit	RX_DR	=sta^6;
sbit	TX_DS	=sta^5;
sbit	MAX_RT	=sta^4;

/****************************************************************************************************
/*函数：uint SPI_RW(uint uchar)
/*功能：NRF24L01的SPI写时序
/****************************************************************************************************/
u8 SPI_RW(u8 uchars)
{
	u8 bit_ctr;
  for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
 	{
		MOSI = (uchars & 0x80);         // output 'uchar', MSB to MOSI
		uchars = (uchars << 1);           // shift next bit into MSB..
		SCK = 1;                      // Set SCK high..
		uchars |= MISO;       		  // capture current MISO bit
		SCK = 0;            		  // ..then set SCK low again 
	}
  return(uchars);           		  // return read uchar
}
/****************************************************************************************************
/*函数：uchar SPI_Read(uchar reg)
/*功能：NRF24L01的SPI时序
/****************************************************************************************************/
u8 SPI_Read(u8 reg)
{
	u8 reg_val;
	
	CSN = 0;                // CSN low, initialize SPI communication...
	SPI_RW(reg);            // Select register to read from..
	reg_val = SPI_RW(0);    // ..then read registervalue
	CSN = 1;                // CSN high, terminate SPI communication
	
	return(reg_val);        // return register value
}
/****************************************************************************************************/
/*功能：NRF24L01读写寄存器函数
/****************************************************************************************************/
u8 SPI_RW_Reg(u8 reg, u8 value)
{
	u8 status;
	
	CSN = 0;                   // CSN low, init SPI transaction
	status = SPI_RW(reg);      // select register
	SPI_RW(value);             // ..and write value to it..
	CSN = 1;                   // CSN high again
	
	return(status);            // return nRF24L01 status uchar
}
/****************************************************************************************************/
/*函数：uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*功能: 用于读数据，reg：为寄存器地址，pBuf：为待读出数据地址，uchars：读出数据的个数
/****************************************************************************************************/
u8 SPI_Read_Buf(u8 reg, u8 *pBuf, u8 uchars)
{
	u8 status,uchar_ctr;
	
	CSN = 0;                    		// Set CSN low, init SPI tranaction
	status = SPI_RW(reg);       		// Select register to write to and read status uchar
	
	for(uchar_ctr=0;uchar_ctr<uchars;uchar_ctr++)
		pBuf[uchar_ctr] = SPI_RW(0);    // 
	
	CSN = 1;                           
	
	return(status);                    // return nRF24L01 status uchar
}
/*********************************************************************************************************
/*函数：uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*功能: 用于写数据：为寄存器地址，pBuf：为待写入数据地址，uchars：写入数据的个数
/*********************************************************************************************************/
u8 SPI_Write_Buf(u8 reg, u8 *pBuf, u8 uchars)
{
	u8 status,uchar_ctr;
	
	CSN = 0;            //SPI使能       
	status = SPI_RW(reg);
	delay_us(10);	
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //
		SPI_RW(*pBuf++);
	CSN = 1;           //关闭SPI
	return(status);    // 
}

void setSPIsta(u8 uchars)
{
	sta = uchars;
}

u8 getSPIsta()
{
	return sta;
}

void setSPIRX_DR(u8 value)
{
	RX_DR = value;
}

bit getSPIRX_DR()
{
	return RX_DR;
}