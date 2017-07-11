/************************************************************
* 组织名称：
* 文件名称: K:\单片机相关\电子大赛程序框架\HARDWARE\DEVICES\COMMON_DEVICES\74H\74HC595.C
* 作者:     
* 版本:    
* 日期:     2017/07/10
* 描述: 595的驱动程序
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
* 
***********************************************************/

#include "74HC595.H"
void HC595_Init()
{

}
void HC595SendData(unsigned char SendVal)
{
	unsigned char i;
	for (i = 0; i < 8; i++)
	{
		if ((SendVal << i) & 0x80)
		{	
			MOSIO_HIGH;
		}
		else
		{
			MOSIO_LOW;
		}	
		S_CLK_LOW;
		NOP2();
		S_CLK_HIGH;
	}
	R_CLK_LOW;
	NOP2();
	R_CLK_HIGH;
}