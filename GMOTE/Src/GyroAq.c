#include "GyroAq.h"
#include "discoLeds.h"

aquisitn gyroAq;

volatile int interruptEn = 0;
osSemaphoreId gyroDrdySemaph;
extern volatile osMessageQId gyroFrameReadyMsgQ;

void gyroGetAq(void);

void  runGyroGest(void * argument){
	volatile int sampleCount = 0;
	volatile int frameCount = 0;
	int firstTime = 1;
	
	int16_t sample[NR_OF_AXES];
	int16_t* ptr[NR_OF_AXES];
	
	uint32_t i = 0;
	
	BaseType_t notifRcvd = pdFALSE;
	uint32_t notification;
	int nSamples = FRAME_OVERLAP;
	
	while(1){
		/* start aquisition */
		//RED(1);
		MPU_WAKEUP();
		
		while(sampleCount < AQ_SIZE){
			/*stop listening?*/
			notifRcvd = xTaskNotifyWait(STOP, 0, &notification, 0);
			if(notifRcvd && (notification & STOP))
				goto EXIT;
			/* wait for accelerometer data */
			for(i=0; i < nSamples; 
					i++, sampleCount++)
			{
				xSemaphoreTake(gyroDrdySemaph, portMAX_DELAY);
				/* put sample in buffer */
				MPU_GetGyro_Sample(sample);
				gyroAq.samples[0][gyroAq.end] = sample[0];
				gyroAq.samples[1][gyroAq.end] = sample[1];
				gyroAq.samples[2][gyroAq.end] = sample[2];
				/* prepare for next sample */
				gyroAq.end++;
			}
			
			if(sampleCount > (AQ_SIZE - FRAME_SIZE)){
				break;
			}
			
			if(nSamples == FRAME_OVERLAP)
				nSamples = 24;
			else if(get_nextFrame((int16_t**)ptr, &gyroAq, &firstTime) != -1)
					/* send frame */
					xQueueSend(gyroFrameReadyMsgQ, ptr, 10);			
		}
		
		/* send NULL pointer indicating end of aquisition */
		xQueueSend(gyroFrameReadyMsgQ, NULL, 10);
		EXIT:		
		MPU_SLEEP();
		sampleCount = 0;
		frameCount = 0;		
		nSamples = FRAME_OVERLAP;
		initBuffer(&gyroAq);
		firstTime = 1;
		//BLUE(0);
		vTaskSuspend(NULL);
	}
}

void initGyroAq(void)
{
	
	/* Create semaphore */
	gyroDrdySemaph = xSemaphoreCreateCounting(7, 0);
	
	MPU_Initialize();
	/* prepare buffer */
	initBuffer(&gyroAq);
	/* enbale interrupt */
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void gyroGetAq(){
//	MPU_Gyro_OutputSample temp, temp2;
//	int i;
//	
//	for(i=0; i<FRAME_SIZE; i++){
//		MPU_GetGyro_SampleFIFO(&temp);
//		MPU_GetGyro_Sample(&temp2);	
//		sample[0][i] = temp.x;
//		sample[1][i] = temp.y;
//		sample[2][i] = temp.z;
//	}
}

void mpuTest(void)
{
//	int fifoCount;
//	int16_t sample[3];
//	int i = 0;
//	int state = 0;
//	MPU_WAKEUP();
//	
//	while(1)
//	{
//		while(!HAL_GPIO_ReadPin(GPIOB, 6));
//		
//		if(MPU_Get_FIFOCount(&fifoCount)){
//			fifoCount /= 6;
//			GREEN(1);
//		} 
//		else {
//			RED(1);
//		}
//		
//		MPU_GetGyro_SampleFIFO(sample);
//		
//		while(HAL_GPIO_ReadPin(GPIOB, 6));
//	}
}
