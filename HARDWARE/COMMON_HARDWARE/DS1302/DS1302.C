/************************************************************
* 组织名称：
* 文件名称: K:\单片机相关\电子大赛程序框架\HARDWARE\COMMON_HARDWARE\DS1302\DS1302.C
* 作者:
* 版本:
* 日期:     2017/08/04
* 描述:
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
*
***********************************************************/
#include "DS1302.H"


unsigned char time_buf1[8];//空年月日时分秒周,时间设置缓存区
unsigned char time_buf[8]; //空年月日时分秒周，时间写入缓存区


/*************************************************
* 函数名称: Ds1302_Write_Byte
* 描述: 向DS1302写入一字节数据
* 输入: unsigned char addr, unsigned char d
* 返回值: 无
* 其他说明: 最后停止DS1302总线
*************************************************/

void Ds1302_Write_Byte(unsigned char addr, unsigned char d)
{

	unsigned char i;
	RST_SET;

	//写入目标地址：addr
	addr = addr & 0xFE;     //最低位置零
	for (i = 0; i < 8; i++)
	{
		if (addr & 0x01)
		{
			IO_SET;
		}
		else
		{
			IO_CLR;
		}
		SCK_SET;
		SCK_CLR;
		addr = addr >> 1;
	}

	//写入数据：d
	for (i = 0; i < 8; i++)
	{
		if (d & 0x01)
		{
			IO_SET;
		}
		else
		{
			IO_CLR;
		}
		SCK_SET;
		SCK_CLR;
		d = d >> 1;
	}
	RST_CLR;					//停止DS1302总线
}


/*************************************************
* 函数名称: Ds1302_Read_Byte
* 描述: 从DS1302读出一字节数据
* 输入: unsigned char addr
* 返回值: temp
* 其他说明: 读出原始数据
*************************************************/

unsigned char Ds1302_Read_Byte(unsigned char addr)
{

	unsigned char i;
	unsigned char temp;
	RST_SET;

	//写入目标地址：addr
	addr = addr | 0x01;//最低位置高
	for (i = 0; i < 8; i++)
	{

		if (addr & 0x01)
		{
			IO_SET;
		}
		else
		{
			IO_CLR;
		}
		SCK_SET;
		SCK_CLR;
		addr = addr >> 1;
	}

	//输出数据：temp
	for (i = 0; i < 8; i++)
	{
		temp = temp >> 1;
		if (IO_R)
		{
			PrintString1(" high\r\n");
			temp |= 0x80;
		}
		else
		{
		  PrintString1(" low\r\n");

			temp &= 0x7F;
		}
		SCK_SET;
		SCK_CLR;
	}

	RST_CLR;	//停止DS1302总线
	return temp;
}

/*************************************************
* 函数名称: Ds1302_Write_Time
* 描述: 向DS1302写入时钟数据
* 输入: 无
* 返回值: 年，月，日，时，分，秒，周
* 其他说明:空年月日时分秒周,时间设置缓存区
*************************************************/

void Ds1302_Write_Time(void)
{

	unsigned char i, tmp;
	for (i = 0; i < 8; i++)
	{                  //BCD处理
		tmp = time_buf1[i] / 10;
		time_buf[i] = time_buf1[i] % 10;
		time_buf[i] = time_buf[i] + tmp * 16;
	}
	Ds1302_Write_Byte(ds1302_control_add, 0x00);			//关闭写保护 
	Ds1302_Write_Byte(ds1302_sec_add, 0x80);				//暂停 
	Ds1302_Write_Byte(ds1302_charger_add,0xa9);			//涓流充电 

	Ds1302_Write_Byte(shuju_1_add, time_buf[0]);//写入年份前两位至RAM
	Ds1302_Write_Byte(ds1302_year_add, time_buf[1]);		//年 
	Ds1302_Write_Byte(ds1302_month_add, time_buf[2]);	//月 
	Ds1302_Write_Byte(ds1302_date_add, time_buf[3]);		//日  
	Ds1302_Write_Byte(ds1302_hr_add, time_buf[4]);		  //时 
	Ds1302_Write_Byte(ds1302_min_add, time_buf[5]);		//分
	Ds1302_Write_Byte(ds1302_sec_add, time_buf[6]);		//秒
	Ds1302_Write_Byte(ds1302_day_add, time_buf[7]);		//周 
	Ds1302_Write_Byte(ds1302_control_add, 0x80);			//打开写保护 
}

/*************************************************
* 函数名称: Ds1302_Read_Time
* 描述: 从DS1302读出时钟数据
* 输入: 无
* 返回值:time_buf
* 其他说明: 空年月日时分秒周，时间写入缓存区
*************************************************/

void Ds1302_Read_Time(void)
{
	unsigned char i, tmp;


	time_buf[0] = Ds1302_Read_Byte(shuju_1_add);//读出RAM中年份前两位
	time_buf[1] = Ds1302_Read_Byte(ds1302_year_add);		//年 
	time_buf[2] = Ds1302_Read_Byte(ds1302_month_add);		//月 
	time_buf[3] = Ds1302_Read_Byte(ds1302_date_add);		//日 
	time_buf[4] = Ds1302_Read_Byte(ds1302_hr_add);		//时 
	time_buf[5] = Ds1302_Read_Byte(ds1302_min_add);		//分 
	time_buf[6] = (Ds1302_Read_Byte(ds1302_sec_add)) & 0x7F;//秒 
	time_buf[7] = Ds1302_Read_Byte(ds1302_day_add);		//周 


	for (i = 0; i < 8; i++)
	{           //BCD处理
		tmp = time_buf[i] / 16;
		time_buf1[i] = time_buf[i] % 16;
		time_buf1[i] = time_buf1[i] + tmp * 10;
	}
}

/*************************************************
* 函数名称: Ds1302_Init
* 描述: DS1302初始化
* 输入: 无
* 返回值:无
* 其他说明: ds1302模块初始化
*************************************************/

void Ds1302_Init(void)
{
	GPIO_InitTypeDef    GPIO_InitStructure;     //设置管脚
	GPIO_InitStructure.Mode = GPIO_PullUp;
	GPIO_InitStructure.Pin = GPIO_Pin_3 | GPIO_Pin_1 | GPIO_Pin_2 ;   //ds1302
	GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);
	RST_CLR;			//RST脚置低
	delay_us(50);
	SCK_CLR;			//SCK脚置低
	delay_us(50);
	Ds1302_Write_Byte(ds1302_sec_add, 0x00);
}

