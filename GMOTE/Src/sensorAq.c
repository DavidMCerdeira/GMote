#include "sensorAq.h"

void gPress(void);
void printFrame(int16_t** buff1, int16_t** buff2, int firstFrame);

QueueHandle_t accelFrameReadyMsgQ;
QueueHandle_t gyroFrameReadyMsgQ;
TaskHandle_t accelThreadHandle;
TaskHandle_t gyroThreadHandle;

void aqManager(void* argument)
{
	volatile osEvent event;
	BaseType_t notifRcvd = pdFALSE;
	uint32_t notification;
	
	/* init aquisitors */
	initAccelAq();
	initGyroAq();
	
	/* initialize accelerometer frame ready queue */
	accelFrameReadyMsgQ = xQueueCreate(10, sizeof(int16_t*[3]));
	gyroFrameReadyMsgQ = xQueueCreate(10, sizeof(int16_t*[3]));
	
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
	int16_t* accelBuff[3];
	int16_t* gyroBuff[3];
	BaseType_t accelMsgQRcvd = pdFALSE;
	BaseType_t gyroMsgQRcvd = pdFALSE;
	BaseType_t notifRcvd = pdFALSE;
	uint32_t notification;
	
	/* wait for thread to be actualy suspended */
	while(eTaskGetState(accelThreadHandle) != eSuspended){}
	while(eTaskGetState(accelThreadHandle) != eSuspended){}
	
	/* wake up tasks */
	vTaskResume(accelThreadHandle);
	vTaskResume(gyroThreadHandle);
	
	ORANGE(1);
	while(1){
		/* wait for frame */
		
		/*Verificar que a sequência das duas linhas que se seguem não dão problemas*/
		accelMsgQRcvd = xQueueReceive(accelFrameReadyMsgQ, (void*)accelBuff, portMAX_DELAY);
		gyroMsgQRcvd =  xQueueReceive(gyroFrameReadyMsgQ,  (void*)gyroBuff,  portMAX_DELAY);
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
			if(gyroBuff == NULL){
				break;
			}
			if(accelBuff == NULL){
				break;
			}
			/* we received a frame */
			else{
				/* deal with it */
				nFrames++;
				printFrame(accelBuff, gyroBuff, nFrames == 0);
				//printf("Frame Received!\n");
			}
		}
	}
	
	printf("Received a total of %d frames\n", nFrames);
	nFrames = 0;
	ORANGE(0);
}

//void printRawFrame(int16_t** buff, int firstFrame)
//{
//	int i = 0;
//	
//	if(firstFrame)
//	{
//		i = 0;
//		firstFrame = 0;
//	}
//	else 
//		i = FRAME_OVERLAP;
//	
//	for(; i < (FRAME_SIZE + FRAME_OVERLAP); i++)
//	{
//		nrf24l01_txSend(buff[0][i], 0);	
//		nrf24l01_txSend(buff[1][i], 0); 
//		nrf24l01_txSend(buff[2][i], 0);
//	}
//}

void printFrame(int16_t** buff1, int16_t** buff2, int firstFrame)
{
	int i = 0;	
	
	if(firstFrame)
	{
		i = 0;
		firstFrame = 0;
	}
	else 
		i = FRAME_OVERLAP;
	
	for(; i < (FRAME_SIZE + FRAME_OVERLAP); i++)
	{
		printf("%+06hd, %+06hd, %+06hd, %+06hd, %+06hd, %+06hd;\n", 
					buff1[0][i], 
					buff1[1][i], 
					buff1[2][i],
					buff2[0][i], 
					buff2[1][i], 
					buff2[2][i]);
	}
}
