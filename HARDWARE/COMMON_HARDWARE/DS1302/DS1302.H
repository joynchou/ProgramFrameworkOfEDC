/************************************************************
* 组织名称：
* 文件名称: K:\单片机相关\电子大赛程序框架\HARDWARE\COMMON_HARDWARE\DS1302\DS1302.H
* 作者:
* 版本:
* 日期:     2017/08/04
* 描述:
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
*
***********************************************************/
#ifndef _DS1302_H_
#define _DS1302_H_
#include "../BSP/BSP.H"

sbit DS_SCK = P1 ^ 1;
sbit DS_SDA = P1 ^ 3;
sbit RST = P1 ^ 2;
//复位脚
#define RST_CLR	RST=0//电平置低
#define RST_SET	RST=1//电平置高


//双向数据
#define IO_CLR	DS_SDA=0//电平置低
#define IO_SET	DS_SDA=1//电平置高
#define IO_R	DS_SDA  //电平读取


//时钟信号
#define DS_SCK_CLR	DS_SCK=0//时钟信号
#define DS_SCK_SET	DS_SCK=1//电平置高


#define ds1302_sec_add			0x80		//秒数据地址
#define ds1302_min_add			0x82		//分数据地址
#define ds1302_hr_add			0x84		//时数据地址
#define ds1302_date_add			0x86		//日数据地址
#define ds1302_month_add		0x88		//月数据地址
#define ds1302_day_add			0x8a		//星期数据地址
#define ds1302_year_add			0x8c		//年数据地址
#define ds1302_control_add		0x8e		//控制数据地址
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe

#define shuju_1_add 0xc0
#define shuju_2_add 0xc2
#define shuju_3_add 0xc4

//内部ＲＡＭ地址0xc0,0xc2,0xc4.....0xfc都是8位存储空间;0xfe存储字符

extern unsigned char time_buf1[8];//空年月日时分秒周
extern unsigned char time_buf[8];//空年月日时分秒周

 /*************************************************
 * 函数名称: Ds1302_Write_Byte
 * 描述: 向DS1302写入一字节数据
 * 输入: unsigned char addr, unsigned char d
 * 返回值: 无
 * 其他说明: 最后停止DS1302总线
 *************************************************/
void Ds1302_Write_Byte(unsigned char addr, unsigned char d);

/*************************************************
* 函数名称: Ds1302_Read_Byte
* 描述: 从DS1302读出一字节数据
* 输入: unsigned char addr
* 返回值: temp
* 其他说明: 读出原始数据
*************************************************/
unsigned char Ds1302_Read_Byte(unsigned char addr);

/*************************************************
* 函数名称: Ds1302_Write_Time
* 描述: 向DS1302写入时钟数据
* 输入: 无
* 返回值: 年，月，日，时，分，秒，周
* 其他说明: 无
*************************************************/
void Ds1302_Write_Time(void);

/*************************************************
* 函数名称: Ds1302_Read_Time
* 描述: 从DS1302读出时钟数据
* 输入: 无
* 返回值:time_buf
* 其他说明: time_buf数组中分别是{年，月，日，时，分，秒，周}
*************************************************/
void Ds1302_Read_Time(void);

/*************************************************
* 函数名称: Ds1302_Init
* 描述: DS1302初始化
* 输入: 无
* 返回值:无
* 其他说明: ds1302模块初始化
*************************************************/
void Ds1302_Init(void);


#endif
