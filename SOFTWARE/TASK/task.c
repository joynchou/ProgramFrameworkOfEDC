#include "task.h"
#include <rtx51tny.h>                 /* RTX-51 tiny functions & defines      */
#include "../COMMON_SOFTWARE/DATA_SCOPE/DataScope_DP.h"

//串口示波器数据发送函数
void taskStart() _task_ 0
{
	os_create_task (1);
	os_delete_task (0); 
}
void sendScopeData(void) _task_ 1
{
	u8 a; //
	u8 Send_Count;
	/*
	DataScope_Get_Channel_Data(yourData, 1);  //误差数据
	DataScope_Get_Channel_Data(yourData, 2);  //实际输出数据
	DataScope_Get_Channel_Data(yourData, 3);  //积分数据
	DataScope_Get_Channel_Data(yourData, 4);  //设定角度
	DataScope_Get_Channel_Data(yourData, 5);  //实际角度
	...
	*/
	Send_Count = DataScope_Data_Generate(5); //
	for (a = 0; a < Send_Count; a++)
	{
		TX1_write2buff(DataScope_OutPut_Buffer[a]); //发送一通道数据到串口示波器
	}
  os_wait(K_IVL,10,0);
}

