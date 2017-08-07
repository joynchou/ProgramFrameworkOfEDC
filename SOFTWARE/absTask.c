#include <stdlib.h>
#include "TASK/task.h"
void taskStart() _task_ 0
{
	setup();
	blink(4);
 	os_create_task(12);

	os_delete_task(0);

}
void printAngleData(void) _task_ 1
{
	for (;;)
	{
		DataScope_Get_Channel_Data(getJY901Angle(JY901_1, X), 1);
		DataScope_Get_Channel_Data(getJY901Angle(JY901_1, Y), 2);
		DataScope_Get_Channel_Data(getJY901Angle(JY901_1, Z), 3);
		sendScopeData(3);
		os_wait(K_TMO, 30, 0);
	}
}
void dataUpdate(void) _task_ 2
{
	for (;;)
	{
		LCD_printNum_I(0, 0, (int)getJY901Angle(JY901_1, X), 4);
		LCD_printNum_I(0, 1, (int)getJY901Angle(JY901_1, Y), 4);
		LCD_printNum_I(0, 2, (int)getJY901Angle(JY901_1, Z), 4);
		os_wait(K_TMO, 30, 0);

	}

}
void printADS1115(void) _task_ 3
{
	for (;;)
	{
		DataScope_Get_Channel_Data(getADS1115ConvsionData(CHANNEL_1), 1);
		DataScope_Get_Channel_Data(getADS1115ConvsionData(CHANNEL_2), 2);
		DataScope_Get_Channel_Data(getADS1115ConvsionData(CHANNEL_3), 3);
		DataScope_Get_Channel_Data(getADS1115ConvsionData(CHANNEL_4), 4);
		sendScopeData(4);
		os_wait(K_TMO, 30, 0);

	}

}
void Buzz(void) _task_ 8
{
	for (;;)
	{

		if (getButtonState(BUTTON3))
		{
			buzz(2000, 200);

		}
		if (getButtonState(BUTTON4))
		{
			buzzSucceed();
		}
		if (getButtonState(BUTTON5))
		{
			buzzFailed();
		}
		os_wait(K_TMO, 10, 0);
	}

}
void aButtonScan(void) _task_ 4
{
	for (;;)
	{
		buttonScan();


		os_wait(K_TMO, 5, 0);

	}

}
void printfButton(void) _task_ 7
{
	for (;;)
	{
		if (getButtonState(BUTTON1))
		{
			LCD_printsl(0, 1, "button 1");
			os_wait(K_TMO, 200, 0);
			LCD_clr_scr();

		}
		if (getButtonState(BUTTON2))
		{
			LCD_printsl(0, 1, "button 2 ");
			os_wait(K_TMO, 200, 0);
			LCD_clr_scr();

		}
		os_wait(K_TMO, 5, 0);
	}
}
void printDistance(void) _task_ 5
{
	for (;;)
	{
		DataScope_Get_Channel_Data(getdistance(HC_SR04_1), 1);

		sendScopeData(1);
		os_wait(K_TMO, 30, 0);
	}
}
void distanceUpdata(void) _task_ 6
{
	float time = 0;
	float distance = 0;
#define TIME 30
	u8 i = 0;
	float Data[TIME + 1];
	for (;;)
	{
		//	for (i = 0; i < TIME; i++)
		{
			updateDistance(HC_SR04_1);
			os_wait(K_TMO, 4, 0);
			//		Data[i] = getTimerValue(HC_SR04_1);
		}
		//Data[TIME] = filter(Data, TIME, 65535.0, 0);
		Data[TIME] = KalmanFilter((double)getTimerValue(HC_SR04_1), 0.00001f, 3.0f, 1);
		time = Data[TIME] * 4.166667e-6;//公式，time的单位为ms，在24mzh下

		distance = (time * 340.0f) / 2;

		setDistance(HC_SR04_1, distance);


	}
}
void Distance(void)  _task_ 12
{
	float value;
	float actValue;
	float Data[21];
	u8 i = 0;
	for (;;)
	{
		for (i = 0; i < 20; i++)
		{
			updateDistance(HC_SR04_1);
			os_wait(K_TMO, 4, 0);
			actValue = (float)getTimerValue(HC_SR04_1);//原始数据
			value = limitingFilter(actValue, 6000);
			value = shudderingFilter(value, 120);
			value = movingAverageFilter(value);
			Data[i] = value;
		}
		Data[20] = filter(Data, 20, 65535, 0);
			DataScope_Get_Channel_Data(actValue, 1);
			DataScope_Get_Channel_Data(Data[20], 2);
			DataScope_Get_Channel_Data(actValue* 4.166667e-6* 340.0f / 2, 3);
			DataScope_Get_Channel_Data(Data[20] * 4.166667e-6* 340.0f / 2, 4);
			sendScopeData(4);
		
		os_wait(K_TMO, 30, 0);

	}
}
void ButtonSound(void) _task_ 10
{
	for (;;)
	{
		if (getButtonNum())
		{
			buzzWait();
		}
		os_wait(K_TMO, 5, 0);
	}

}
