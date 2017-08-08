/************************************************************
* ��֯���ƣ�
* �ļ�����: HARDWARE\COMMON_HARDWARE\HC_SR04\HC_SR04.C
* ����:
* �汾:
* ����:     2017/08/05
* ����:
* ��ʷ�޸ļ�¼:
* <����> <ʱ��> <�汾 > <����>
*
***********************************************************/
#define ext0Disable() EX0 = 0
#define ext0Able() EX0 = 1

//#define DEBUG
#include "hc_sr04.h"
#include <stdio.h>
#include "../SOFTWARE/TASK/COMMON_SOFTWARE/ALGORITHM/DIGITAL_FILTER/FILTER/FILTER.H"
#include "../ADS1115/ADS1115.H"
typedef struct
{
	double distance;
	u8 state;
	u16 timerValue;

}HC_SR04;
static HC_SR04 ultrasonic[2];
static u8 extiBit = 0;
u8 str[20];
void ultrasonicInit(void)
{
	GPIO_InitTypeDef ultrasonic_GPIO;
	EXTI_InitTypeDef  hc_sr04_EXTI;
	ultrasonic_GPIO.Mode = GPIO_PullUp;
	ultrasonic_GPIO.Pin = GPIO_Pin_3;
	GPIO_Inilize(GPIO_P3, &ultrasonic_GPIO);
	ultrasonic_GPIO.Mode = GPIO_HighZ; //�ⲿ�ж�Ҫʹ�����ģʽ
	ultrasonic_GPIO.Pin = GPIO_Pin_2;
	GPIO_Inilize(GPIO_P3, &ultrasonic_GPIO);
	hc_sr04_EXTI.EXTI_Interrupt = ENABLE;
	hc_sr04_EXTI.EXTI_Mode = EXT_MODE_RiseFall;
	hc_sr04_EXTI.EXTI_Polity = PolityHigh;
	Ext_Inilize(EXT_INT0, &hc_sr04_EXTI);
	P32 = 0;//���ų�ʼ��
	P33 = 0;//���ų�ʼ��

}



//************************************
// Method:    open_HC_SR04
// FullName:  open_HC_SR04
// Access:    public 
// Returns:   void
// Qualifier: �򿪴�ģ��Ŀ���
// Parameter: u8 num
//************************************
void open_Ultrasonic(u8 num)
{

	ultrasonic[num].state = ON;


}
void close_Ultrasonic(u8 num)
{
	ultrasonic[num].state = OFF;
}
u8 getUltrasonicState(u8 num)
{
	return ultrasonic[num].state;

}
void setTimerValue(u8 num, u16 value)
{
	ultrasonic[num].timerValue = value;
}
void setDistance(u8 num,float value)
{
	ultrasonic[num].distance = value;
}
//************************************
// Method:    getTimerValue
// FullName:  getTimerValue
// Access:    public 
// Returns:   u16
// Qualifier: �����ԭʼ�ĸߵ�ƽʱ�䣬��λms
// Parameter: u8 num
//************************************
u16 getTimerValue(u8 num)
{
	return ultrasonic[num].timerValue;

}
//************************************
// Method:    updateDistance
// FullName:  updateDistance
// Access:    public 
// Returns:   void
// Qualifier: ��������и��¾���
// Parameter: u8 num
//************************************
void updateDistance(u8 num)
{
	static double time;//��Ӧʱ������λms
	if (!ultrasonic[num].state)
	{
		return ;
	}
	if (num==HC_SR04_1)
	{
		ext0Able();

		Trig = HIGH;//���������ź�
		delay_us(5);//�˺�����̫׼��3usʵ�ʴ��
		Trig = LOW;
	}
	else if (num == US_016_1)
	{
		ultrasonic[US_016_1].timerValue = getADS1115ConvsionData(CHANNEL_1);
		delay_us(5);//�˺�����̫׼��3usʵ�ʴ��
	}
	else
	{

	}
 }
//************************************
// Method:    getdistance
// FullName:  getdistance
// Access:    public 
// Returns:   float
// Qualifier: //��ȡ����������,��λcm,ԭʼ���ݣ�
// Parameter: u8 num
//************************************
double getdistance(u8 num)//��ȡ����������
{

 
	return ultrasonic[num].distance;//���û�и��������򷵻���һ�θ��µ�ֵ�����򷵻����ֵ
}
/********************* INT0�жϺ��� *************************/
static void Ext_INT0(void) interrupt INT0_VECTOR		//���ж�ʱ�Ѿ������־
{

	//u8 timerValueL, timerValueH;
#ifdef DEBUG
		//PrintString1("into\r\n");
#endif
	//delay_us(1);
	if (INT0 == RISING_EDGE)//������
	{
		Timer4_Run();//��ʼ��ʱ
		extiBit = LOW;
#ifdef DEBUG
		PrintString1("rising edge\r\n");
#endif

	}
	else if (INT0 == FALLING_EDGE)//�½���
	{

		Timer4_Stop();
		ultrasonic[0].timerValue = TH4;
		ultrasonic[0].timerValue = ultrasonic[0].timerValue * 256 + TL4;
#ifdef DEBUG
		USART1_printf("valueL is %d\r\n", (u16)TL4);
		USART1_printf("valueH is %d\r\n", (u16)TH4);
		sprintf(str, "value is %u\r\n", TH4 * 256 + TL4);
		PrintString1(str);
#endif  		
		TH4 = 0;
		TL4 = 0;
		extiBit = OK;//������׼����

	}
	else
	{
		extiBit = LOW;
		Timer4_Stop();

#ifdef DEBUG
		PrintString1("error\r\n");
#endif
	}
	//	ext0Disable();

}
