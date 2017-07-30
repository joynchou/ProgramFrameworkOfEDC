//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>

#include "MPU9250_SBUF.H"

enum STATE
{
	STOP,RUNNING,NO = 0,YES
};
/**********private structural*********/

struct STime//time struct
{
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned short usMiliSecond;
};
struct SAcc//acceleration struct
{
	short a[3];
	short T;
};
struct SGyro//palstance struct
{
	short w[3];
	short T;
};
struct SAngle//angle struct
{
	short Angle[3];
	short T;
};
struct SMag//magnetic field strut
{
	short h[3];
	short T;
};

struct SDStatus
{
	short sDStatus[4];
};

struct SPress
{
	long lPressure;
	long lAltitude;
};

struct SLonLat
{
	long lLon;
	long lLat;
};

struct SGPSV
{
	short sGPSHeight;
	short sGPSYaw;
	long lGPSVelocity;
};

typedef struct//the structural about JY901 modular
{
	struct STime			stcTime;
	struct SAcc 			stcAcc;
	struct SGyro 			stcGyro;
	struct SAngle 		stcAngle;
	struct SMag 			stcMag;
	struct SDStatus 	stcDStatus;
	struct SPress 		stcPress;
	struct SLonLat 		stcLonLat;
	struct SGPSV 			stcGPSV;
	enum STATE ModularStart;//STOP or RUNNING
	enum STATE ModularSwitch;//ON or OFF
	enum STATE CalcuEnd;//If calculate is finsh,the value can be read
}JY901Modular;
/************Initialization struct parameter************/
//struct STime		stcTime={0};
//struct SAcc 		stcAcc={0};
//struct SGyro 		stcGyro={0};
//struct SAngle 		stcAngle={0};
//struct SMag 		stcMag={0};
//struct SDStatus 	stcDStatus={0};
//struct SPress 		stcPress={0};
//struct SLonLat 		stcLonLat={0};
//struct SGPSV 		stcGPSV={0};
static JY901Modular MPU9250[JY901_NUM];

//************************************
// Method:    InitJY901
// FullName:  InitJY901
// Access:    public 
// Returns:   void
// Qualifier: Initialization of the JY901 modular on the software
// Parameter: u8 JY901_N;the JY901 modular's number
//************************************
void InitJY901(u8 JY901_N)
{
	MPU9250[JY901_N].ModularStart = STOP;
	MPU9250[JY901_N].ModularSwitch = OFF;
	MPU9250[JY901_N].CalcuEnd = NO;
}

//************************************
// Method:    EnableJY901
// FullName:  EnableJY901
// Access:    public 
// Returns:   void
// Qualifier: Make JY901 modular enable in software
// Parameter: u8 JY901_N;the JY901 modular's number
//************************************
void EnableJY901(u8 JY901_N)
{
	MPU9250[JY901_N].ModularStart = RUNNING;
}

//************************************
// Method:    DisableJY901
// FullName:  DisableJY901
// Access:    public 
// Returns:   void
// Qualifier: Make JY901 modular disable in software
// Parameter: u8 JY901_N;the JY901 modular's number
//************************************
void DisableJY901(u8 JY901_N)
{
	MPU9250[JY901_N].ModularStart = STOP;
}

//************************************
// Method:    openJY901SbufMode
// FullName:  openJY901SbufMode
// Access:    public 
// Returns:   void
// Qualifier: open JY901 modular's serial communication mode
// Parameter: u8 JY901_N;the JY901 modular's number
//************************************
void openJY901SbufMode(u8 JY901_N)
{
	MPU9250[JY901_N].ModularSwitch = ON;
}

//************************************
// Method:    closeJY901SbufMode
// FullName:  closeJY901SbufMode
// Access:    public 
// Returns:   void
// Qualifier: close JY901 modular's serial communication mode
// Parameter: u8 JY901_N;the JY901 modular's number
//************************************
void closeJY901SbufMode(u8 JY901_N)
{
	MPU9250[JY901_N].ModularSwitch = OFF;
}

//************************************
// Method:    getJY901Acceleration
// FullName:  getJY901Acceleration
// Access:    public 
// Returns:   bit
// Qualifier: return of the acceleration is axis do you want
// Parameter: u8 JY901_N;the JY901 modular's number
// Parameter: u8 axis;x,y,z choose one of them
//************************************
float getJY901Acceleration(u8 JY901_N,u8 axis)
{
	if(MPU9250[JY901_N].CalcuEnd == YES)
	{
		return (float)MPU9250[JY901_N].stcAcc.a[axis]/32768*16;
	}
	return 0;
}

