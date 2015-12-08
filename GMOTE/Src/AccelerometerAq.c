#include "AccelerometerAq.h"

aquisitn aq;

SemaphoreHandle_t  drdySemaph;
extern osMessageQId accelFrameReadyMsgQ;
int firstTime = 1;

void printBuffer(void);
void initBuffer1(void);
int get_nextFram1(int16_t** buff);

void runAccelGest(void* argument)
{
	volatile int sampleCount = 0;
	volatile int frameCount = 0;
	
	volatile osEvent event;
	int16_t sample[3];
	int16_t* ptr[3];
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
			xSemaphoreTake(drdySemaph, portMAX_DELAY);
			
			/* read 24 samples */
			for(i = 0; i < nSamples; 
					i++, sampleCount++)
			{
				read_sample((uint8_t*)(&sample));
				/* put sample in buffer */
				aq.samples[0][aq.end] = sample[0];
				aq.samples[1][aq.end] = sample[1];
				aq.samples[2][aq.end] = sample[2];
					
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
				aq.end++;	
			}
			nSamples = 24;
		}
		
		/* send NULL pointer indicating end of aquisition */
		xQueueSend(accelFrameReadyMsgQ, NULL, 10);
	EXIT:		
		pause_accel();
		sampleCount = 0;
		frameCount = 0;		
		initBuffer1();
		BLUE(0);
		osThreadSuspend(NULL);
	}
}

void printBuffer(void)
{
	int j = 0;

	for(j = 0; j < AQ_SIZE; j++){
		printf("%+06hd\t%+06hd\t%+06hd\n", aq.samples[0][j], 
																			 aq.samples[1][j], 
																			 aq.samples[2][j]);
	}
}

void initBuffer1(void)
{	
	aq.end = aq.start = 0;
	firstTime = 1;
}

void initAccelAq(void)
{
	/* configure registers */
	accelInit();
	/* garantee it's not sampling */
	pause_accel();
	/* prepare buffer */
	initBuffer1();
	
	/* Create semaphore */
	drdySemaph = xSemaphoreCreateCounting(7, 0);
	
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
	if(aq.start >= (FRAME_OVERLAP - 1)){
		// if there are enough samples to make a frame
		if((aq.end - aq.start) >= (FRAME_SIZE-1)){
			buff[0] = &aq.samples[0][aq.start - FRAME_OVERLAP];
			buff[1] = &aq.samples[1][aq.start - FRAME_OVERLAP];
			buff[2] = &aq.samples[2][aq.start - FRAME_OVERLAP];
			aq.start += FRAME_SIZE;
			goto OK;
		}
	}
	// if it's the first time and there are enough samples to make a frame 
	else if(firstTime && (aq.end - aq.start) >= ((FRAME_SIZE-1) + FRAME_OVERLAP)){
		buff[0] = &aq.samples[0][aq.start];
		buff[1] = &aq.samples[1][aq.start];
		buff[2] = &aq.samples[2][aq.start];
		
		aq.start += FRAME_SIZE + FRAME_OVERLAP;
		firstTime = 0;
		goto OK;
	}
	
	return -1;
	
OK:
	return 0;
}
