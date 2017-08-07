/************************************************************
* 组织名称：
* 文件名称: K:\单片机相关\电子大赛程序框架\HARDWARE\COMMON_HARDWARE\ADS1115\ADS1115.H
* 作者:
* 版本:
* 日期:     2017/08/03
* 描述:
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
*
***********************************************************/

#ifndef _ADS1115_H_
#define _ADS1115_H_
#include "../BSP/BSP.H"
/*=========================================================================
I2C ADDRESS/BITS
-----------------------------------------------------------------------*/
#define ADS1015_ADDRESS                 (0x48)    // 1001 000 (ADDR = GND)
#define CHANNEL_1 0
#define CHANNEL_2 1
#define CHANNEL_3 2
#define CHANNEL_4 3
/*=========================================================================*/

void ADS1115_Config(u8 speed, u8 mode);
u16 getADS1115ConvsionData(u8 channl);
void open_ADS1115(u8 channel);
void close_ADS1115(u8 channel);
#endif // !_ADS1115_H_
