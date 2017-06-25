 /************************************************************
 * ��֯���ƣ����Ӵ���С��
 * �ļ�����: PID..h
 * ����:     ���Ӵ���С��
 * �汾 :    1.0
 * ����:     10/06/17
 * ����: 	 
 * ��ʷ�޸ļ�¼: 
 * <����> <ʱ��> <�汾 > <����>
 ***********************************************************/
 #ifndef _PID_H_
 #define _PID_H_
#include "../USER/USER.h"
#define SET_ANGLE    0
#define ERR          1
#define ERR_LAST     2
#define KP 			 3
#define KI 			 4
#define KD           5
#define INTEGRAL     6
#define OUTPUT       7

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
void PID_config(float kp, float ki, float kd);//pid�㷨��ʼ��������������������PID


 
 #endif