//************************************
// Method:    getJY901Palstance
// FullName:  getJY901Palstance
// Access:    public 
// Returns:   float
// Qualifier: return of the Palstance is axis do you want
// Parameter: u8 JY901_N;the JY901 modular's number
// Parameter: u8 axis;x,y,z choose one of them
//************************************
float getJY901Palstance(u8 JY901_N,u8 axis)
{
	if(MPU9250[JY901_N].CalcuEnd == YES)
	{
		return (float)MPU9250[JY901_N].stcGyro.w[axis]/32768*2000;
	}
	return 0;
}

//************************************
// Method:    getJY901Angle
// FullName:  getJY901Angle
// Access:    public 
// Returns:   float
// Qualifier: return of the angle is axis do you want
// Parameter: u8 JY901_N;the JY901 modular's number
// Parameter: u8 axis;x,y,z choose one of them
//************************************
float getJY901Angle(u8 JY901_N,u8 axis)
{
	if(MPU9250[JY901_N].CalcuEnd == YES)
	{
		return (float)MPU9250[JY901_N].stcAngle.Angle[axis]/32768*180;
	}
	return 0;
}

//************************************
// Method:    getJY901Magnetic
// FullName:  getJY901Magnetic
// Access:    public 
// Returns:   float
// Qualifier: return of the magnetic field is axis do you want
// Parameter: u8 JY901_N;the JY901 modular's number
// Parameter: u8 axis;x,y,z choose one of them
//************************************
float getJY901Magnetic(u8 JY901_N,u8 axis)
{	
	if(MPU9250[JY901_N].CalcuEnd == YES)
	{
		return MPU9250[JY901_N].stcMag.h[axis];
	}
	return 0;
}

/***********private calculate**************/
void CharToLong(char Dest[],char Source[])
{
	 *Dest 		  = Source[3];
	 *(Dest+1) 	= Source[2];
	 *(Dest+2) 	= Source[1];
	 *(Dest+3) 	= Source[0];
}

