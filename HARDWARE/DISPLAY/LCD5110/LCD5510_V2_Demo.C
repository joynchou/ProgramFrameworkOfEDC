/*--------------------------------------------------------------*/
#include <AT89X52.H>
#include "Font_code.c"
#include "LCD5510_V2.H"


unsigned char code *str1 = {"Nokia 5510 Test, Haha^_^ I am so glad to see you agian! Do you think so?"};
unsigned char code *str2 = {"I Love You AVR"};

/*--------------------------------------------------------------*/
//延时250000+1us 函数定义
void delay250ms(void)
{
    unsigned char i,j,k;
    for(i=251;i>0;i--)
    for(j=3;j>0;j--)
    for(k=164;k>0;k--);
}

//延时1000000+1us 函数定义
void delay1s(void)
{
    unsigned char i,j,k;
    for(i=167;i>0;i--)
    for(j=171;j>0;j--)
    for(k=16;k>0;k--);
}


/*--------------------------------------------------------------*/
//主函数
void main(void)
{
	unsigned char i, j, k;
	unsigned char LCD_contrast = 0xc8;

	LCD5510_Init();

	while(*str1)
	{
		LCD_prints(0, 0, str1++); 
		delay250ms(); i++;
		LCD_clr_row(0);
	}
	str1 -= i;
	LCD_printsl(0, 0, str1);

	delay1s(); delay1s();
	LCD_clr_scr();		//清屏
	for(i = 0; i < 14; i++) {LCD_printc(i, 2, str2[i]); delay250ms();}

	delay1s();
	LCD_prints(0, 3, ">--(*^_^*)--<");
	delay1s();

	LCD_prints(0, 0, "Blank Test ");
	delay1s();
	LCD_show_blank;		//空白测试
	delay1s();
	LCD_prints(0, 0, "Normal Test");
	LCD_show_normal;	//恢复正常
	delay1s();
	LCD_prints(0, 0, "Black Test ");
	delay1s();
	LCD_show_black;		//全黑检测坏点
	delay1s();
	LCD_show_normal;	//恢复正常
	delay1s();
	LCD_prints(0, 0, "Inverse Test");
	LCD_show_inverse;	//反色
	delay1s();
	LCD_prints(0, 0, "Normal again");
	LCD_show_normal;	//恢复正常
	delay1s();
	LCD_clr_scr();		//清屏
	delay1s();
	
	i = 0; j = 0; k =0;
	while(k++ < 101)	//ASCII字符测试
	{ 
		LCD_printc(i, j, k + 32); 
		delay250ms(); 
		i++; if(i == 14) {i = 0; j++;}
		if(j == 6) j = 0;
	}
	
	LCD_prints(2, 1, "Alexi2008");
	while(1)				//对比度软件调节
	{
		LCD_write_cmd(0x23);//工作模式, 水平寻址, 扩展指令	

		for(i = 0; i < 10; i++) {LCD_contrast++; LCD_write_cmd(LCD_contrast); delay250ms();}
		for(i = 0; i < 20; i++) {LCD_contrast--; LCD_write_cmd(LCD_contrast); delay250ms();}
		for(i = 0; i < 10; i++) {LCD_contrast++; LCD_write_cmd(LCD_contrast); delay250ms();}
	}
}

