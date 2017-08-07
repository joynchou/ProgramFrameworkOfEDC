/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : stc15_spi.H
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 *
 * 版本代号 : V1.0
 * 修改日期 : 2015-08-29
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
              为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
              视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐
 * Copyright (C), 2013-2015, 刘平（xymbmcu@163.com）/清华大学出版社/STC MCU International Limited
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */
#ifndef __STC15_SPI_H__
#define __STC15_SPI_H__
#include    "../config.h"

sbit 	MISO	=P1^2;
sbit 	MOSI	=P1^3;
sbit	SCK	  =P1^1;
sbit	CE	  =P1^5;
sbit	CSN		=P1^4;
sbit	IRQ		=P1^0;

u8 SPI_RW(u8 uchars);
u8 SPI_Read(u8 reg);
u8 SPI_RW_Reg(u8 reg, u8 value);
u8 SPI_Read_Buf(u8 reg, u8 *pBuf, u8 uchars);
u8 SPI_Write_Buf(u8 reg, u8 *pBuf, u8 uchars);
void setSPIsta(u8 uchars);
u8 getSPIsta();
void setSPIRX_DR(u8 value);
bit getSPIRX_DR();
#endif
