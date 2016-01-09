/*
nrf24l01 lib 0x02

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/

#include "nrf24l01.h"

//address variables
static uint8_t nrf24l01_addr0[NRF24L01_ADDRSIZE] = NRF24L01_ADDRP0;
static uint8_t nrf24l01_addrtx[NRF24L01_ADDRSIZE] = NRF24L01_ADDRP0;

unsigned char SPI_Send(unsigned char dat);

int nrf24l01_txSend(char* str, char pipe){
	uint8_t writeret;
		
	//write buffer
	writeret = nrf24l01_write((uint8_t*)str);

	if(writeret == 1) {
		return 1;
	}

	return 0;
}

int rx_receive(char* bufferin){
	uint8_t pipe = 0;
	
	if(nrf24l01_readReady(&pipe)) {
		nrf24l01_read((uint8_t*) bufferin);
		return 1;
	}
	return 0;
}

/*
 * read one register
 */
uint8_t nrf24l01_readregister(uint8_t reg) {
	uint8_t result;
	nrf24l01_CSNlo(); //low CSN
	SPI_Send(NRF24L01_CMD_R_REGISTER | (NRF24L01_CMD_REGISTER_MASK & reg));
	result = SPI_Send(NRF24L01_CMD_NOP); //read write register
	
	nrf24l01_CSNhi(); //high CSN
		return result;
}

/*
 * read many registers
 */
void nrf24l01_readregisters(uint8_t reg, uint8_t *value, uint8_t len) {
	uint8_t i = 0;
	nrf24l01_CSNlo(); //low CSN
	SPI_Send(NRF24L01_CMD_R_REGISTER | (NRF24L01_CMD_REGISTER_MASK & reg));
	
	for(i=0; i<len; i++)
		value[i] = SPI_Send(NRF24L01_CMD_NOP); //read write register
	
	nrf24l01_CSNhi(); //high CSN
}

/*
 * write one register
 */
void nrf24l01_writeRegister(uint8_t reg, uint8_t value) {
	nrf24l01_CSNlo(); //low CSN
	SPI_Send(NRF24L01_CMD_W_REGISTER | (NRF24L01_CMD_REGISTER_MASK & reg));
	SPI_Send(value); //write register
	
	nrf24l01_CSNhi(); //high CSN
}

/*
 * write many registers
 */
void nrf24l01_writeRegisters(uint8_t reg, uint8_t *value, uint8_t len) {
	uint8_t i = 0;
	nrf24l01_CSNlo(); //low CSN
		
	SPI_Send(NRF24L01_CMD_W_REGISTER | (NRF24L01_CMD_REGISTER_MASK & reg));
		
	for(i=0; i<len; i++)
		 SPI_Send(value[i]); //write register
	
	nrf24l01_CSNhi(); //high CSN
}

/*
 * reverse an array, NRF24L01 expects LSB first
 */
void nrf24l01_revaddress(uint8_t *addr, uint8_t *addrrev) {
	//reverse address
	uint8_t i = 0;
	
	for(i=0; i<NRF24L01_ADDRSIZE; i++)
		memcpy(&addrrev[i], &addr[NRF24L01_ADDRSIZE-1-i], 1);
}

/*
 * set rx address
 */
void nrf24l01_setRxAddr(uint8_t pipe, uint8_t *addr) {
	uint8_t addrrev[NRF24L01_ADDRSIZE];
	
	if(pipe == 0) {
		memcpy(&nrf24l01_addr0, addr, NRF24L01_ADDRSIZE); //cache address
		nrf24l01_revaddress(addr, (uint8_t *)addrrev);
			nrf24l01_writeRegisters(NRF24L01_REG_RX_ADDR_P0, addrrev, NRF24L01_ADDRSIZE);
	}
}

/*
 * set tx address
 */
void nrf24l01_setTxAddr(uint8_t *addr) {	
	uint8_t addrrev[NRF24L01_ADDRSIZE];
	memcpy(&nrf24l01_addrtx, addr, NRF24L01_ADDRSIZE); //cache address

	nrf24l01_revaddress(addr, (uint8_t *)addrrev);
	nrf24l01_writeRegisters(NRF24L01_REG_RX_ADDR_P0, addrrev, NRF24L01_ADDRSIZE); //set rx address for ack on pipe 0
	nrf24l01_writeRegisters(NRF24L01_REG_TX_ADDR, addrrev, NRF24L01_ADDRSIZE); //set tx address
}

/*
 * flush RX fifo
 */
