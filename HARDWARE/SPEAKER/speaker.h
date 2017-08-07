#ifndef _SPEAKER_H_
#define _SPEAKER_H_
#include "../COMMON_HARDWARE/common_HD.h"
void Speaker_Init(void);
void setSpeakerPeriod(u16 value);
void setLength(u16 value);
void open_Speaker(u8 value);
void close_Speaker(u8 value);
void buzz(u16 type,u16 time) ;
void buzzWait(void);
void buzzFailed(void);
void buzzSucceed(void);
#endif 
