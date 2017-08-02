#include "RELAY.H"

sbit IN1=P2^7;
sbit IN2=P2^6;
sbit IN3=P2^5;
sbit IN4=P2^4;

enum STATE
{
	OPEN,CLOSE
};

typedef struct
{
	u8 state;//继电器开关，open为开，close为关
}Relay;

typedef struct//继电器模块结构体
{
	u8 able;//继电器模块使能
	Relay RelaySwitch[RELAY_NUM];//单个模块中继电器个数
}RelayModular;
static RelayModular s_RelayModular[RELAY_MODULAR_NUM];

void Relay_Init(void)
{
	GPIO_InitTypeDef    GPIO_InitStructure;     //结构定义
	GPIO_InitStructure.Mode = GPIO_PullUp;  
	GPIO_InitStructure.Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_Inilize(GPIO_P2, &GPIO_InitStructure);  //初始化  
}

static void RelayKeyChange(u8 RELAY_MODULAR_N,u8 RELAY_N)
{
	switch(RELAY_N)
	{
		case RELAY_1:
			IN1 = s_RelayModular[RELAY_MODULAR_N].RelaySwitch[RELAY_N].state;
			break;
		case RELAY_2:
			IN2 = s_RelayModular[RELAY_MODULAR_N].RelaySwitch[RELAY_N].state;
			break;
		case RELAY_3:
			IN3 = s_RelayModular[RELAY_MODULAR_N].RelaySwitch[RELAY_N].state;
			break;
		case RELAY_4:
			IN4 = s_RelayModular[RELAY_MODULAR_N].RelaySwitch[RELAY_N].state;
			break;
	}
}
void openRelayModular(u8 RELAY_MODULAR_N)
{
	s_RelayModular[RELAY_MODULAR_N].able = ON;
}

void closeRelayModular(u8 RELAY_MODULAR_N)
{
	u8 val;
	s_RelayModular[RELAY_MODULAR_N].able = OFF;
	for(val = 0;val < RELAY_NUM;val++)
	{
		s_RelayModular[RELAY_MODULAR_N].RelaySwitch[val].state = CLOSE;
		RelayKeyChange(RELAY_MODULAR_N,val);
	}
}

void openRelayKey(u8 RELAY_MODULAR_N,u8 RELAY_N)
{
	if(s_RelayModular[RELAY_MODULAR_N].able == ON)
	{
		s_RelayModular[RELAY_MODULAR_N].RelaySwitch[RELAY_N].state = OPEN;
		RelayKeyChange(RELAY_MODULAR_N,RELAY_N);
	}
}

void closeRelayKey(u8 RELAY_MODULAR_N,u8 RELAY_N)
{
	if(s_RelayModular[RELAY_MODULAR_N].able == ON)
	{
		s_RelayModular[RELAY_MODULAR_N].RelaySwitch[RELAY_N].state = CLOSE;
		RelayKeyChange(RELAY_MODULAR_N,RELAY_N);
	}
}