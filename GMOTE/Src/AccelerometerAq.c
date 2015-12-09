#include "AccelerometerAq.h"

aquisitn accelAq;

SemaphoreHandle_t  accelDrdySemaph;
extern osMessageQId accelFrameReadyMsgQ;
int firstTime = 1;

int get_nextFram1(int16_t** buff);

void runAccelGest(void* argument)
{
	volatile int sampleCount = 0;
	volatile int frameCount = 0;
	
	int16_t sample[NR_OF_AXES];
	int16_t* ptr[NR_OF_AXES];
	uint32_t i = 0;
	BaseType_t notifRcvd = pdFALSE;
	uint32_t notification;
	int nSamples = 5;
	
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
					
				/* reached end of frame? */
				if((++frameCount) >= FRAME_SIZE)
				{
					/* reset frame counter */
					frameCount = 0;
					/* get next frame if available */
					if(get_nextFram1((int16_t**)ptr) != -1){
						/* send frame */
						xQueueSend(accelFrameReadyMsgQ, ptr, 10);
					}
				}
				/* prepare for next sample */
				accelAq.end++;	
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

// each frame contains FRAME_OVERLAP + FRAME_SIZE elements
// the first samples from the previous frame
// and the rest from the current
// return  0 if ok
// return -1 if not enough samples
// note: a conditional variable should be used in order to avoid polling
int get_nextFram1(int16_t** buff)
{		
	// are there previous samples 
	if(accelAq.start >= (FRAME_OVERLAP - 1)){
		// if there are enough samples to make a frame
		if((accelAq.end - accelAq.start) >= (FRAME_SIZE-1)){
			buff[0] = &accelAq.samples[0][accelAq.start - FRAME_OVERLAP];
			buff[1] = &accelAq.samples[1][accelAq.start - FRAME_OVERLAP];
			buff[2] = &accelAq.samples[2][accelAq.start - FRAME_OVERLAP];
			accelAq.start += FRAME_SIZE;
			goto OK;
		}
	}
	// if it's the first time and there are enough samples to make a frame 
	else if(firstTime && (accelAq.end - accelAq.start) >= ((FRAME_SIZE-1) + FRAME_OVERLAP)){
		buff[0] = &accelAq.samples[0][accelAq.start];
		buff[1] = &accelAq.samples[1][accelAq.start];
		buff[2] = &accelAq.samples[2][accelAq.start];
		
		accelAq.start += FRAME_SIZE + FRAME_OVERLAP;
		firstTime = 0;
		goto OK;
	}
	
	return -1;
	
OK:
	return 0;
}
