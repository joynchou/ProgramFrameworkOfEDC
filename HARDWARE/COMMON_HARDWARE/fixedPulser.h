#ifndef _FIXEDPULSER_H_
#define _FIXEDPULSER_H_
#include "../BSP/config.h"
#define PULSER_NUM	2
#define PULSER_1	0
#define PULSER_2	1
extern void PulserInit(void)                          ;

extern bool setPulse( u8 pulser_num,u16 Hz,u16 count) ;
extern bool openPulser(u8 pulser_num)                 ;
extern bool closePulser(u8 pulser_num)                ;
extern bool getPulserState(u8 pulser_num)             ;
#endif