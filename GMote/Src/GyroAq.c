#include "GyroAq.h"
#include "discoLeds.h"

aquisitn gyroAq;

volatile int interruptEn = 0;

SemaphoreHandle_t gyroDrdySemaph;
extern QueueHandle_t gyroFrameReadyMsgQ;

void gyroGetAq(void);

void  runGyroGest(void * argument){
	volatile int sampleCount = 0;
	volatile int frameCount = 0;
	
	int16_t sample[NR_OF_AXES];
	
	uint32_t i = 0;
	
	BaseType_t notifRcvd = pdFALSE;
	BaseType_t semRcvd = pdFALSE;
	uint32_t notification;
	
	while(1){
		/* start aquisition */
		MPU_WAKEUP();
		
		while(sampleCount < AQ_SIZE){			
			/* wait for gyro data */
			for(i=0; i < FRAME_SIZE; i++, sampleCount++)
			{
				while(semRcvd == pdFALSE){
					semRcvd = xSemaphoreTake(gyroDrdySemaph, portMAX_DELAY);
					/*stop listening?*/
					notifRcvd = xTaskNotifyWait(STOP, 0, &notification, 0);
					if(notifRcvd && (notification & STOP)){
						goto EXIT;
					}
				}
				semRcvd = pdFALSE;
				
				/* put sample in buffer */
				if(!MPU_GetGyro_Sample(sample)){
					error("Gyro problems", 1);
				}
				data[gyroAq.end][GYRO_X] = (float)sample[0];
				data[gyroAq.end][GYRO_Y] = (float)sample[1];
				data[gyroAq.end][GYRO_Z] = (float)sample[2];
				/* prepare for next sample */
				gyroAq.end++;
			}
			
			if(sampleCount > (AQ_SIZE - FRAME_SIZE)){
				break;
			}

			xQueueSend(gyroFrameReadyMsgQ, &i, 10);			
		}
		i = 0;
		
		/* send 0 indicating end of aquisition */
		xQueueSend(gyroFrameReadyMsgQ, &i, 10);
		EXIT:		
		MPU_SLEEP();
		sampleCount = 0;
		frameCount = 0;		
		initBuffer(&gyroAq);
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
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

