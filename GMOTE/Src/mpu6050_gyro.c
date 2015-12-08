#include "mpu6050_gyro.h"

extern I2C_HandleTypeDef hi2c1;

void MPU_Init(){
	//I2C_INIT();
	MPU_WAKEUP();
	
	//MPU_Register_Read(MPU_REG_WHOAMI, &retVal);
	
	/*Reset Signal paths for Gyro*/
	MPU_Register_Write(MPU_REG_SIGNALPATHRESET, MPU_REG_SIGNALPATHRESET_VAL);
	
	/*Configuration of the sample rate throuigh sample rate divider*/
	MPU_Register_Write(MPU_REG_SMPLRTDIV, (GYROOUTPUTRATE/SAMPLERATE)-1);
	
	/*Configurates Filter and Sample Rate*/
	MPU_Register_Write(MPU_REG_CONFIG, MPU_REG_CONFIG_VAL);
	
	/*Sample rate at +/-250º/s; Disable Selftest*/
	MPU_Register_Write(MPU_REG_GYROCONFIG, MPU_REG_GYROCONFIG_VAL);
	
	/*Wich Outputs pass to Fifo*/
	MPU_Register_Write(MPU_REG_FIFOEN, MPU_REG_FIFOEN_VAL);
	
	/*Configures Int Pin behavior*/
	MPU_Register_Write(MPU_REG_INTPINCFG, MPU_REG_INTPINCFG_VAL);
	
	/*Enable Interrupts*/
	MPU_Register_Write(MPU_REG_INTENABLE, MPU_REG_INTENABLE_VAL);
	
	/*Enables I2C */
	MPU_Register_Write(MPU_REG_USERCTRL, 0x05);
	MPU_Register_Write(MPU_REG_USERCTRL, 0x40);
	
	/*Configure Interruption*/
	MPU_Register_Write(MPU_REG_INTENABLE, MPU_REG_INTENABLE_VAL);
	
	MPU_SLEEP();
}

bool MPU_GetGyro_Sample(MPU_Gyro_OutputSample* sample){
	uint8_t temp[6];
	
	/*Read Gyro Output registers*/
	if(HAL_I2C_Mem_Read(&_HI2C, MPU_CUR_ADDRESS, MPU_REG_GYROXOUTH, 1, temp, 6, 100) != HAL_OK) 
		return false;
	
	/*Put in the sample struct*/
	sample->x = (temp[0] << 8) | temp[1];
	sample->y = (temp[2] << 8) | temp[3];
	sample->z = (temp[4] << 8) | temp[5];
	
	return true;
}

inline bool MPU_GetGyro_SampleFIFO(MPU_Gyro_OutputSample* sample){
	uint8_t temp[6];
	volatile uint32_t	i;
	
	for(i=0; i<6; i++){
		if(!MPU_Register_Read(MPU_REG_FIFORW, &temp[i]))
				return false;
	}
	/*Put in the sample struct*/
	sample->x = (temp[0] << 8) | temp[1];
	sample->y = (temp[2] << 8) | temp[3];
	sample->z = (temp[4] << 8) | temp[5];
	return true;
}

inline bool MPU_Get_FIFOCount(int *count){
		uint8_t count_H, count_L;
		/*If when reading both High and Low Fifo Count Registers is ok*/
		if(MPU_Register_Read(MPU_REG_FIFOCOUNTL, &count_L) &&		
			 MPU_Register_Read(MPU_REG_FIFOCOUNTH, &count_H)){
					count_H &= 0x0E; //Filter unwanted bits
				 *count = (count_H << 8) | count_L; 
				return true;
		}
		return false;
}

HAL_StatusTypeDef MPU_Register_Write(const uint8_t regAdd, const uint8_t regVal){
	uint8_t d[]={regAdd, regVal};
	return (HAL_I2C_Master_Transmit(&_HI2C,  MPU_CUR_ADDRESS, d, 2, 100) == HAL_OK);
}
 
HAL_StatusTypeDef MPU_Register_Read(const uint8_t regAdd, uint8_t* retValue){
	return (HAL_I2C_Mem_Read(&_HI2C, MPU_CUR_ADDRESS, regAdd, 1, retValue, 1, 100) == HAL_OK);		
}
