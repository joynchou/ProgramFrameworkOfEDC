#include "../TASK/TASK.h"
#include <rtx51tny.h>                 /* RTX-51 tiny functions & defines      */
#include <stdio.h>
#include "../../HARDWARE/DEVICES/BUTTON/BUTTON.H"
#include "../../HARDWARE/DEVICES/LED/LED.H"
#include "../../HARDWARE/BSP/USART1.H"

//´®¿ÚÊ¾²¨Æ÷Êý¾Ý·¢ËÍº¯Êý
 unsigned int count1=0;
 unsigned int count2=0;
 unsigned int count3=0;
 unsigned int count4=0;
 unsigned int count5=0;

void taskStart() _task_ 0
{
	setup();
//	os_create_task (1);
//	os_create_task (2);
  os_create_task (3);
//  os_create_task (5);
//	os_create_task (6);
//	os_create_task (7);
	//	os_create_task (8);
//		os_create_task (9);
	os_delete_task (0); 
}
void task1(void) _task_ 1
{ 
	
		for(;;)
	{
		if(++count1>=65536)count1=0;
	
	 
	}
}
void task2(void) _task_ 2
{
	static unsigned int count=0;
  unsigned int test[20];

	 for(;;)
	{
	 blink(4);
   os_delete_task(2);
	}
	
}
void task3(void) _task_ 3
{ 
	unsigned int string[50];
	static unsigned int count=0;
	for(;;)
	{
			//if(++count3>=65536)count3=0;

		sprintf(string,"MILLIS is %d \n seconds is %d \n minutes is %d\n",getMillis(),getSeconds(),getMinutes());
		PrintString1(string);   //´®¿Ú²âÊÔ

	//	sendScopeData();
	  //PrintString1("task3 is running\n");   //´®¿Ú²âÊÔ
	//	TX1_write2buff(i++);
		os_wait(K_IVL,10,0);

	}
	
}
void task5(void) _task_ 5
{
		unsigned long count=0;
	for(;;)
	{
			if(++count5>=65536)count5=0;

	buttonScan();
		os_wait(K_IVL,5,0);	
	}
}

void task6(void) _task_ 6
{
	unsigned int string[150];
	unsigned int count=0;
	 for(;;)
	{
		sprintf(string,"count1=%d,\n count2=%d,\n count3=%d,\n count5=%d,\n ",count1,count2,count3,count5);
		PrintString1(string);   //´®¿Ú²âÊÔ
		os_wait(K_IVL,1000,0);	
	}
}
void task7(void) _task_ 7
{
	 for(;;)
	{
		if( getButtonState(BUTTON1_GPIO_PIN) )
		{
			 open_Board_LED();
		} 
		else
		{
			 close_Board_LED();
		}
		os_wait(K_IVL,10,0);
	}
}
void task8(void) _task_ 8
{
	unsigned int id[20];
	for(;;)
	{
		sprintf(id,"Task %d is running\n",os_running_task_id());
		PrintString1(id);   //´®¿Ú²âÊÔ
	
	os_wait(K_IVL,10,0);	
	}
}
void task9(void) _task_ 9
{
	for(;;)
	{
		open_Board_LED();
		os_wait(K_IVL,1000,0);
		close_Board_LED();
		os_wait(K_IVL,100,0);

	}
	
}

