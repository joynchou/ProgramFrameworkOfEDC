#include "RTC.H"

typedef struct
{
	u16 second;//秒
	u16 minute;//分
	u16 hour;	 //时
	u16 week;  //星期
	u16 day;   //日期
	u16 month; //月份
	u16 year;  //年份
}TimerClock;

static TimerClock s_RTC_Time;
/**************************************************************
 *函数：u8 Read_RTC_Date(u8 address,u8 date)
 *作用：读取单个地址的数据
 **************************************************************/
u8 Read_RTC_Date(u8 address,u8 date)
{
	u8 value;
	InputOneByte(address | IIC_WRITE);
	IIC_RdAck();
	InputOneByte(date);
	IIC_RdAck();
	InputOneByte(address | IIC_READ);
	IIC_RdAck();
	value = OutputOneByte();
	IIC_Nack();
	IIC_Stop();
	return value;
}

/**************************************************************
 *函数：u8 Write_RTC_Date(u8 date)
 *作用：写命令
 **************************************************************/
void Write_RTC_Date(u8 date)
{
	IIC_WrDevAddAndDatAdd(DS1307_ADDRESS | IIC_WRITE,DS1307_CONTROL);
	InputOneByte(date);
	IIC_RdAck();
	IIC_Stop();
}

/**************************************************************
 *函数：u8 *Read_RTC_Time(u8 address)
 *作用：读取时间的数据
 **************************************************************/
u8 get_RTC_Time(u8 address,u8 *Time)
{
	u8 i;
	IIC_Start();
	InputOneByte(address | IIC_READ);
	IIC_RdAck();
	for(i = 0;i < 7;i++)
	{	
		Time[i] = OutputOneByte();	
		IIC_Ack();
	}
	IIC_Nack();
	IIC_Stop();
//	return Time;
}

