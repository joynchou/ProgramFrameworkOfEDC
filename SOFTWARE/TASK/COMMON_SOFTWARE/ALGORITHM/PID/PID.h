 /************************************************************
 * ��֯���ƣ�
 * �ļ�����: K:\��Ƭ�����\���Ӵ���������\SOFTWARE\ALGORITHM\PID\PID.H
 * ����:     
 * �汾 :    
 * ����:     2017/07/06
 * ����:
 * ��ʷ�޸ļ�¼:
 * <����> <ʱ��> <�汾 > <����>
 * 
 ***********************************************************/
 
 #ifndef _PID_H_
 #define _PID_H_
 #include "../../../../../HARDWARE/devices.h"

#define SET_ANGLE    0
#define ERR          1
#define ERR_LAST     2
#define KP 			 3
#define KI 			 4
#define KD           5
#define INTEGRAL     6
#define OUTPUT       7
#define PID_NUM	2   //��Ҫʹ�ö��ٸ�pid
#define PID_1 0
#define PID_2 1


 /*************************************************
 * ��������:double getPID_data(u8 DATA)
 * ����: ��ȡpid����
 * ����: ���궨��
 * ���:
 * ����ֵ: ��Ӧpid����
 * ����˵��: ��û������pid������ֱ�Ӷ�ȡ������δ֪��
 *************************************************/
float getPID_data(u8 DATA);



/*************************************************
* ��������:void setPID_data(u8 DATA,float value)
* ����:  ����pid���������ĺ�����һ����ֻ������һ������
*        ����Ϊ����PID�����Ľӿڡ�
* ����: u8 DATA ����Ҫ���ĵĲ������ƣ�Ϊ�궨��,
float value������ֵ
* ���: ��
* ����ֵ: ��
* ����˵��: ��
*************************************************/
void setPID_data(u8 DATA, float value);

/*************************************************
* ��������: void PID_config(float kp,float ki,float kd)
*                    ����:
*************************************************
* pid�㷨��ʼ��������������������P,I,D,
* �˺���ֻ����Ϊ��ʼ����������Ϊ����������ֵ�Ľӿ�
* �����Ҫ����������ֵ����ʹ��setPID_data()����
* ***********************************************
* ����: float kp,float ki,float kd
* ���:     ��
* ����ֵ:   ��
* ����˵��: ��
*************************************************/
void PID_config(u8 PID_N, float kp, float ki, float kd);//pid�㷨��ʼ��������������������PID


 
void openPID(u8 PID_N);
void closePID(u8 PID_N);
void IncClassPID(u8 PID_N,u8 PID_MODE);//������PID�㷨
void PosClassPID(u8 PID_N,u8 PID_MODE);//λ����PID�㷨
void setParameterInferiorLimit(u8 PID_N, float value);
void setParameterUpperLimit(u8 PID_N, float value);
void setActualParameter(u8 PID_N, float value);
void setKi(u8 PID_N, float value);
void setKp(u8 PID_N, float value);
void setKd(u8 PID_N, float value);
void setParameter(u8 PID_N, float value);
void setMaxError(u8 PID_N,float err_max);
float getParameter(u8 PID_N);
float getErr(u8 PID_N);
float getErrLast(u8 PID_N);
float getKp(u8 PID_N);
float getKi(u8 PID_N);
float getKd(u8 PID_N);
float getOutput(u8 PID_N);
float getIntegral(u8 PID_N);
#endif