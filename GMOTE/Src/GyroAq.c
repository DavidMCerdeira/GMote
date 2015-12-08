#include "GyroAq.h"

#define FRAME_SAMPLES 24
volatile uint16_t samples[FRAME_SAMPLES][3];

volatile int interruptEn = 0;
osSemaphoreId gyroDrdySemaph;
extern volatile osMessageQId gyroFrameReadyMsgQ;

void gyroGetAq(void);

void  runGyroGest(const void * argument){
	
gyroGetAq();
}

void initGyroAq(void){
	MPU_WAKEUP();
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	//osSemaphoreDel();
	//gyroDrdySemaph = osSemaphoreCreate(osSemaphore(gyroDRDY),AQ_SIZE);
	
}

void gyroGetAq(){
	MPU_Gyro_OutputSample temp, temp2;
	int i;
	
	for(i=0; i<FRAME_SAMPLES; i++){
		MPU_GetGyro_SampleFIFO(&temp);
		MPU_GetGyro_Sample(&temp2);	
		samples[i][0] = temp.x;
		samples[i][1] = temp.y;
		samples[i][2] = temp.z;
	}
}