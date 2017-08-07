#ifndef __NRF24L01_H__
#define __NRF24L01_H__

#include "../../COMMON_HARDWARE/BSP/BSP.H"

#define RX_MODE 0
#define TX_MODE 1
#define HALF_DUPLEX 2

//void NRF24L01_TX_Init(void);
//void NRF24L01_RX_Init(void);
void NRF24L01_Init(u8 mode);
void ChoiceHalfDuplexMode(u8 mode);
unsigned char nRF24L01_RxPacket(unsigned char* rx_buf);
void nRF24L01_TxPacket(unsigned char * tx_buf);

#endif