void nrf24l01_flushRXfifo(void) {
	nrf24l01_CSNlo(); //low CSN
	SPI_Send(NRF24L01_CMD_FLUSH_RX);
	
	nrf24l01_CSNhi(); //high CSN
}

/*
 * flush RX fifo
 */
void nrf24l01_flushTXfifo(void) {
	nrf24l01_CSNlo(); //low CSN
	SPI_Send(NRF24L01_CMD_FLUSH_TX);
	
	nrf24l01_CSNhi(); //high CSN
}

/*
 * set chip as RX
 */
void nrf24l01_setRX(void) {
	nrf24l01_setRxAddr(0, nrf24l01_addr0); //restore pipe 0 address
	nrf24l01_writeRegister(NRF24L01_REG_CONFIG, nrf24l01_readregister(NRF24L01_REG_CONFIG) | (1<<NRF24L01_REG_PRIM_RX)); //prx mode
	nrf24l01_writeRegister(NRF24L01_REG_CONFIG, nrf24l01_readregister(NRF24L01_REG_CONFIG) | (1<<NRF24L01_REG_PWR_UP)); //power up
	nrf24l01_writeRegister(NRF24L01_REG_STATUS, (1<<NRF24L01_REG_RX_DR) | (1<<NRF24L01_REG_TX_DS) | (1<<NRF24L01_REG_MAX_RT)); //reset status
	nrf24l01_flushRXfifo(); //flush rx fifo
	nrf24l01_flushTXfifo(); //flush tx fifo
	nrf24l01_CEhi(); //start listening
	HAL_Delay(1); //_delay_us(150); //wait for the radio to power up
}

/*
 * set chip as TX
 */
void nrf24l01_setTX(void) {
	nrf24l01_CElo(); //stop listening
	nrf24l01_writeRegister(NRF24L01_REG_CONFIG, nrf24l01_readregister(NRF24L01_REG_CONFIG) & ~(1<<NRF24L01_REG_PRIM_RX)); //ptx mode
	nrf24l01_writeRegister(NRF24L01_REG_CONFIG, nrf24l01_readregister(NRF24L01_REG_CONFIG) | (1<<NRF24L01_REG_PWR_UP)); //power up
	nrf24l01_writeRegister(NRF24L01_REG_STATUS, (1<<NRF24L01_REG_RX_DR) | (1<<NRF24L01_REG_TX_DS) | (1<<NRF24L01_REG_MAX_RT)); //reset status
	
	nrf24l01_flushTXfifo(); //flush tx fifo
	HAL_Delay(1);  //_delay_us(150); //wait for the radio to power up
}

void nrf24l01_printInfo(void) {
	printf("info\n");
	printf("STATUS: %02X\n", nrf24l01_getStatus());
	printf("CONFIG: %02X\n", nrf24l01_readregister(NRF24L01_REG_CONFIG));
	printf("RF_CH: %02X\n", nrf24l01_readregister(NRF24L01_REG_RF_CH));
	printf("RF_SETUP: %02X\n", nrf24l01_readregister(NRF24L01_REG_RF_SETUP));
	printf("EN_AA: %02X\n", nrf24l01_readregister(NRF24L01_REG_EN_AA));
	printf("EN_RXADDR: %02X\n", nrf24l01_readregister(NRF24L01_REG_EN_RXADDR));
	printf("SETUP_RETR: %02X\n", nrf24l01_readregister(NRF24L01_REG_SETUP_RETR));
	printf("SETUP_AW: %02X\n", nrf24l01_readregister(NRF24L01_REG_SETUP_AW));
	printf("OBSERVE_TX: %02X\n", nrf24l01_readregister(NRF24L01_REG_OBSERVE_TX));
	printf("\n");
}


/*
 * get status register
 */
uint8_t nrf24l01_getStatus(void) {
	uint8_t status = 0;
	nrf24l01_CSNlo(); //low CSN
	status = SPI_Send(NRF24L01_CMD_NOP); //get status, send NOP request
	nrf24l01_CSNhi(); //high CSN
	//printf("getstatus(): %02X\n",status);
	return status;
}

/*
 * check if there is data ready
 */
uint8_t nrf24l01_readReady(uint8_t* pipe) {
		uint8_t status;
		uint8_t ret;
		status = nrf24l01_getStatus();
	
		ret = status & (1 << NRF24L01_REG_RX_DR);
	
		if(ret) {
			//get the pipe number
			if(pipe)
				*pipe = (status >> NRF24L01_REG_RX_P_NO) & 7;
		}
		
		return ret;
}

