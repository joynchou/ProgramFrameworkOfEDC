#include "NRF24L01.H"

//*********************************************NRF24L01*************************************
#define TX_ADR_WIDTH    5   	// 5 uints TX address width
#define RX_ADR_WIDTH    5   	// 5 uints RX address width
#define TX_PLOAD_WIDTH  32  	// 20 uints TX payload
#define RX_PLOAD_WIDTH  32  	// 20 uints TX payload
u8 const TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};	//本地地址
u8 const RX_ADDRESS[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};	//接收地址
//***************************************NRF24L01寄存器指令*******************************************************
#define READ_REG        0x00  	// 读寄存器指令
#define WRITE_REG       0x20 	// 写寄存器指令
#define RD_RX_PLOAD     0x61  	// 读取接收数据指令
#define WR_TX_PLOAD     0xA0  	// 写待发数据指令
#define FLUSH_TX        0xE1 	// 冲洗发送 FIFO指令
#define FLUSH_RX        0xE2  	// 冲洗接收 FIFO指令
#define REUSE_TX_PL     0xE3  	// 定义重复装载数据指令
#define NOP             0xFF  	// 保留
//*************************************SPI(nRF24L01)寄存器地址****************************************************
#define CONFIG          0x00  // 配置收发状态，CRC校验模式以及收发状态响应方式
#define EN_AA           0x01  // 自动应答功能设置
#define EN_RXADDR       0x02  // 可用信道设置
#define SETUP_AW        0x03  // 收发地址宽度设置
#define SETUP_RETR      0x04  // 自动重发功能设置
#define RF_CH           0x05  // 工作频率设置
#define RF_SETUP        0x06  // 发射速率、功耗功能设置
#define STATUS          0x07  // 状态寄存器
#define OBSERVE_TX      0x08  // 发送监测功能
#define CD              0x09  // 地址检测           
#define RX_ADDR_P0      0x0A  // 频道0接收数据地址
#define RX_ADDR_P1      0x0B  // 频道1接收数据地址
#define RX_ADDR_P2      0x0C  // 频道2接收数据地址
#define RX_ADDR_P3      0x0D  // 频道3接收数据地址
#define RX_ADDR_P4      0x0E  // 频道4接收数据地址
#define RX_ADDR_P5      0x0F  // 频道5接收数据地址
#define TX_ADDR         0x10  // 发送地址寄存器
#define RX_PW_P0        0x11  // 接收频道0接收数据长度
#define RX_PW_P1        0x12  // 接收频道0接收数据长度
#define RX_PW_P2        0x13  // 接收频道0接收数据长度
#define RX_PW_P3        0x14  // 接收频道0接收数据长度
#define RX_PW_P4        0x15  // 接收频道0接收数据长度
#define RX_PW_P5        0x16  // 接收频道0接收数据长度
#define FIFO_STATUS     0x17  // FIFO栈入栈出状态寄存器设置
//************************************************************************************
/*
void NRF24L01_TX_Init(void)
{
 	CE=0;    // chip enable
 	CSN=1;   // Spi  disable 
 	SCK=0;   // 
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 写本地地址	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  频道0自动	ACK应答允许	
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  允许接收地址只有频道0，如果需要多频道可以参考Page21
//	SPI_RW_Reg(WRITE_REG + SETUP_RETR,0x1a);//设置重发次  
	SPI_RW_Reg(WRITE_REG + RF_CH, 0);	//   设置信道工作为2.4GHZ，收发必须一致数
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//设置发射速率为1MB/S，发射功率为最大值+7dB，由于有X2401L功放，实际+21dbm输出
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
  SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e); //IRQ收发完成中断响应，16位CRC	，主发送
	delay_us(20);
}

void NRF24L01_RX_Init(void)
{
 	CE=0;    // chip enable
 	CSN=1;   // Spi  disable 
 	SCK=0;   // 
//	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 写本地地址	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  频道0自动	ACK应答允许	
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  允许接收地址只有频道0，如果需要多频道可以参考Page21  
	SPI_RW_Reg(WRITE_REG + RF_CH, 0);        //   设置信道工作为2.4GHZ，收发必须一致
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//设置发射速率为1MB/S，发射功率为最大值+7dB，由于有X2401L功放，实际+21dbm输出 
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f); //IRQ收发完成中断响应，16位CRC	，主接收
	delay_us(20);
}

void NRF24L01_Half_duplex(void)
{
	 	CE=0;    // chip enable
 	CSN=1;   // Spi  disable 
 	SCK=0;   // 
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 写本地地址	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  频道0自动	ACK应答允许	
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  允许接收地址只有频道0，如果需要多频道可以参考Page21
//	SPI_RW_Reg(WRITE_REG + SETUP_RETR,0x1a);//设置重发次  
	SPI_RW_Reg(WRITE_REG + RF_CH, 0);	//   设置信道工作为2.4GHZ，收发必须一致数
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//设置发射速率为1MB/S，发射功率为最大值+7dB，由于有X2401L功放，实际+21dbm输出
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
}*/

