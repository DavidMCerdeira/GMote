#include "Accelerometer.h"
#include <stdio.h>

#define CS_HIGH() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
#define CS_LOW()  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);

/***************************************/
#define W_BUFF writeStrInc
#define BUFFSIZE (7)

uint8_t writeStrInc[] = { ACCEL_OUT_XL | 0x80, 0, 0, 0, 0, 0, 0};
/***************************************/

extern SPI_HandleTypeDef hspi1;

void accelConfig(void);
void read_sample(uint8_t* buff);
uint8_t accel_multiRead(uint8_t addr);
uint8_t accel_read(uint8_t addr);
void accel_write(uint8_t addr, uint8_t wat);

/*Fifo mode*/
	#define REG3_CONFIG_FIFO      0x68  				 // Interrupt active high, interrupt pulsed, Enable IT	
	#define REG5_CONFIG_FIFO 		  0xC0  				 // Anti aliasing filter bandwidth 50Hz, +/-2G, self-test, 4-wire interface
	#define REG6_CONFIG_FIFO      0x54				 	 // fifo enabled, ADD_INC, watermark interrupt
	#define FIFO_CTRL_CONFIG_FIFO (0x40 | 0x18) // FIFO stream mode, watermark on 24th sample

/*Data ready*/
	#define REG3_CONFIG_BYTE      0xE8  				 // DRDY IT, Interrupt active high, interrupt pulsed, Enable IT	
	#define REG5_CONFIG_BYTE 		  0xC0  				 // Anti aliasing filter bandwidth 50Hz, +/-2G, self-test, 4-wire interface
	#define REG6_CONFIG_BYTE      0x10				 	 // ADD_INC
	#define FIFO_CTRL_CONFIG_BYTE (0) 					 // FIFO disabled 


inline void accel_fifoEnable(void)
{
	int ret;
	
	accel_write(ACCEL_CTRL_REG5, REG5_CONFIG_FIFO);					
	accel_write(ACCEL_CTRL_REG6, REG6_CONFIG_FIFO);				 
	accel_write(ACCEL_CTRL_REG3, REG3_CONFIG_FIFO);   
	accel_write(ACCEL_FIFO_CTRL, 0x18); // watermark 24th sample, bypass mode to reset FIFO	
	accel_write(ACCEL_FIFO_CTRL, FIFO_CTRL_CONFIG_FIFO);
	
	ret = accel_read(ACCEL_CTRL_REG5);
	if(ret != REG5_CONFIG_FIFO)
		goto ERROR;
	
	ret = accel_read(ACCEL_CTRL_REG6);
	if(ret != REG6_CONFIG_FIFO)
		goto ERROR;
	
	ret = accel_read(ACCEL_CTRL_REG3);
	if(ret != REG3_CONFIG_FIFO)
		goto ERROR;
	
	ret = accel_read(ACCEL_FIFO_CTRL);
	if(ret != FIFO_CTRL_CONFIG_FIFO)
		goto ERROR;
	
	ret = accel_read(ACCEL_WHO_AM_I);
	if(ret != 0x3F)
		goto ERROR;
	
	return;	
	
	ERROR:
		error("Accel configuration failure", 3);
}

inline void accel_byteByByte(void)
{
	int ret;
	
	accel_write(ACCEL_CTRL_REG5, REG5_CONFIG_BYTE);					
	accel_write(ACCEL_CTRL_REG6, REG6_CONFIG_BYTE);				 
	accel_write(ACCEL_CTRL_REG3, REG3_CONFIG_BYTE); 
	accel_write(ACCEL_FIFO_CTRL, FIFO_CTRL_CONFIG_BYTE);
	
	ret = accel_read(ACCEL_CTRL_REG5);
	if(ret != REG5_CONFIG_BYTE)
		goto ERROR;
	
	ret = accel_read(ACCEL_CTRL_REG6);
	if(ret != REG6_CONFIG_BYTE)
		goto ERROR;
	
	ret = accel_read(ACCEL_CTRL_REG3);
	if(ret != REG3_CONFIG_BYTE)
		goto ERROR;
	
	ret = accel_read(ACCEL_FIFO_CTRL);
	if(ret != FIFO_CTRL_CONFIG_BYTE)
		goto ERROR;
	
	ret = accel_read(ACCEL_WHO_AM_I);
	if(ret != 0x3F)
		goto ERROR;
	
	return;	
	
	ERROR:
		error("Accel configuration failure", 3);
}

inline void start_accel(int speed)
{
	
	if((speed < 0x10) || (speed > 0x90)){
		error("Accel invalid frequency", 1);
		return;
	}
	
	accel_write(ACCEL_CTRL_REG4, speed | EN_ALL_AX );
	
	if(accel_read(ACCEL_CTRL_REG4) != (speed | EN_ALL_AX ))
	{
		error("Error configuring speed", 3);
	}
}

inline void pause_accel(void)
{
	/* no sampling */
	accel_write(ACCEL_CTRL_REG4, HZ_0);
}

void accelInit(void)
{
	volatile int ret = 0;

	accel_write(ACCEL_CTRL_REG6, 0x80);		// reboot
	/* give time to reboot */
	HAL_Delay(10);
	
	//accel_fifoEnable();
}

void read_sample(uint8_t* buff)
{
	int i = 0;
	uint8_t ret = 0;
	
	CS_LOW();
	for(i = 0; i < 7; i++)
	{
		ret = accel_multiRead(W_BUFF[i]);

		if(i > 0)
				*(buff + (i-1)) = ret;
	}
	CS_HIGH();
}

uint8_t accel_read(uint8_t addr)
{
	uint8_t c = 0;
	addr |= 0x80;
	
	CS_LOW();
	
	if(HAL_SPI_Transmit(&hspi1, &addr, 1, 1000) != HAL_OK)
		goto ERROR;
	if(HAL_SPI_Receive(&hspi1, &c, 1, 1000) != HAL_OK)
		goto ERROR;
			
	CS_HIGH();
	
	return c;
		
ERROR:
	CS_HIGH();
	error("Accel comunication failure: reading", 2);
	return 0xFF;
}

void accel_write(uint8_t addr, uint8_t wat)
{	
	CS_LOW();
	if(HAL_SPI_Transmit(&hspi1, (uint8_t*)&addr, 1, 100) != HAL_OK)
		goto ERROR;
	if(HAL_SPI_Transmit(&hspi1, (uint8_t*)&wat,  1, 100) != HAL_OK)
		goto ERROR;
	CS_HIGH();
	
	return;
ERROR:
	error("Accel comunication failure: writing", 2);
}

uint8_t accel_multiRead(uint8_t addr)
{
	uint8_t c = 0;	
	addr |= 0x80; //read
	
	if(HAL_SPI_TransmitReceive(&hspi1, &addr, &c, 1, 1000) != HAL_OK){
		CS_HIGH();
		error("Accel comunication failure: multiple-read", 2);
	}		

	return c;
}