/*
 * get data
 */
void nrf24l01_read(uint8_t *data) {
	uint8_t i = 0;
	
	//read rx register
	nrf24l01_CSNlo(); //low CSN
	SPI_Send(NRF24L01_CMD_R_RX_PAYLOAD);
	
	for(i=0; i<NRF24L01_PAYLOAD; i++)
		data[i] = SPI_Send(NRF24L01_CMD_NOP);
	
	nrf24l01_CSNhi(); //high CSN
	//reset register
	nrf24l01_writeRegister(NRF24L01_REG_STATUS, (1<<NRF24L01_REG_RX_DR));
	//handle ack payload receipt
	
	if (nrf24l01_getStatus() & (1<<NRF24L01_REG_TX_DS))
		nrf24l01_writeRegister(NRF24L01_REG_STATUS, (1<<NRF24L01_REG_TX_DS));
}

/*
 * put data
 */
uint8_t nrf24l01_write(uint8_t *data) {
	uint8_t i = 0;
	uint8_t ret = 0;

	//set tx mode
	nrf24l01_setTX();

	//write data
	nrf24l01_CSNlo(); 	//low CSN
	SPI_Send(NRF24L01_CMD_W_TX_PAYLOAD);
	
	for (i=0; i<NRF24L01_PAYLOAD; i++)
		SPI_Send(data[i]);
	
	nrf24l01_CSNhi(); 	//high CSN
	//start transmission
	nrf24l01_CEhi(); 		//high CE
	
	usDelay(15); //_delay_us(15); 
		
	nrf24l01_CElo(); 		//low CE

	//stop if max_retries reached or send is ok
	do {
		usDelay(10); //_delay_us(10);
	}
	while( !(nrf24l01_getStatus() & (1<<NRF24L01_REG_MAX_RT | 1<<NRF24L01_REG_TX_DS)) );

	if(nrf24l01_getStatus() & 1<<NRF24L01_REG_TX_DS)
		ret = 1;
		
	//reset PLOS_CNT
	nrf24l01_writeRegister(NRF24L01_REG_RF_CH, NRF24L01_CH);

	//power down
	nrf24l01_writeRegister(NRF24L01_REG_CONFIG, nrf24l01_readregister(NRF24L01_REG_CONFIG) & ~(1<<NRF24L01_REG_PWR_UP));

	//set rx mode
	//nrf24l01_setRX();

	return ret;
}

/*
 * set power level
 */
void nrf24l01_setpalevel(void) {
	uint8_t setup = nrf24l01_readregister(NRF24L01_REG_RF_SETUP);
	setup &= ~((1<<NRF24L01_REG_RF_PWR_LOW) | (1<<NRF24L01_REG_RF_PWR_HIGH));

	if (NRF24L01_RF24_PA == NRF24L01_RF24_PA_MAX) {
		setup |= (1<<NRF24L01_REG_RF_PWR_LOW) | (1<<NRF24L01_REG_RF_PWR_HIGH);
	} else if (NRF24L01_RF24_PA == NRF24L01_RF24_PA_HIGH) {
		setup |= (1<<NRF24L01_REG_RF_PWR_HIGH) ;
	} else if (NRF24L01_RF24_PA == NRF24L01_RF24_PA_LOW) {
		setup |= (1<<NRF24L01_REG_RF_PWR_LOW);
	} else if (NRF24L01_RF24_PA == NRF24L01_RF24_PA_MIN) {
	} else {
		//default is max power
		setup |= (1<<NRF24L01_REG_RF_PWR_LOW) | (1<<NRF24L01_REG_RF_PWR_HIGH);
	}

	nrf24l01_writeRegister(NRF24L01_REG_RF_SETUP, setup);
}

/*
 * set datarate
 */
void nrf24l01_setdatarate(void) {
	uint8_t setup = nrf24l01_readregister(NRF24L01_REG_RF_SETUP) ;

	setup &= ~((1<<NRF24L01_REG_RF_DR_LOW) | (1<<NRF24L01_REG_RF_DR_HIGH));
	if(NRF24L01_RF24_SPEED == NRF24L01_RF24_SPEED_250KBPS) {
		setup |= (1<<NRF24L01_REG_RF_DR_LOW);
	} else {
		if (NRF24L01_RF24_SPEED == NRF24L01_RF24_SPEED_2MBPS) {
			setup |= (1<<NRF24L01_REG_RF_DR_HIGH);
		} else if (NRF24L01_RF24_SPEED == NRF24L01_RF24_SPEED_2MBPS) {
		} else {
			//default is 1Mbps
		}
	}

	nrf24l01_writeRegister(NRF24L01_REG_RF_SETUP, setup);
}