void NRF24L01_Init(u8 mode)
{
	if(mode == RX_MODE)
	{
		CE=0;    // chip enable
		CSN=1;   // Spi  disable 
		SCK=0;   // 
	//	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 写本地地址	
		SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
		SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  频道0自动	ACK应答允许	
		SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  允许接收地址只有频道0，如果需要多频道可以参考Page21  
		SPI_RW_Reg(WRITE_REG + RF_CH, 0);        //   设置信道工作为2.4GHZ，收发必须一致
		SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
		SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//设置发射速率为1MB/S，发射功率为最大值+7dB，由于有X2401L功放，实际+21dbm输出 
		SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f); //IRQ收发完成中断响应，16位CRC	，主接收
		delay_us(20);
	}
	else if(mode == TX_MODE)
	{
		CE=0;    // chip enable
		CSN=1;   // Spi  disable 
		SCK=0;   // 
		SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 写本地地址	
		SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
		SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  频道0自动	ACK应答允许	
		SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  允许接收地址只有频道0，如果需要多频道可以参考Page21
	//	SPI_RW_Reg(WRITE_REG + SETUP_RETR,0x1a);//设置重发次  
		SPI_RW_Reg(WRITE_REG + RF_CH, 0);	//   设置信道工作为2.4GHZ，收发必须一致数
		SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//设置发射速率为1MB/S，发射功率为最大值+7dB，由于有X2401L功放，实际+21dbm输出
		SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
		SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e); //IRQ收发完成中断响应，16位CRC	，主发送
		delay_us(20);
	}else if(mode == HALF_DUPLEX)
	{
		CE=0;    // chip enable
		CSN=1;   // Spi  disable 
		SCK=0;   // 
		SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 写本地地址	
		SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
		SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  频道0自动	ACK应答允许	
		SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  允许接收地址只有频道0，如果需要多频道可以参考Page21
	//	SPI_RW_Reg(WRITE_REG + SETUP_RETR,0x1a);//设置重发次  
		SPI_RW_Reg(WRITE_REG + RF_CH, 0);	//   设置信道工作为2.4GHZ，收发必须一致数
		SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//设置发射速率为1MB/S，发射功率为最大值+7dB，由于有X2401L功放，实际+21dbm输出
		SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
	}
}

void ChoiceHalfDuplexMode(u8 mode)
{
	delay_us(500);
	if(mode == RX_MODE)
	{
		CE = 0;
		SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);
		CE = 1;
		delay_us(20);
	}
	else if(mode == TX_MODE)
	{
		CE = 0;
		SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);
		CE = 1;
		delay_us(20);
	}
}
/******************************************************************************************************/
/*函数：unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
/*功能：数据读取后放如rx_buf接收缓冲区中
/******************************************************************************************************/
unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
{
	u8 RxOk = 0;
	setSPIsta(SPI_Read(STATUS));	
	if(getSPIRX_DR())				
	{
		CE = 0; 		
		SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);
		RxOk = 1;
	}
	SPI_RW_Reg(WRITE_REG+STATUS,getSPIsta());   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
	CE = 1;
	delay_us(200);
	return RxOk;
}

/***********************************************************************************************************
/*函数：void nRF24L01_TxPacket(unsigned char * tx_buf)
/*功能：发送 tx_buf中数据
/**********************************************************************************************************/
void nRF24L01_TxPacket(unsigned char * tx_buf)
{
	SPI_RW_Reg(WRITE_REG+STATUS,0xff);
	SPI_RW_Reg(0xE1,0xff);
	CE = 0;		
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			       	
	CE = 1;		 
	delay_us(200);   //CE高电平大于10us才能进入发射模式
}