#include <stdlib.h>
#include "TASK/task.h"
void taskStart() _task_ 0
{ 
	setup();
	blink(4);
	//os_create_task(1);
	os_create_task(3);
	os_delete_task(0);
	
}
void printAngleData(void) _task_ 1
{
	for (;;)
	{
		DataScope_Get_Channel_Data(getJY901Angle(JY901_1,X), 1);
		DataScope_Get_Channel_Data(getJY901Angle(JY901_1,Y), 2);
		DataScope_Get_Channel_Data(getJY901Angle(JY901_1,Z), 3);

		sendScopeData(3);
		os_wait(K_TMO, 30, 0);
	}
}
void dataUpdate(void) _task_ 2
{
	 for(;;)
	{
		LCD_printNum_I(0,0, (int)getJY901Angle(JY901_1, X),4);
		LCD_printNum_I(0, 1, (int)getJY901Angle(JY901_1, Y),4);
		LCD_printNum_I(0, 2, (int)getJY901Angle(JY901_1, Z),4);
		os_wait(K_TMO, 30, 0);

	}
	
}
void printADS1115(void) _task_ 3
{
	 for(;;)
	{
		DataScope_Get_Channel_Data(getADS1115ConvsionData(), 1);
				sendScopeData(1);
		os_wait(K_TMO, 30, 0);

	}
	
}