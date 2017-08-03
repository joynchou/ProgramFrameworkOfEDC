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

void Relay_Init(void);
void openRelayModular(u8 RELAY_MODULAR_N);
void closeRelayModular(u8 RELAY_MODULAR_N);
void openRelayKey(u8 RELAY_MODULAR_N,u8 RELAY_N);
void closeRelayKey(u8 RELAY_MODULAR_N,u8 RELAY_N);

#endif