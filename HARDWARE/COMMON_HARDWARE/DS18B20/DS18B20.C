
#include <stdio.h>
#include "DS18B20.H"

sbit DQ = P0 ^ 1;
typedef struct
{
	u8 tempL;//温度低八位
	u8 tempH;//温度高八位
	float Tempera;//温度
	u8 StartState;//运行状态状态
	u8 InitState;//初始化状态
	u16 Integer;//整数部分
	u16 Decimal;//小数部分
}DS18B20;
 
 static void Delay260us()		//@24.000MHz
{
	unsigned char i, j;

	i = 7;
	j = 14;
	do
	{
		while (--j);
	} while (--i);
}

 static void Delay60us()		//@24.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 99;
	do
	{
		while (--j);
	} while (--i);
}

 
 static void Delay750us()		//@24.000MHz
{
	unsigned char i, j;

	i = 18;
	j = 127;
	do
	{
		while (--j);
	} while (--i);
}
static void Delay10us()		//@24.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 57;
	while (--i);
}

static void Delay1us()		//@24.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 3;
	while (--i);
}

static void Delay100us()		//@24.000MHz
{
	unsigned char i, j;

	i = 3;
	j = 82;
	do
	{
		while (--j);
	} while (--i);
}

//读一个字节
static u8 ReadOneChar(void)  			//主机数据线先从高拉至低电平1us以上，再使数据线升为高电平，从而产生读信号
{
    u8 Value = 0x00;
    u16 i;

    DQ = 1;
    Delay10us( );
    for(i=0;i<8;i++)
    {
        Value >>= 1; 
        DQ = 0;// 给脉冲信号
        Delay1us();
        DQ = 1;// 给脉冲信号
        Delay1us();
        if(DQ == 1) Value |= 0x80;
        Delay60us( );
    } 
    return Value;
}

static void WriteOneChar(unsigned char dat)
{
    u16 i;
    
    for(i=0;i<8;i++)
    {
        if((dat & 0x01))
        {
            DQ = 0;
            Delay1us( );
            DQ = 1;
            Delay60us( );
        }
        else
        {
            DQ = 0;
            Delay60us( );
            DQ = 1;
            Delay1us( );
        }
        dat >>= 1;
    }
}
static void Init_DS18B20(void)
{
   u8 Status = 0x00;
    u16 CONT_1 = 0;
    u8 Flag_1 = 1;

    DQ = 1;      //DQ复位
    Delay260us( );  //稍做延时
    DQ = 0;      //单片机将DQ拉低
    Delay750us( );  //精确延时 大于 480us 小于960us
    DQ = 1;      //拉高总线
    while((DQ != 0)&&(Flag_1 == 1)) //等待ds18b20响应，具有防止超时功能
    {                                      //等待约60ms左右
        CONT_1++;
        Delay10us( );
        if(CONT_1 > 16000)Flag_1 = 0;
        Status = DQ;
    }
    DQ = 1;
    Delay100us( );
    
    //return Status;       //返回初始化状态
}
float getDS18B20_Temperature(u8 which)
{
	u8 str[30];
	u16 tempL, tempH,temp;
 	Init_DS18B20(); 					//初始化
	WriteOneChar(0xcc); 				//跳过读序列号的操作
	WriteOneChar(0x44); 				//启动温度转换
 
	Init_DS18B20(); 					//初始化
	WriteOneChar(0xcc); 				//跳过读序列号的操作 
	WriteOneChar(0xbe); 				//读温度寄存器（头两个值分别为温度的低位和高位）
	tempL = ReadOneChar(); 				//读出温度的低位LSB
	tempH = ReadOneChar(); 				//读出温度的高位MSB	
 	temp = (tempH << 8) | tempL;
	return temp*0.0625f;
}
void DS18B20_Init(void)
{
	GPIO_InitTypeDef DS18B20_GPIO;
	DS18B20_GPIO.Mode = GPIO_PullUp;
	DS18B20_GPIO.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P0, &DS18B20_GPIO);

}
