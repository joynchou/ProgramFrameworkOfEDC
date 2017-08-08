/************************************************************
* ��֯���ƣ�
* �ļ�����: K:\��Ƭ�����\���Ӵ���������\SOFTWARE\TASK\SETUP.C
* ����:     �ܳ���
* �汾:
* ����:     2017/07/18
* ����:		��ʼ�������Ͳ�������ʹ��
* ��ʷ�޸ļ�¼:
* <����> <ʱ��> <�汾 > <����>
*
***********************************************************/

#include "setup.h"

/*************  ����1��ʼ������ *****************/
/*************************************************
* ��������: void    UART1_init(unsigned long BandRate)
* ����: ����1��ʼ������
* ����: unsigned long BandRate �����ڵĲ����ʣ�������ֵ�����ĸ"L"����ֹ������
* ���: ���ô˺����ᷢ��һ�β������ �� STC15w4k58s4 UART1 is open ��
* ����ֵ: ��
* ����˵��: ��
*************************************************/
void    UART1_init(unsigned long BandRate)
{
	COMx_InitDefine     COMx_InitStructure;
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx;
	COMx_InitStructure.UART_BRT_Use = BRT_Timer1;
	COMx_InitStructure.UART_BaudRate = BandRate;
	COMx_InitStructure.UART_RxEnable = ENABLE;
	COMx_InitStructure.BaudRateDouble = DISABLE;
	COMx_InitStructure.UART_Interrupt = ENABLE;
	COMx_InitStructure.UART_Polity = PolityHigh;
	COMx_InitStructure.UART_P_SW = UART1_SW_P30_P31;
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;
	USART_Configuration(USART1, &COMx_InitStructure);
	PrintString1("STC15w4k58s4's UART1 is open \r\n");   //���ڲ���
}
void test(void)//��������
{

}
void setup(void)
{

	UART1_init(9600);
	timerInit();
	Board_LED_Init();
	LCD5510_Init();
	Button_config();
	Speaker_Init();
	ADS1115_Config();
	ultrasonicInit();
	DS18B20_Init();
	LCD_printsl(0, 0, "Hello!");
	os_wait(K_TMO, 250, 0);
	os_wait(K_TMO, 250, 0);
	os_wait(K_TMO, 250, 0);
	os_wait(K_TMO, 250, 0);
	LCD_clr_scr();
	//InitJY901(JY901_1);
	//EnableJY901(JY901_1);
	//openJY901SbufMode(JY901_1);
	//ADC_config(ADC_P10, ADC_540T);
	open_Ultrasonic(HC_SR04_1);
	open_Ultrasonic(US_016_1);
	open_ADS1115(CHANNEL_1);
	open_ADS1115(CHANNEL_2);
 	// test();

}

