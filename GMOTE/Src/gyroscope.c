#include "gyroscope.h"
#include "stm32f4xx_hal_i2c.h"

#define ADDR 0xD0
#define WHO_AM_I 0X75

extern I2C_HandleTypeDef hi2c1;

void gyroTest(void)
{
	int i = 0;
	HAL_StatusTypeDef error[5];
	uint8_t receive[5];
	uint8_t send[2] = {0x1A, 0x0F};
	
	GREEN(1);
	
	error[0] = HAL_I2C_IsDeviceReady(&hi2c1, ADDR, 1, 100);
	error[1] = HAL_I2C_Mem_Read(&hi2c1, ADDR, WHO_AM_I, 1, &receive[0], 1, 10);
	printf("Who am I? %02X\n", receive[0]);
	
//	error[2] = HAL_I2C_Master_Transmit(&hi2c1, ADDR, send, 2, 10);
//	error[3] = HAL_I2C_Mem_Read(&hi2c1, ADDR, 0x1A, 1, &receive[2], 1, 10);
//	printf("Sent 0x0F\nReceived %02X\n", receive[2]);

	for( i = 0; i < 4; i++)
		if(error[i] != HAL_OK){
			RED(1);
			printf("Error on %d\n", i);
		}
	
	while(1);
}

