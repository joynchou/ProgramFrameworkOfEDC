#include "../TASK/TASK.h"
#include <rtx51tny.h>                 /* RTX-51 tiny functions & defines      */
#include <stdio.h>

//串口示波器数据发送函数
void taskStart() _task_ 0
{
	setup();
	os_create_task (1);
	os_create_task (2);
  os_create_task (3);

	os_delete_task (0); 
}
void task1(void) _task_ 1
{  
	for(;;)
	{
   PrintString1("task1 is running\n");   //串口测试
	 os_wait(K_IVL,1000,0);
	}
}
void task2(void) _task_ 2
{
	 for(;;)
	{
   PrintString1("task2 is running\n");   //串口测试

		os_wait(K_IVL,2000,0);

	}
	
}
void task3(void) _task_ 3
{ 
int i=0;	
	for(;;)
	{
		sendScopeData();
	  //PrintString1("task3 is running\n");   //串口测试
	//	TX1_write2buff(i++);
		os_wait(K_IVL,100,0);

	}
	
}
