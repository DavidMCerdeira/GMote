#include "sensorAq.h"

void gPress(void);
void printFrame(int idx);

QueueHandle_t accelFrameReadyMsgQ;
QueueHandle_t gyroFrameReadyMsgQ;
TaskHandle_t accelThreadHandle;
TaskHandle_t gyroThreadHandle;

void aqManager(void* argument)
{
	volatile osEvent event;
	BaseType_t notifRcvd = pdFALSE;
	uint32_t notification;	
	
	/* initialize accelerometer frame ready queue */
	accelFrameReadyMsgQ = xQueueCreate(30, sizeof(uint32_t));
	gyroFrameReadyMsgQ  = xQueueCreate(30, sizeof(uint32_t));
	
	/* init aquisitors */
	initAccelAq();
	initGyroAq();
	
	/* initiate suspended thread */
	xTaskCreate(runAccelGest, "AccelGest", 128, NULL, 0, &accelThreadHandle);
	xTaskCreate(runGyroGest, "GyroGest", 128, NULL, 0, &gyroThreadHandle);
	
	vTaskSuspend(accelThreadHandle);
	vTaskSuspend(gyroThreadHandle);
	
	vTaskPrioritySet(accelThreadHandle, 2);
	vTaskPrioritySet(gyroThreadHandle, 2);
	
	while(1)
	{
		notifRcvd = xTaskNotifyWait(0, 0, &notification, portMAX_DELAY);
		if(notifRcvd == pdTRUE){
			if(notification & GStart)
				gPress();
			else if(notification & EqON)
				/* equilibrium mode */;
		}
	}
}

void gPress(void)
{
	static int nFrames = 0;
	uint32_t accelRes;
	uint32_t gyroRes;
	BaseType_t accelMsgQRcvd = pdFALSE;
	BaseType_t gyroMsgQRcvd = pdFALSE;
	BaseType_t notifRcvd = pdFALSE;
	uint32_t notification;
	
	/* wait for thread to be actualy suspended */
	while(eTaskGetState(accelThreadHandle) != eSuspended){}
	while(eTaskGetState(gyroThreadHandle) != eSuspended){}
	
	/* wake up tasks */
	vTaskResume(accelThreadHandle);
	vTaskResume(gyroThreadHandle);
	
	ORANGE(1);
	while(1){
		/* wait for frame */
		
		/*Verificar que a sequência das duas linhas que se seguem não dão problemas*/
		accelMsgQRcvd = xQueueReceive(accelFrameReadyMsgQ, (void*)&accelRes, portMAX_DELAY);
		gyroMsgQRcvd =  xQueueReceive(gyroFrameReadyMsgQ,  (void*)&gyroRes,  portMAX_DELAY);
		/* check if user released button */
		notifRcvd = xTaskNotifyWait(GStop, 0, &notification, 0);
		

		/* user gesture ended? discard frame */
		if(notifRcvd && (notification & GStop))
		{
			/* order aquisition thread to stop */;
			xTaskNotify(accelThreadHandle, STOP, eSetBits);
			xTaskNotify(gyroThreadHandle,  STOP, eSetBits);
			break;
		}
		/* message received */
		if(accelMsgQRcvd == pdTRUE && gyroMsgQRcvd == pdTRUE){
			/* if end of sampling */
			if((gyroRes) == 0){
				xTaskNotify(accelThreadHandle, STOP, eSetBits);
				break;
			}
			if((accelRes) == 0){
				xTaskNotify(gyroThreadHandle,  STOP, eSetBits);
				break;
			}
			/* we received a frame */
			else if((gyroRes) != (accelRes)){
				xTaskNotify(accelThreadHandle, STOP, eSetBits);
				xTaskNotify(gyroThreadHandle,  STOP, eSetBits);
				error("Error aquiring: different Lenghts", 3);
			}
			else{
				/* deal with it */
				nFrames++;
				printFrame(accelRes);
				//printf("Frame Received!\n");
			}
		}
	}
	
	printf("Received a total of %d frames\n", nFrames);
	nFrames = 0;
	ORANGE(0);
}

void printFrame(int idx)
{
	static int last = 0;	
	int i = 0;
	for(; i < (last + idx); i++)
	{
		printf("%+06hd, %+06hd, %+06hd, %+06hd, %+06hd, %+06hd\n", 
					data[ACCEL_X][i], 
					data[ACCEL_Y][i], 
					data[ACCEL_Z][i],
					data[GYRO_X] [i], 
					data[GYRO_Y] [i], 
					data[GYRO_Z] [i]);
	}
	
	last += idx;
}
