#ifndef _BUTTON_H_
#define _BUTTON_H_
#include "../COMMON_HARDWARE/common_HD.h"
#define BUTTON_NUM 16
#define BUTTON1 0
#define BUTTON2 1
#define BUTTON3 2
#define BUTTON4 3
#define BUTTON5 4
#define BUTTON6 5
#define BUTTON7 6
#define BUTTON8 7
#define BUTTON9 8
#define BUTTON10 9
#define BUTTON11 10
#define BUTTON12 11
#define BUTTON13 12
#define BUTTON14 13
#define BUTTON15 14
#define BUTTON16 15
static u8 g_Button[BUTTON_NUM];
/*********��������ͽӿں���***********/
extern void  buttonScan(void );
//extern void Button_config(void);
extern u8 getButtonState(u8 BUTTON_data); //��ȡ����״̬����,���°�������1��û���·���0
#endif
