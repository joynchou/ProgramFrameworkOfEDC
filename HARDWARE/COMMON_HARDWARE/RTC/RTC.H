#ifndef __RTC_H__
#define __RTC_H__

#include "../BSP/BSP.H"

/*****************************RTC Date RAM Address****************************/
#define DS1307_ADDRESS  0xd0  //DS1307 element's address
#define DS1307_SECOND   0x00  //DS1307 second's address
#define DS1307_MINUTE   0x01  //DS1307 minute's address
#define DS1307_HOUR     0x02  //DS1307 hour's address
#define DS1307_WEEK     0x03  //DS1307 week's address
#define DS1307_DAY      0x04  //DS1307 day's address
#define DS1307_MONTH    0x05  //DS1307 month's address
#define DS1307_YEAR     0x06  //DS1307 year's address
#define DS1307_CONTROL  0x07  //DS1307 commond's address
/*******************************RTC Date Commond******************************/
#define DISABLE_SQUARE_OUTPUT 0x00//SQL/OUT output low level
#define ENABLE_SQUARE_OUTPUT  0x80//SQL/OUT output high level
#define SQUARE_1HZ_RATE       0x10//Set 1Hz square rate 
#define SQUARE_4096HZ_RATE    0x11//Set 4096Hz square rate
#define SQUARE_8192HZ_RATE    0x12//Set 8192Hz square rate
#define SQUARE_32768HZ_RATE   0x13//Set 32768Hz square rate

u8 get_RTC_Time(u8 address,u8 *Time);
void Write_RTC_Date(u8 date);
u8 Read_RTC_Date(u8 address,u8 date);

#endif