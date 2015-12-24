#include "AccelerometerAq.h"

aquisitn accelAq;

SemaphoreHandle_t  accelDrdySemaph;
extern QueueHandle_t accelFrameReadyMsgQ;

int get_nextFram1(int16_t** buff);

void runAccelGest(void* argument)
{
	volatile int sampleCount = 0;
	volatile int frameCount = 0;
	
	int16_t sample[NR_OF_AXES];
	uint32_t i = 0;
	BaseType_t notifRcvd = pdFALSE;
	uint32_t notification;
	BaseType_t received = pdFALSE;
	
	/* infinite cycle */
	while(1)
	{
		/* start aquisition */
		BLUE(1);
		
		/*mutex? i think so*/		
		accel_fifoEnable();
		start_accel(HZ_100);	
		
		/* continue sampling until condition */
		while((sampleCount < AQ_SIZE)){
			/* stop listening? */
			notifRcvd = xTaskNotifyWait(STOP, 0, &notification, 0);
			/* stop aquiring? */
			if(notifRcvd && (notification & STOP)){
				goto EXIT;
			}
			
			/* wait for accelerometer data */
			received = xSemaphoreTake(accelDrdySemaph, portMAX_DELAY);
			/* received data? */
			if(received == pdTRUE){
				received = pdFALSE;
				
				/* read FRAME_SIZE samples, and increment global counter */
				for(i = 0; i < FRAME_SIZE; i++, sampleCount++)
				{
					read_sample((uint8_t*)(&sample));
					/* put sample in buffer */
					data[accelAq.end][ACCEL_X] = (float)sample[0];
					data[accelAq.end][ACCEL_Y] = (float)sample[1];
					data[accelAq.end][ACCEL_Z] = (float)sample[2];
					/* prepare for next sample */
					accelAq.end++;
				}
				
				/* reached end of frame? */
				if(sampleCount > (AQ_SIZE - FRAME_SIZE)){
					/*leave cycle*/
					break;
				}
				
				/* send frame */
				xQueueSend(accelFrameReadyMsgQ, &i, 10);
			}
		}
		i = 0;
		
		/* send 0 indicating end of aquisition */
		xQueueSend(accelFrameReadyMsgQ, &i, 10);
		
	EXIT:
		/*pause accelerometer*/
		pause_accel();
		/* reset variables */
		sampleCount = 0;
		frameCount = 0;		
		initBuffer(&accelAq);
		BLUE(0);
		/* go to sleep after hard work */
		vTaskSuspend(NULL);
	}
}

void runAccelSimple(void* argument)
{
	int leave = 0;
	BaseType_t receivedSem = pdFALSE;
	BaseType_t receivedNotify = pdFALSE;
	uint32_t notification;
	int16_t sample[NR_OF_AXES];
	
	while(1){
		/*mutex? i think so*/
		accel_byteByByte();
		start_accel(HZ_6_25);
		
		while(!leave){
			/* wait for data or notfication*/
			while((receivedSem == pdFALSE) && (receivedNotify == pdFALSE)){
				receivedSem = xSemaphoreTake(accelDrdySemaph, portMAX_DELAY);
			}
			
			/* data? */
			if(receivedSem == pdTRUE)
			{
				/* read sample */
				read_sample((uint8_t*)(&sample));				
				/* send sample in Q */
				xQueueSend(accelFrameReadyMsgQ, sample, 10);
			}
			/* notification*/
			else if(receivedNotify == pdTRUE)
			{
				/*read contents then leave*/
				leave = 1;
			}			
		}
		/* reset flag */
		leave = 0;
		/* pause accel */
		pause_accel();
		/* go to sleep, sweet dreams */
		vTaskSuspend(NULL);		
	}
}

void initAccelAq(void)
{
	/* init accel */
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
