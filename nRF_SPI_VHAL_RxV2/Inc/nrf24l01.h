/*
nrf24l01 lib 0x02

copyright (c) Davide Gironi, 2012

References:
  -  This library is based upon nRF24L01 avr lib by Stefan Engelke
     http://www.tinkerer.eu/AVRLib/nRF24L01
  -  and arduino library 2011 by J. Coliz
     http://maniacbug.github.com/RF24

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/

#ifndef _NRF24L01_H_
#define _NRF24L01_H_

#include "nrf24l01registers.h"
#include "stm32f4xx_hal.h"
#include "spi.h"

#define GPIO_CS_CE GPIOD
#define GPIO_Pin_CE GPIO_PIN_0
#define GPIO_Pin_CS GPIO_PIN_1

//#define NRF24L01_TX
#define NRF24L01_RX

#define initSPI() MX_SPI3_Init()

extern SPI_HandleTypeDef hspi3;
#define NRF_HSPI hspi3

//CE and CSN functions
#define nrf24l01_CSNhi() HAL_GPIO_WritePin(GPIO_CS_CE, GPIO_Pin_CS, GPIO_PIN_SET)
#define nrf24l01_CSNlo() HAL_GPIO_WritePin(GPIO_CS_CE, GPIO_Pin_CS, GPIO_PIN_RESET)
#define nrf24l01_CEhi() HAL_GPIO_WritePin(GPIO_CS_CE, GPIO_Pin_CE, GPIO_PIN_SET)
#define nrf24l01_CElo() HAL_GPIO_WritePin(GPIO_CS_CE, GPIO_Pin_CE, GPIO_PIN_RESET)

//power setup
#define NRF24L01_RF24_PA_MIN 1
#define NRF24L01_RF24_PA_LOW 2
#define NRF24L01_RF24_PA_HIGH 3
#define NRF24L01_RF24_PA_MAX 4
#define NRF24L01_RF24_PA NRF24L01_RF24_PA_MAX

//speed setup
#define NRF24L01_RF24_SPEED_250KBPS 1
#define NRF24L01_RF24_SPEED_1MBPS 2
#define NRF24L01_RF24_SPEED_2MBPS 3
#define NRF24L01_RF24_SPEED NRF24L01_RF24_SPEED_2MBPS

//crc setup
#define NRF24L01_RF24_CRC_DISABLED 1
#define NRF24L01_RF24_CRC_8 2
#define NRF24L01_RF24_CRC_16 3
#define NRF24L01_RF24_CRC NRF24L01_RF24_CRC_16

//transmission channel
#define NRF24L01_CH 76

//payload lenght
#define NRF24L01_PAYLOAD 16

//auto ack enabled
#define NRF24L01_ACK 1

//auto retransmit delay and count
#define NRF24L01_RETR ((4 << NRF24L01_REG_ARD) | (7 << NRF24L01_REG_ARC)) //1500uS, 15 times

//enable / disable pipe
#define NRF24L01_ENABLEDP0 1 //pipe 0
//#define NRF24L01_ENABLEDP1 1 //pipe 1
//#define NRF24L01_ENABLEDP2 1 //pipe 2
//#define NRF24L01_ENABLEDP3 1 //pipe 3
//#define NRF24L01_ENABLEDP4 1 //pipe 4
//#define NRF24L01_ENABLEDP5 1 //pipe 5

//address size
#define NRF24L01_ADDRSIZE 5

//pipe address
#define NRF24L01_ADDRP0 {0xE8, 0xE8, 0xF0, 0xF0, 0xE2} //pipe 0, 5 byte address
#define NRF24L01_ADDRP1 {0xC1, 0xC2, 0xC2, 0xC2, 0xC2} //pipe 1, 5 byte address
#define NRF24L01_ADDRP2 {0xC1, 0xC2, 0xC2, 0xC2, 0xC3} //pipe 2, 5 byte address
#define NRF24L01_ADDRP3 {0xC1, 0xC2, 0xC2, 0xC2, 0xC4} //pipe 3, 5 byte address
#define NRF24L01_ADDRP4 {0xC1, 0xC2, 0xC2, 0xC2, 0xC5} //pipe 4, 5 byte address
#define NRF24L01_ADDRP5 {0xC1, 0xC2, 0xC2, 0xC2, 0xC6} //pipe 5, 5 byte address
#define NRF24L01_ADDRTX {0xE8, 0xE8, 0xF0, 0xF0, 0xE2} //tx default address*/

#define nRF24l01_IRQ    GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8)

extern void nrf24l01_init(void);
extern uint8_t nrf24l01_getstatus(void);
extern uint8_t nrf24l01_readready(uint8_t* pipe);
extern void nrf24l01_read(uint8_t *data);
extern uint8_t nrf24l01_write(uint8_t *data);
extern void nrf24l01_setrxaddr(uint8_t channel, uint8_t *addr);
extern void nrf24l01_settxaddr(uint8_t *addr);
extern void nrf24l01_printinfo(void);
//void initSPI(void);
int rx_receive(char* bufferin);
int tx_send(char* str, char pipe);

void nrf24l01_writeregister(uint8_t, uint8_t);
#endif