void CopeSerialData(u8 JY901_N)//This function need added in abstask.c to buliding a task if you want use JY901 modular
{
	//u8 str_0[15],str_1[15],str_2[15];
	static unsigned char ucRxBuffer[12];//数据接收缓冲
	static unsigned char ucRxCnt = 0;	
	if(MPU9250[JY901_N].ModularStart)
	{
		if(MPU9250[JY901_N].ModularSwitch)
		{
			MPU9250[JY901_N].CalcuEnd = NO;
		if( RX1_Buffer[0]!=0x55)//如果帧头不对，
		{
			COM1.RX_Cnt=0;//清除数组长度记录变量
			ucRxCnt=0;
		//PrintString1("DATA's head is not right\r\n");

			return ;//退出本次数据处理
		}
		//以下是当帧头正确时才执行的代码
			ucRxBuffer[COM1.RX_Cnt]=RX1_Buffer[COM1.RX_Cnt];//将串口1接收缓冲中的数据读出

		if(COM1.RX_Cnt<11)//如果还没有收到12个数据，也退出本次数据处理
		{
			//PrintString1("DATA IS not ready \r\n");

			return ;
		}
//			if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
//			{
//				ucRxCnt 				= 0;
//				COM1.RX_Cnt     = 0;
//				return;																																	  
//			}
//			if (ucRxCnt<11) {return;}//数据不满11个，则返回
		
	//以下是当收到12个数据之后才执行的代码

			else//如果收到了12个数据了，则开始本次数据处理
			{
			//	PrintString1("DATA IS OK \r\n");
				switch(ucRxBuffer[1])
				{
					case 0x50: 
								MPU9250[JY901_N].stcTime.ucYear 			= ucRxBuffer[2];
								MPU9250[JY901_N].stcTime.ucMonth 			= ucRxBuffer[3];
								MPU9250[JY901_N].stcTime.ucDay 				= ucRxBuffer[4];
								MPU9250[JY901_N].stcTime.ucHour 			= ucRxBuffer[5];
								MPU9250[JY901_N].stcTime.ucMinute 		= ucRxBuffer[6];
								MPU9250[JY901_N].stcTime.ucSecond 		= ucRxBuffer[7];
								MPU9250[JY901_N].stcTime.usMiliSecond = ((unsigned short)ucRxBuffer[9]<<8)|ucRxBuffer[8];
													//	PrintString1("into time\r\n");

								break;
					case 0x51:	
								MPU9250[JY901_N].stcAcc.a[0] = ((unsigned short)ucRxBuffer[3]<<8)|ucRxBuffer[2];
								MPU9250[JY901_N].stcAcc.a[1] = ((unsigned short)ucRxBuffer[5]<<8)|ucRxBuffer[4];
								MPU9250[JY901_N].stcAcc.a[2] = ((unsigned short)ucRxBuffer[7]<<8)|ucRxBuffer[6];
																		//	PrintString1("into acc\r\n");


								break;
					case 0x52:	
								MPU9250[JY901_N].stcGyro.w[0] = ((unsigned short)ucRxBuffer[3]<<8)|ucRxBuffer[2];
								MPU9250[JY901_N].stcGyro.w[1] = ((unsigned short)ucRxBuffer[5]<<8)|ucRxBuffer[4];
								MPU9250[JY901_N].stcGyro.w[2] = ((unsigned short)ucRxBuffer[7]<<8)|ucRxBuffer[6];
															//				PrintString1("into gyro\r\n");

								break;
					case 0x53:	
								MPU9250[JY901_N].stcAngle.Angle[0] = ((unsigned short)ucRxBuffer[3]<<8)|ucRxBuffer[2];
								MPU9250[JY901_N].stcAngle.Angle[1] = ((unsigned short)ucRxBuffer[5]<<8)|ucRxBuffer[4];
								MPU9250[JY901_N].stcAngle.Angle[2] = ((unsigned short)ucRxBuffer[7]<<8)|ucRxBuffer[6];
								MPU9250[JY901_N].stcAngle.T				 = ((unsigned short)ucRxBuffer[9]<<8)|ucRxBuffer[8];
								//	PrintString1("into angle\r\n");
//							sprintf(str,"x is %d\n",(unsigned short)MPU9250[0].stcAngle.Angle[X]);
//				PrintString1(str);
//							sprintf(str,"y is %d\n",(unsigned short)MPU9250[0].stcAngle.Angle[Y]);
//				PrintString1(str);
//							sprintf(str,"z is %d\n",(unsigned short)MPU9250[0].stcAngle.Angle[Z]);
//				PrintString1(str);

								break;
					case 0x54:	
								MPU9250[JY901_N].stcMag.h[0] = ((unsigned short)ucRxBuffer[3]<<8)|ucRxBuffer[2];
								MPU9250[JY901_N].stcMag.h[1] = ((unsigned short)ucRxBuffer[5]<<8)|ucRxBuffer[4];
								MPU9250[JY901_N].stcMag.h[2] = ((unsigned short)ucRxBuffer[7]<<8)|ucRxBuffer[6];
								MPU9250[JY901_N].stcMag.T		 = ((unsigned short)ucRxBuffer[9]<<8)|ucRxBuffer[8];
																		//	PrintString1("into mag\r\n");

								break;
					case 0x55:	
								MPU9250[JY901_N].stcDStatus.sDStatus[0] = ((unsigned short)ucRxBuffer[3]<<8)|ucRxBuffer[2];
								MPU9250[JY901_N].stcDStatus.sDStatus[1] = ((unsigned short)ucRxBuffer[5]<<8)|ucRxBuffer[4];
								MPU9250[JY901_N].stcDStatus.sDStatus[2] = ((unsigned short)ucRxBuffer[7]<<8)|ucRxBuffer[6];
								MPU9250[JY901_N].stcDStatus.sDStatus[3] = ((unsigned short)ucRxBuffer[9]<<8)|ucRxBuffer[8];
								break;
					case 0x56:	
								ucRxBuffer[2] = 0x12;
								ucRxBuffer[3] = 0x34;
								ucRxBuffer[4] = 0x56;
								ucRxBuffer[5] = 0x78;
								CharToLong((char*)&MPU9250[JY901_N].stcPress.lPressure,(char*)&ucRxBuffer[2]);
								CharToLong((char*)&MPU9250[JY901_N].stcPress.lAltitude,(char*)&ucRxBuffer[6]);
								break;
					case 0x57:	
								CharToLong((char*)&MPU9250[JY901_N].stcLonLat.lLon,(char*)&ucRxBuffer[2]);
								CharToLong((char*)&MPU9250[JY901_N].stcLonLat.lLat,(char*)&ucRxBuffer[6]);
								break;
					case 0x58:	
								MPU9250[JY901_N].stcGPSV.sGPSHeight = ((unsigned short)ucRxBuffer[3]<<8)|ucRxBuffer[2];
								MPU9250[JY901_N].stcGPSV.sGPSYaw 		= ((unsigned short)ucRxBuffer[5]<<8)|ucRxBuffer[4];
								CharToLong((char*)&MPU9250[JY901_N].stcGPSV.lGPSVelocity,(char*)&ucRxBuffer[6]);
								break;
				}
			}
			ucRxCnt  		= 0;
			COM1.RX_Cnt = 0;
			MPU9250[JY901_N].CalcuEnd = YES;
//							sprintf(str_0,"x is %f\r\n",getJY901Angle(JY901_1,X));
//				PrintString1(str_0);
//							sprintf(str_1,"y is %f\r\n",getJY901Angle(JY901_1,Y));
//				PrintString1(str_1);
//							sprintf(str_2,"z is %f\r\n",getJY901Angle(JY901_1,Z));
//				PrintString1(str_2);

		}
	}
}