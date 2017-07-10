#include "LCD1602.h"

void LCD1602_GPIO_config()
{
	P5M1 &= ~(1<<4);		//设置P5.4为推挽输出
	P5M0 |= (1<<4);

	P5M1 &= ~(1<<0);		//设置P5.0为准双向IO
	P5M0 &= ~(1<<0);

	P5M1 &= ~(1<<1);		//设置P5.1为准双向IO
	P5M0 &= ~(1<<1);

	P5M1 &= ~(1<<2);		//设置P5.2为准双向IO
	P5M0 &= ~(1<<2);

	P4M1 = 0X00;		//设置P4为准双向IO
	P4M0 = 0X00;
}

//****************************************************
//写指令
//****************************************************
void LCD1602_write_com(unsigned char com)
{
	LCD1602_RS = 0;
	delay_ms(1);
	LCD1602_EN = 1;
	LCD1602_PORT = com;
	delay_ms(1);
	LCD1602_EN = 0;
}

//****************************************************
//写数据
//****************************************************
void LCD1602_write_data(unsigned char dat)
{
	LCD1602_RS = 1;
	delay_ms(1);	
	LCD1602_PORT = dat;
	LCD1602_EN = 1;
	delay_ms(1);
	LCD1602_EN = 0;
}

//****************************************************
//连续写字符
//****************************************************
void LCD1602_write_word(unsigned char *s)
{
	while(*s>0)
	{
		LCD1602_write_data(*s);
		s++;
	}
}

void Init_LCD1602()
{
	LCD1602_GPIO_config();
	LCD1602_Backlight = 1;	//打开背光


	LCD1602_EN = 0;
	LCD1602_RW = 0;						//设置为写状态
	LCD1602_write_com(0x38);			//显示模式设定
	LCD1602_write_com(0x0c);			//开关显示、光标有无设置、光标闪烁设置
	LCD1602_write_com(0x06);			//写一个字符后指针加一
	LCD1602_write_com(0x01);			//清屏指令
}