/*
 * set crc length
 */
void nrf24l01_setcrclength(void) {
	uint8_t config = nrf24l01_readregister(NRF24L01_REG_CONFIG) & ~((1<<NRF24L01_REG_CRCO) | (1<<NRF24L01_REG_EN_CRC));

	if (NRF24L01_RF24_CRC == NRF24L01_RF24_CRC_DISABLED) {
		//nothing
	} else if (NRF24L01_RF24_CRC == NRF24L01_RF24_CRC_8) {
		config |= (1<<NRF24L01_REG_EN_CRC);
	} else if (NRF24L01_RF24_CRC == NRF24L01_RF24_CRC_16) {
		config |= (1<<NRF24L01_REG_EN_CRC);
		config |= (1<<NRF24L01_REG_CRCO);
	} else {
		//default is disabled
	}

	nrf24l01_writeRegister(NRF24L01_REG_CONFIG, config);
}

unsigned char SPI_Send(unsigned char dat)
{
	unsigned char rcvd;
	if(HAL_SPI_TransmitReceive(&NRF_HSPI, (uint8_t*)&dat, (uint8_t*)&rcvd, 1, 30) != HAL_OK){
		error("NRF problem writing", 3);
	}
	return rcvd;
}
/*
 * init nrf24l01
 */
