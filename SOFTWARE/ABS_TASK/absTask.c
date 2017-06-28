#include "../TASK/TASK.h"
#include <rtx51tny.h>                 /* RTX-51 tiny functions & defines      */

//串口示波器数据发送函数
void taskStart() _task_ 0
{
	setup();
	os_create_task (1);
	os_delete_task (0); 
}
void task1(void) _task_ 1
{   for(;;)
	{
	 sendScopeData();
	 os_wait(K_IVL,10,0);
	}
}
void task2(void) _task_ 2
{
	 for(;;)
	{
		
		
	}
	
}
void task3(void) _task_ 3
{
	for(;;)
	{
		
		
	}
	
}
