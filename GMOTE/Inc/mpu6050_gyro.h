#ifndef _MPU_6050
#define _MPU_6050

/*includes*/
#include "stm32f4xx_hal.h"
#include "stdbool.h"
#include "error.h"

/*defines*/
//PB8     ------> I2C1_SCL
//PB9     ------> I2C1_SDA 
#define MPU_SCL_PIN 	GPIO_PIN_8	//  
#define MPU_SCL_PORT  GPIOB				//	STM32F4 i2c3 
#define MPU_SDA_PIN		GPIO_PIN_9	//	"i2c.h"
#define MPU_SDA_PORT 	GPIOB				//

#define MPU_ADDRESS_LOW 	(0x68 << 1) // By default
#define MPU_ADDRESS_HIGH 	(0x69 << 1) //
#define MPU_CUR_ADDRESS  	MPU_ADDRESS_LOW  //<--

//MPU6050 REGISTERS ADDRESS
/*Only those that are required to make the GMOTE work, 
	plus some others that are relevant for gmote*/
#define MPU_REG_SMPLRTDIV 				0x19 //
#define MPU_REG_CONFIG						0x1A //
#define MPU_REG_GYROCONFIG				0x1C //
#define MPU_REG_FIFOEN						0x23 //
#define MPU_REG_INTPINCFG					0x37 //	CONFIGURATION REGISTERS
#define MPU_REG_INTENABLE					0x38 //
#define MPU_REG_SIGNALPATHRESET		0x68 //
#define MPU_REG_USERCTRL					0x6A //
#define MPU_REG_PWRMGMT1					0x6B //
//#define MPU_REG_PWRMGMT2					0x6C //

/*SAMPLE FREQ DEFS*/
#define GYROOUTPUTRATE 8000
#define SAMPLERATE 100

/*Configures the MPU according to what difined as _MODE*/
#define _FIFO_MODE 1
#define _DATA_READY 0
#define _MODE _DATA_READY //Change here if you want to

#if _MODE == _FIFO_MODE
	#define MPU_REG_SMPLRTDIV_VAL	 			((GYROOUTPUTRATE/SAMPLERATE)-1)
	#define MPU_REG_CONFIG_VAL					0x00
	#define MPU_REG_GYROCONFIG_VAL			0x00
	#define MPU_REG_FIFOEN_VAL					0x70		
	#define MPU_REG_INTPINCFG_VAL				0x40	
	#define MPU_REG_INTENABLE_VAL				0x11		
	#define MPU_REG_SIGNALPATHRESET_VAL	0x04	
	#define MPU_REG_USERCTRL_VAL_FIFOENABLE				0x40
	#define MPU_REG_USERCTRL_VAL_FIFORESET				0x05
#elif _MODE == _DATA_READY
	#define MPU_REG_SMPLRTDIV_VAL				((GYROOUTPUTRATE/SAMPLERATE)-1)
	#define MPU_REG_CONFIG_VAL					0x00		
	#define MPU_REG_GYROCONFIG_VAL			0x00		
	#define MPU_REG_FIFOEN_VAL					0x00		
	#define MPU_REG_INTPINCFG_VAL				0x00		
	#define MPU_REG_INTENABLE_VAL				0x01		
	#define MPU_REG_SIGNALPATHRESET_VAL	0x04	
	#define MPU_REG_USERCTRL_VAL				0x00				

#endif

#define MPU_REG_INTSTATUS					0x3A // 
#define MPU_REG_FIFOCOUNTH				0x72 // 
#define MPU_REG_FIFOCOUNTL				0x73 // READ ONLY REGISTERSS
#define MPU_REG_FIFORW						0x74 // (FIFO ACCESS)
#define MPU_REG_WHOAMI						0x75 // 

#define MPU_REG_GYROXOUTH					0x43 //
#define MPU_REG_GYROXOUTL					0x44 //
#define MPU_REG_GYROYOUTH					0x45 // GYRO OUTPUT REGISTERS
#define MPU_REG_GYROYOUTL					0x46 //
#define MPU_REG_GYROZOUTH					0x47 //
#define MPU_REG_GYROZOUTL					0x48 //

#define MPU_WAKEUP() MPU_Register_Write(MPU_REG_PWRMGMT1, 0x00)
#define MPU_SLEEP()	 MPU_Register_Write(MPU_REG_PWRMGMT1, (0x01 << 6))

#define MPU_FIFORESET() MPU_Register_Write(MPU_REG_USERCTRL, MPU_REG_USERCTRL_VAL)

#define MPU_REGSRESET() MPU_Register_Write(MPU_REG_PWRMGMT1, 0x80)

#define I2C_INIT() MX_I2C3_Init()

#define _HI2C hi2c1

typedef struct{
	uint16_t x;
	uint16_t y;
	uint16_t z;
}MPU_Gyro_OutputSample; 

/*Initialization*/
void MPU_Init(void);

/*Registers basic accessors*/
HAL_StatusTypeDef MPU_Register_Write(const uint8_t regAdd, const uint8_t regValue);
HAL_StatusTypeDef MPU_Register_Read(const uint8_t regAdd, uint8_t* retValue);

/*Gyro output accessors*/
bool MPU_GetGyro_Sample(int16_t* sample);
bool MPU_GetGyro_SampleFIFO(int16_t* sample);
bool MPU_Get_FIFOCount(int* count);
#endif
