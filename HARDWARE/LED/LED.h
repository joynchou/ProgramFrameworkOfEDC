#ifndef _LED_H_
#define _LED_H_
#include "../COMMON_HARDWARE/common_HD.h"

extern bit Board_LED_Init  	(void)  ;
extern void open_Board_LED 	(void) ;
extern void close_Board_LED	(void);
extern bit getBoard_LED_State(void);
extern void blink(u8 time);


#endif