void nrf24l01_Init(void) {
		uint8_t config;
		uint8_t addrtx0[NRF24L01_ADDRSIZE] = NRF24L01_ADDRP0;

		nrf24l01_CElo(); //low CE
		nrf24l01_CSNhi(); //high CSN

		HAL_Delay(5); //_delay_ms(5); //wait for the radio to init
	
		nrf24l01_setpalevel(); //set power level
		nrf24l01_setdatarate(); //set data rate
		nrf24l01_setcrclength(); //set crc length
		nrf24l01_writeRegister(NRF24L01_REG_SETUP_RETR, NRF24L01_RETR); // set retries
		nrf24l01_writeRegister(NRF24L01_REG_DYNPD, 0); //disable dynamic payloads
		nrf24l01_writeRegister(NRF24L01_REG_RF_CH, NRF24L01_CH); //set RF channel

	//payload size
	#if NRF24L01_ENABLEDP0 == 1
		nrf24l01_writeRegister(NRF24L01_REG_RX_PW_P0, NRF24L01_PAYLOAD);
	#endif
	#if NRF24L01_ENABLEDP1 == 1
		nrf24l01_writeRegister(NRF24L01_REG_RX_PW_P1, NRF24L01_PAYLOAD);
	#endif
	#if NRF24L01_ENABLEDP2 == 1
		nrf24l01_writeRegister(NRF24L01_REG_RX_PW_P2, NRF24L01_PAYLOAD);
	#endif
	#if NRF24L01_ENABLEDP3 == 1
		nrf24l01_writeRegister(NRF24L01_REG_RX_PW_P3, NRF24L01_PAYLOAD);
	#endif
	#if NRF24L01_ENABLEDP4 == 1
		nrf24l01_writeRegister(NRF24L01_REG_RX_PW_P4, NRF24L01_PAYLOAD);
	#endif
	#if NRF24L01_ENABLEDP5 == 1
		nrf24l01_writeRegister(NRF24L01_REG_RX_PW_P5, NRF24L01_PAYLOAD);
	#endif

	//enable pipe
	nrf24l01_writeRegister(NRF24L01_REG_EN_RXADDR, 0);
	#if NRF24L01_ENABLEDP0 == 1
		nrf24l01_writeRegister(NRF24L01_REG_EN_RXADDR, nrf24l01_readregister(NRF24L01_REG_EN_RXADDR) | (1<<NRF24L01_REG_ERX_P0));
	#endif
	#if NRF24L01_ENABLEDP1 == 1
		nrf24l01_writeRegister(NRF24L01_REG_EN_RXADDR, nrf24l01_readregister(NRF24L01_REG_EN_RXADDR) | (1<<NRF24L01_REG_ERX_P1));
	#endif
	#if NRF24L01_ENABLEDP2 == 1
		nrf24l01_writeRegister(NRF24L01_REG_EN_RXADDR, nrf24l01_readregister(NRF24L01_REG_EN_RXADDR) | (1<<NRF24L01_REG_ERX_P2));
	#endif
	#if NRF24L01_ENABLEDP3 == 1
		nrf24l01_writeRegister(NRF24L01_REG_EN_RXADDR, nrf24l01_readregister(NRF24L01_REG_EN_RXADDR) | (1<<NRF24L01_REG_ERX_P3));
	#endif
	#if NRF24L01_ENABLEDP4 == 1
		nrf24l01_writeRegister(NRF24L01_REG_EN_RXADDR, nrf24l01_readregister(NRF24L01_REG_EN_RXADDR) | (1<<NRF24L01_REG_ERX_P4));
	#endif
	#if NRF24L01_ENABLEDP5 == 1
		nrf24l01_writeRegister(NRF24L01_REG_EN_RXADDR, nrf24l01_readregister(NRF24L01_REG_EN_RXADDR) | (1<<NRF24L01_REG_ERX_P5));
	#endif

	//auto ack
	#if NRF24L01_ACK == 1
		nrf24l01_writeRegister(NRF24L01_REG_EN_AA, nrf24l01_readregister(NRF24L01_REG_EN_AA) | (1<<NRF24L01_REG_ENAA_P0));
		nrf24l01_writeRegister(NRF24L01_REG_EN_AA, nrf24l01_readregister(NRF24L01_REG_EN_AA) | (1<<NRF24L01_REG_ENAA_P1));
		nrf24l01_writeRegister(NRF24L01_REG_EN_AA, nrf24l01_readregister(NRF24L01_REG_EN_AA) | (1<<NRF24L01_REG_ENAA_P2));
		nrf24l01_writeRegister(NRF24L01_REG_EN_AA, nrf24l01_readregister(NRF24L01_REG_EN_AA) | (1<<NRF24L01_REG_ENAA_P3));
		nrf24l01_writeRegister(NRF24L01_REG_EN_AA, nrf24l01_readregister(NRF24L01_REG_EN_AA) | (1<<NRF24L01_REG_ENAA_P4));
		nrf24l01_writeRegister(NRF24L01_REG_EN_AA, nrf24l01_readregister(NRF24L01_REG_EN_AA) | (1<<NRF24L01_REG_ENAA_P5));
	#else
		nrf24l01_writeRegister(NRF24L01_REG_EN_AA, nrf24l01_readregister(NRF24L01_REG_EN_AA) & ~(1<<NRF24L01_REG_ENAA_P0));
		nrf24l01_writeRegister(NRF24L01_REG_EN_AA, nrf24l01_readregister(NRF24L01_REG_EN_AA) & ~(1<<NRF24L01_REG_ENAA_P1));
		nrf24l01_writeRegister(NRF24L01_REG_EN_AA, nrf24l01_readregister(NRF24L01_REG_EN_AA) & ~(1<<NRF24L01_REG_ENAA_P2));
		nrf24l01_writeRegister(NRF24L01_REG_EN_AA, nrf24l01_readregister(NRF24L01_REG_EN_AA) & ~(1<<NRF24L01_REG_ENAA_P3));
		nrf24l01_writeRegister(NRF24L01_REG_EN_AA, nrf24l01_readregister(NRF24L01_REG_EN_AA) & ~(1<<NRF24L01_REG_ENAA_P4));
		nrf24l01_writeRegister(NRF24L01_REG_EN_AA, nrf24l01_readregister(NRF24L01_REG_EN_AA) & ~(1<<NRF24L01_REG_ENAA_P5));
	#endif

	//rx address
	nrf24l01_setRxAddr(0, nrf24l01_addr0);

	//tx address
	nrf24l01_setTxAddr(nrf24l01_addrtx);
	
	
	#ifdef NRF24L01_RX
		nrf24l01_setRX(); //set rx mode
	#endif
	#ifdef NRF24L01_TX
		nrf24l01_setTX(); //set tx mode
	#endif
	
	config = nrf24l01_readregister(NRF24L01_REG_CONFIG) & ~((1<<NRF24L01_REG_MASK_MAX_RT) | (1<<NRF24L01_REG_MASK_TX_DS) | (1<<NRF24L01_REG_MASK_RX_DR));
	config |= ((1<<NRF24L01_REG_MASK_MAX_RT) | (1<<NRF24L01_REG_MASK_TX_DS));
	nrf24l01_writeRegister(NRF24L01_REG_CONFIG, config);
	
	nrf24l01_setTxAddr(addrtx0);
}

