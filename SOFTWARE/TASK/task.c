#include "task.h"
#include "../COMMON_SOFTWARE/DATA_SCOPE/DataScope_DP.h"
#include "setup.h"
#include "../HARDWARE/BSP/USART1.h"


void sendScopeData(void) 
{
	u8 a; //
	u8 Send_Count;
	
	DataScope_Get_Channel_Data(123.6f, 1); 
		
	DataScope_Get_Channel_Data(567, 2);  
	/*
	DataScope_Get_Channel_Data(yourData, 3);  
	DataScope_Get_Channel_Data(yourData, 4);  
	DataScope_Get_Channel_Data(yourData, 5);  
	...
	*/
	Send_Count = DataScope_Data_Generate(2); //
	for (a = 0; a < Send_Count; a++)
	{
		TX1_write2buff(DataScope_OutPut_Buffer[a]); //发送一通道数据到串口示波器
	}
  
}
