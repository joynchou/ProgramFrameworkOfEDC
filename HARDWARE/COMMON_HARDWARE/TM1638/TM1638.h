#ifndef __TM1638_H__
#define __TM1638_H__

//#include "../../BSP/STC15Fxxxx.H"
#include "../BSP/BSP.H"

#define segA 0x40
#define segB 0x20
#define segC 0x10
#define segD 0x08
#define segE 0x04
#define segF 0x02
#define segG 0x01
#define segDP 0x80

#define ndp0 (segA+segB+segC+segD+segE+segF)
#define ndp1 (segB+segC)
#define ndp2 (segA+segB+segG+segE+segD)
#define ndp3 (segA+segB+segG+segC+segD)
#define ndp4 (segF+segG+segB+segC)
#define ndp5 (segA+segF+segG+segC+segD)
#define ndp6 (segA+segF+segG+segC+segD+segE)
#define ndp7 (segA+segB+segC)
#define ndp8 (segA+segB+segC+segD+segE+segF+segG)
#define ndp9 (segA+segB+segC+segD+segF+segG)
#define ndpA (segA+segB+segC+segE+segF+segG)
#define ndpB (segC+segD+segE+segF+segG)
#define ndpC (segA+segD+segE+segF)
#define ndpD (segB+segC+segD+segE+segG)
#define ndpE (segA+segD+segE+segF+segG)
#define ndpF (segA+segE+segF+segG)
#define wdp0 (segA+segB+segC+segD+segE+segF+segDP)
#define wdp1 (segB+segC+segDP)
#define wdp2 (segA+segB+segG+segE+segD+segDP)
#define wdp3 (segA+segB+segG+segC+segD+segDP)
#define wdp4 (segF+segG+segB+segC+segDP)
#define wdp5 (segA+segF+segG+segC+segD+segDP)
#define wdp6 (segA+segF+segG+segC+segD+segE+segDP)
#define wdp7 (segA+segB+segC+segDP)
#define wdp8 (segA+segB+segC+segD+segE+segF+segG+segDP)
#define wdp9 (segA+segB+segC+segD+segF+segG+segDP)
#define wdpA (segA+segB+segC+segE+segF+segG+segDP)
#define wdpB (segC+segD+segE+segF+segG+segDP)
#define wdpC (segA+segD+segE+segF+segDP)
#define wdpD (segB+segC+segD+segE+segG+segDP)
#define wdpE (segA+segD+segE+segF+segG+segDP)
#define wdpF (segA+segE+segF+segG+segDP)

//引脚定义
sbit	TM1638_DIO=P1^0;
sbit	TM1638_CLK=P1^1;
sbit	TM1638_STB=P1^2;

void setTM1638Write(unsigned char	DATA);	//写数据函数
void setTM1638COM(unsigned char cmd);
unsigned char getButtonNum(void);
unsigned char getTM1638Read(void);
void Init_TM1638(void);
unsigned char ButtonNum(void);
void CloseTM1638Display(void);
void TM1638LedDisplay(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3,
               unsigned char data4,unsigned char data5,unsigned char data6,unsigned char data7);

#endif