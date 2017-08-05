#ifndef __NRF24L01_H__
#define __NRF24L01_H__

#include "../../COMMON_HARDWARE/BSP/BSP.H"

void NRF24L01_TX_Init(void);
void NRF24L01_RX_Init(void);
void SetRX_Mode(void);
unsigned char nRF24L01_RxPacket(unsigned char* rx_buf);
void nRF24L01_TxPacket(unsigned char * tx_buf);

#endif