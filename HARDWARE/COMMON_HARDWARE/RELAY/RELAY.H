#ifndef _RELAY_H_
#define _RELAY_H
#include "../BSP/BSP.H"

#define RELAY_NUM 4
#define RELAY_1 0
#define RELAY_2 1
#define RELAY_3 2
#define RELAY_4 3
#define RELAY_MODULAR_NUM 2
#define RELAY_MODULAR_1 0
#define RELAY_MODULAR_2 1

/*******************基本使用方法********************
void task()
{
  此用法是正规用法
  Relay_Init();
  openRelayModular(RELAY_MODULAR_N);
  openRelayKey(RELAY_MOUDLUAR_N.RELAY_N);
  错误用法
  openRelayKey(RELAY_MODULAR_N,RELAY_N);
  //使用继电器开关时需要初始化继电器模块并开启继电器模块
  //当继电器模块开启时继电器开关才会使能
  //使用closeRelayModular时会关闭所有打开的继电器
}
**************************************************/

void Relay_Init(void);//继电器初始化程序
void openRelayModular(u8 RELAY_MODULAR_N);//打开要使用的继电器模块
void closeRelayModular(u8 RELAY_MODULAR_N);//关闭所选择的继电器模块
void openRelayKey(u8 RELAY_MODULAR_N,u8 RELAY_N);//打开所选继电器模块中的单个继电器开关
void closeRelayKey(u8 RELAY_MODULAR_N,u8 RELAY_N);//关闭所选继电器模块中的单个继电器开关

#endif
