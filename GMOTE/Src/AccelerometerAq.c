#include "AccelerometerAq.h"

aquisitn accelAq;

SemaphoreHandle_t  accelDrdySemaph;
extern QueueHandle_t accelFrameReadyMsgQ;

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
	volatile int sem;
	
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
			sem = xSemaphoreTake(accelDrdySemaph, portMAX_DELAY);
			
			/* read 24 samples */
			for(i = 0; i < FRAME_SIZE; 
					i++, sampleCount++)
			{
				read_sample((uint8_t*)(&sample));
				/* put sample in buffer */
				data[ACCEL_X][accelAq.end] = sample[0];
				data[ACCEL_Y][accelAq.end] = sample[1];
				data[ACCEL_Z][accelAq.end] = sample[2];
				/* prepare for next sample */
				accelAq.end++;
			}
			
			if(sampleCount > (AQ_SIZE - FRAME_SIZE)){
				break;
			}
			/* reached end of frame? */
			/* send frame */
			xQueueSend(accelFrameReadyMsgQ, &i, 10);
		}
		i = 0;
		
		/* send NULL pointer indicating end of aquisition */
		xQueueSend(accelFrameReadyMsgQ, &i, 10);
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
	accelDrdySemaph = xSemaphoreCreateCounting(30, 0);
	
	/* enable interrupt */
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

