/************************************************************
* 组织名称：
* 文件名称: K:\单片机相关\电子大赛程序框架\HARDWARE\DEVICES\MOTOR\STEP_MOTOR\STEP_MOTOR.C
* 作者:  周晨阳
* 版本:  1.0
* 日期:  2017/07/11
* 描述: 步进电机的驱动程序
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
*
***********************************************************/

#include "STEP_MOTOR.H"


static  StepMotor g_stepMotor[STEP_MOTOR_NUM];

//************************************
// Method:    setStepMotorWithPulse
// FullName:  setStepMotorWithPulse
// Access:    public 
// Returns:   bit
// Qualifier: 设置步进电机的脉冲数，单纯设置脉冲
// Parameter: u8 motor
// Parameter: u32 pulse
// Parameter: u16 speed
//************************************
bit setStepMotorWithPulse(u8 motor, u32 pulse,u16 speed)
{
	setPulse(motor,speed,pulse);
	return 1;
}
//************************************
// Method:    setStepMotorWithDistance
// FullName:  setStepMotorWithDistance
// Access:    public 
// Returns:   bit
// Qualifier: //旋转指定长度脉冲发生器需要产生的脉冲数,根据初始化中的数据，自适应不同的步进电机。
// Parameter: u8 motor
// Parameter: float distance
// Parameter: u16 speed
//************************************
bit setStepMotorWithDistance(u8 motor,float distance,u16 speed)//旋转指定长度脉冲发生器需要产生的脉冲数,
{

	setStepMotorWithPulse(motor
						, (u32)((distance * 360 * g_stepMotor[motor].driverDiv) / (PI*g_stepMotor[motor].bearingDia*g_stepMotor[motor].DIV))
						, speed);
	return 1;

}
//************************************
// Method:    setStepMotorWithAngle
// FullName:  setStepMotorWithAngle
// Access:    public 
// Returns:   bit
// Qualifier: 设置步进电机的旋转角度
// Parameter: u8 motor：哪一个电机
// Parameter: u16 angle 旋转角度，可以超过360°
// Parameter: u8 speed：旋转速度，1-100
//************************************
bit setStepMotorWithAngle(u8 motor, float angle, u16 speed)
{
	setPulse(motor, speed, 
		(u32)((angle*g_stepMotor[motor].driverDiv) / g_stepMotor[motor].DIV));
	return 1;
}
//************************************
// Method:    setStepMotorWithRound
// FullName:  setStepMotorWithRound
// Access:    public 
// Returns:   bit
// Qualifier: 设置步进电机的旋转圈数
// Parameter: u8 motor
// Parameter: u16 round
// Parameter: u8 speed
//************************************
bit setStepMotorWithRound(u8 motor, u16 round, u16 speed)
{
	setStepMotorWithAngle(motor, 360 * round, speed);
	return 1;
}
void setStepMotorState(u8 motor,enum StepMotorState state)
{
	if (motor == STEP_MOTOR_1)
	{
		g_stepMotor[STEP_MOTOR_1].state = state;
	}
	else
	{
		g_stepMotor[STEP_MOTOR_2].state = state;
	}
}
//************************************
// Method:    getStepMotorState
// FullName:  getStepMotorState
// Access:    public 
// Returns:   bit
// Qualifier: 读取步进电机当前的状态
// Parameter: u8 motor
//***********************************
enum StepMotorState getStepMotorState(u8 motor)
{
	return g_stepMotor[motor].state;
}
//设置电机旋转方向
bit setStepMotorDiversion(u8 motor,bit diversion)
{
  
			if(motor==STEP_MOTOR_1)
			{
				if(diversion==CW)
				{
				StepMotor_1_DiversionControl=0;
				}
				else
				{
				StepMotor_1_DiversionControl=1;
				}
			}
			if(motor==STEP_MOTOR_2)
			{
				if(diversion==CW)
				{
				StepMotor_2_DiversionControl=0;
				}
				else
				{
				StepMotor_2_DiversionControl=1;
				}
			}
		
		
	return 1;
}
//************************************
// Method:    close_StepMotor
// FullName:  close_StepMotor
// Access:    public 
// Returns:   void
// Qualifier: 不考虑电机当前状态，强行关闭步进电机
// Parameter: u8 motor
//************************************
void close_StepMotor(u8 motor)
{
	closePulser(motor);
	g_stepMotor[motor].state = UNLOCKED;

}
//************************************
// Method:    open_StepMotor
// FullName:  open_StepMotor
// Access:    public 
// Returns:   void
// Qualifier: 设置好旋转参数之后，打开步进电机，电机开始运转
// Parameter: u8 motor
//************************************
void open_StepMotor(u8 motor)
{
	g_stepMotor[motor].state = RUNNING;
	openPulser(motor);
}
//************************************
// Method:    freeStepMotor
// FullName:  freeStepMotor
// Access:    public 
// Returns:   bit
// Qualifier: 解锁步进电机，同时不受到控制器的控制
// Parameter: u8 motor
//************************************
bit freeStepMotor(u8 motor)
{
   if(motor==STEP_MOTOR_1)
	 {
		  StepMotor_1_LockControl=0;
	 }
	 else
	 {
		 StepMotor_2_LockControl=0;
	 }
   g_stepMotor[motor].state = UNLOCKED;
	return 1;
}
//************************************
// Method:    lockStepMotor
// FullName:  lockStepMotor
// Access:    public 
// Returns:   bit
// Qualifier: 锁定步进电机，同时受到控制器控制
// Parameter: u8 motor
//************************************
bit lockStepMotor(u8 motor)
{
   if(motor==STEP_MOTOR_1)
	 {
		StepMotor_1_LockControl=1;
	 }
	 else
	 {
		 StepMotor_2_LockControl=1;
	 }
   g_stepMotor[motor].state = LOCKED;

	return 1;
}
//************************************
// Method:    stepMotor_Init
// FullName:  stepMotor_Init
// Access:    public 
// Returns:   void
// Qualifier: 步进电机初始化，传入初始化参数
// div:		  步进电机步进角，单位度，如1.8°
// driverDiv：驱动板细分值，如16细分
// maxPeriod：电机所能承受的最大启动频率，单位hz，如1000，
// bearingDia:旋转轴承齿轮的直径，单位cm，如3.9f 
//************************************
void stepMotor_Init(u8 motor,float div,u8 driverDiv,u16 maxPeriod,float bearingDia)
{ 
#ifdef DEBUG

			u8 initInfo[10];
#endif
	GPIO_InitTypeDef    GPIO_InitStructure;     //结构定义
	GPIO_InitStructure.Mode = GPIO_PullUp;  
	GPIO_InitStructure.Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_Inilize(GPIO_P2, &GPIO_InitStructure);  //初始化  
	g_stepMotor[motor].DIV = div;//1.8°的步进角
	g_stepMotor[motor].driverDiv = driverDiv; //驱动板上使用16的细分
	g_stepMotor[motor].maxPeriod = maxPeriod;
	g_stepMotor[motor].bearingDia = bearingDia;
	g_stepMotor[motor].state = UNLOCKED;
	PulserInit();//脉冲发生器初始化
#ifdef DEBUG
	sprintf(initInfo, "\r\n stepMotor %u was initialized \r\n", motor + 1);
	PrintString1(initInfo);
#endif
	
}


