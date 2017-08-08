#include "phSensor.h"
 
typedef struct
{
	float k;
	float b;
	u8 state;
	float PH_Value;
}Equation;

static Equation PH[PH_NUM];

 //************************************
 // Method:    PH_config
 // FullName:  PH_config
 // Access:    public 
 // Returns:   void
 // Qualifier: ph计初始化
 // Parameter: u8 PH_N：哪一个ph计
 // Parameter: float k
 // Parameter: float b
 //************************************
 void PH_config(u8 PH_N, float k, float b)
{
	ADS1115_Config();
	open_ADS1115(PH_N);
	PH[PH_N].k = k;
	PH[PH_N].b = b;
}

//************************************
// Method:    setPHCoefficient
// FullName:  setPHCoefficient
// Access:    public 
// Returns:   void
// Qualifier: 设置ph的斜率和截距
// Parameter: u8 PH_N
// Parameter: float k
// Parameter: float b
//************************************
void setPHCoefficient(u8 PH_N,float k,float b)
{
	PH[PH_N].k = k;
	PH[PH_N].b = b;
}

//************************************
// Method:    getPHvalue
// FullName:  getPHvalue
// Access:    public 
// Returns:   float
// Qualifier: //此函数还可以返回上一次的PH值，不需要读取时间 ，是静态的数据，因为需要保存
// Parameter: u8 PH_N
// Parameter: u8 whichPHvalue
//************************************
#define FILTER_TIME  10
float getPH_Value(u8 PH_N,u8  whichPHvalue)
{
	u16 PH_ADC_Value[FILTER_TIME+1];
	u8 i = 0;
	static float presentPH = 0; // 当前结果
	static float lastPH;  
	if (whichPHvalue)  
	{
		for (i = 0; i < FILTER_TIME; i++)
		{
			PH_ADC_Value[i] = getADS1115ConvsionData(PH_N);
		}
		PH_ADC_Value[FILTER_TIME] = filter(PH_ADC_Value, FILTER_TIME, 65535, 0);
		presentPH = PH_ADC_Value[FILTER_TIME] * PH[PH_N].k + PH[PH_N].b;//y=kx+b

 		lastPH = presentPH;
		return presentPH;
	}
	else  //返回上一次PH值结果
  {
		return  lastPH;
	}
}