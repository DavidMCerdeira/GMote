#include "AccelerometerAq.h"

aquisitn accelAq;

SemaphoreHandle_t  accelDrdySemaph;
extern osMessageQId accelFrameReadyMsgQ;

int get_nextFram1(int16_t** buff);

void runAccelGest(void* argument)
{
	volatile int sampleCount = 0;
	volatile int frameCount = 0;
	int firstTime = 1;
	
	int16_t sample[NR_OF_AXES];
	int16_t* ptr[NR_OF_AXES];
	uint32_t i = 0;
	BaseType_t notifRcvd = pdFALSE;
	uint32_t notification;
	int nSamples = 6;
	
	/* infinite cycle */
	while(1)
	{
		/* start aquisition */
		BLUE(1);
		start_accel(HZ_100);
		
		/* continue sampling until condition */
		while((sampleCount < AQ_SIZE)){
			/* stop listening? */
			notifRcvd = xTaskNotifyWait(STOP, 0, &notification, 0);
			if(notifRcvd && (notification & STOP))
				goto EXIT;
			
			/* wait for accelerometer data */
			xSemaphoreTake(accelDrdySemaph, portMAX_DELAY);
			
			/* read 24 samples */
			for(i = 0; i < nSamples; 
					i++, sampleCount++)
			{
				read_sample((uint8_t*)(&sample));
				/* put sample in buffer */
				accelAq.samples[0][accelAq.end] = sample[0];
				accelAq.samples[1][accelAq.end] = sample[1];
				accelAq.samples[2][accelAq.end] = sample[2];
				/* prepare for next sample */
				accelAq.end++;
			}
			
			if(sampleCount > (AQ_SIZE - FRAME_SIZE)){
				break;
			}
			/* reached end of frame? */
				if(nSamples == FRAME_OVERLAP)
						nSamples = 24;
			  else if(get_nextFrame((int16_t**)ptr, &accelAq, &firstTime) != -1){
						/* send frame */
						xQueueSend(accelFrameReadyMsgQ, ptr, 10);
				}
			nSamples = 24;
		}
		
		/* send NULL pointer indicating end of aquisition */
		xQueueSend(accelFrameReadyMsgQ, NULL, 10);
	EXIT:		
		pause_accel();
		sampleCount = 0;
		frameCount = 0;		
		initBuffer(&accelAq);
		firstTime = 1;
		BLUE(0);
		vTaskSuspend(NULL);
	}
}

void initAccelAq(void)
{
	/* configure registers */
	accelInit();
	/* guarantee it's not sampling */
	pause_accel();
	/* prepare buffer */
	initBuffer(&accelAq);
	
	/* Create semaphore */
	accelDrdySemaph = xSemaphoreCreateCounting(7, 0);
	
	/* enbale interrupt */
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

