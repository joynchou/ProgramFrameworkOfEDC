#include "PHOTOELECTRIC.H"

typedef struct//光电模块结构体
{
	u8 state;//光电门的状态，是否有数字量，是为1，否为0
	u8 switcher;//光电门使能开关
}PhotoElectricModular;

static PhotoElectricModular s_PhotoEle[PHOTOELE_NUM];

/*************************************************
 *函数名称：void openPhotoEleMod(u8 PHOTOELE_N)
 *参数：u8 PHOTOELE_N：光电设备的编号
 *返回值：无
 *作用：启用指定的光电设备
 *************************************************/
void openPhotoEleMod(u8 PHOTOELE_N)
{
	s_PhotoEle[PHOTOELE_N].switcher = ON;
}

/*************************************************
 *函数名称：void openPhotoEleMod(u8 PHOTOELE_N)
 *参数：u8 PHOTOELE_N：光电设备的编号
 *返回值：无
 *作用：禁用指定的光电设备
 *************************************************/
void closePhotoEleMod(u8 PHOTOELE_N)
{
	s_PhotoEle[PHOTOELE_N].switcher = OFF;
	s_PhotoEle[PHOTOELE_N].state = 0;
}

/*************************************************
 *函数名称：void openAllPhotoEleMod()
 *参数：无
 *返回值：无
 *作用：启用所有光电设备
 *************************************************/
void openAllPhotoEleMod()
{
	u8 i;
	for(i = 0;i < PHOTOELE_NUM;i++)
	{
		s_PhotoEle[i].switcher = ON;
	}
}

/*************************************************
 *函数名称： void closeAllPhotoEleMod()
 *参数：无
 *返回值：无
 *作用：禁用所有光电设备
 *************************************************/
void closeAllPhotoEleMod()
{
	u8 i;
	for(i = 0;i < PHOTOELE_NUM;i++)
	{
		s_PhotoEle[i].switcher = OFF;
		s_PhotoEle[i].state = 0;
	}
}

/*************************************************
 *函数名称：u8 getPhotoEleState(u8 PHOTOELE_N)
 *参数：u8 PHOTOELE_N：光电设备的编号
 *返回值：unsigned char
 *作用：返回指定的光电设备的状态
 *************************************************/
u8 getPhotoEleState(u8 PHOTOELE_N)
{
	return s_PhotoEle[PHOTOELE_N].state;
}

/*************************************************
 *函数名称：u8 getNightEleState(void)
 *参数：无
 *返回值：unsigned char类型
 *作用：返回所使用的光电设备的状态
 *************************************************/
u8 getNightEleState(void)
{
	u8 EleState = 0,i;
	for(i = PHOTOELE_NUM;i >= 0;i--)
	{
		if(s_PhotoEle[i].state == 1)
		{	
			EleState <<= 1;
			EleState |= 0x01;
		}
	}
	return EleState;
}

/*************************************************
 *函数名称：void PhotoElectricScan(void)
 *参数：无
 *返回值：无
 *作用：光电设备状态扫描
 *************************************************/
void PhotoElectricScan(void)
{
	if(ELECTRTIC_1 == 0 && (s_PhotoEle[PHOTOELE_1].switcher == ON))
	{
		s_PhotoEle[PHOTOELE_1].state = 1;
	}
		else
	{
		s_PhotoEle[PHOTOELE_1].state = 0;
	}
	if(ELECTRTIC_2 == 0 && (s_PhotoEle[PHOTOELE_2].switcher == ON))
	{
		s_PhotoEle[PHOTOELE_2].state = 1;
	}
		else
	{
		s_PhotoEle[PHOTOELE_2].state = 0;
	}
	if(ELECTRTIC_3 == 0 && (s_PhotoEle[PHOTOELE_3].switcher == ON))
	{
		s_PhotoEle[PHOTOELE_3].state = 1;
	}
		else
	{
		s_PhotoEle[PHOTOELE_3].state = 0;
	}
	if(ELECTRTIC_4 == 0 && (s_PhotoEle[PHOTOELE_4].switcher == ON))
	{
		s_PhotoEle[PHOTOELE_4].state = 1;
	}
		else
	{
		s_PhotoEle[PHOTOELE_4].state = 0;
	}
	if(ELECTRTIC_5 == 0 && (s_PhotoEle[PHOTOELE_5].switcher == ON))
	{
		s_PhotoEle[PHOTOELE_5].state = 1;
	}
		else
	{
		s_PhotoEle[PHOTOELE_5].state = 0;
	}
	if(ELECTRTIC_6 == 0 && (s_PhotoEle[PHOTOELE_6].switcher == ON))
	{
		s_PhotoEle[PHOTOELE_6].state = 1;
	}
		else
	{
		s_PhotoEle[PHOTOELE_6].state = 0;
	}
	if(ELECTRTIC_7 == 0 && (s_PhotoEle[PHOTOELE_7].switcher == ON))
	{
		s_PhotoEle[PHOTOELE_7].state = 1;
	}
		else
	{
		s_PhotoEle[PHOTOELE_7].state = 0;
	}
	if(ELECTRTIC_8 == 0 && (s_PhotoEle[PHOTOELE_8].switcher == ON))
	{
		s_PhotoEle[PHOTOELE_8].state = 1;
	}
		else
	{
		s_PhotoEle[PHOTOELE_8].state = 0;
	}
	delay_ms(20);
}