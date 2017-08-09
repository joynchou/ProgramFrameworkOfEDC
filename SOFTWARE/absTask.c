#include <stdlib.h>
#include "TASK/task.h"
#define TEMPERATURE_UPDATE  15 
#define BUTTON_SCAN 14
#define TIME_UPDATE 13
#define BUTTON_SOUND 12
void taskStart() _task_ 0
{
	setup();
	blink(3);
	os_create_task(5);
	os_create_task(BUTTON_SCAN);
	os_create_task(BUTTON_SOUND);
	//	os_create_task(TEMPERATURE_UPDATE);
	//	os_create_task(TIME_UPDATE);
	os_delete_task(0);

}
void printDistance(void) _task_ 5
{
	for (;;)
	{
		DataScope_Get_Channel_Data(getADS1115ConvsionData(CHANNEL_1), 1);

		sendScopeData(1);
		os_wait(K_TMO, 30, 0);
	}
}
void printTmp()  _task_  9
{
	for (;;)
	{
		getDS18B20_Temperature(0);
		//		DataScope_Get_Channel_Data(getDS18B20_Temperature(0));
		//		sendScopeData(1);
		os_wait(K_TMO, 30, 0);
	}
}
void Distance(void)  _task_ 10
{
#define TIME 130

	float value;
	float actValue;
	float Data[TIME + 1];
	float time = 0;
	float distance = 0;

	u8 i = 0;
	for (;;)
	{
		for (i = 0; i < TIME; i++)
		{
			updateDistance(HC_SR04_1);
			os_wait(K_TMO, 4, 0);
			actValue = (float)getTimerValue(HC_SR04_1);//ԭʼ����
			value = limitingFilter(actValue, 30000UL);//�޷��˲�
			value = shudderingFilter(value, 300);//�����˲�
			value = movingAverageFilter(value);//����ƽ���˲�
			Data[i] = value;
		}
		Data[TIME] = filter(Data, TIME, 65535, 0);//��λֵƽ���˲�
		time = Data[TIME] * 4.166667e-6;//��ʽ��time�ĵ�λΪms����24mzh��
		distance = (time * (331.4f + 0.607*getDS18B20_Temperature(0))) / 20;
		setDistance(HC_SR04_1, distance);
		DataScope_Get_Channel_Data(distance, 1);
		sendScopeData(1);
		os_wait(K_TMO, 100, 0);

		//for (i = 0; i < TIME; i++)
		//{
		//	updateDistance(US_016_1);
		//	os_wait(K_TMO, 4, 0);
		//	actValue = (float)getTimerValue(US_016_1);//ԭʼ����
		//	value = limitingFilter(actValue, 30000UL);//�޷��˲�
		//	value = shudderingFilter(value, 300);//�����˲�
		//	value = movingAverageFilter(value);//����ƽ���˲�
		//	Data[i] = value;
		//}
		//Data[TIME] = filter(Data, TIME, 65535, 0);//��λֵƽ���˲�
		//distance = Data[TIME]*0.015625f;
		//setDistance(US_016_1, distance);
		//DataScope_Get_Channel_Data(distance, 1);
	//	sendScopeData(1);
		//os_wait(K_TMO, 100, 0);

	}
}
//ʱ����½��̣�Ƶ��5hz
void TimeUpdate(void) _task_ TIME_UPDATE
{
	for (;;)
	{

		os_wait(K_IVL, 200, 0);
	}
}
//�¶ȼ���ֵ���½��̣�Ƶ��10hz
void  TemperatureUpdata(void) _task_ TEMPERATURE_UPDATE
{
	for (;;)
	{


		os_wait(K_IVL, 100, 0);

	}
}
//���̰������������̣�Ƶ��50hz
void ButtonSound(void) _task_ BUTTON_SOUND
{
	for (;;)
	{
		if (getButtonNum())
		{
			buzzWait();
		}
		os_wait(K_IVL, 20, 0);
	}

}
//����ɨ����̣�50hz
void ButtonStateUpdate(void) _task_ BUTTON_SCAN
{
	for (;;)
	{
		buttonScan();


		os_wait(K_IVL, 20, 0);

	}

}

