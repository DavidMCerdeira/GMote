#include "sensorAq.h"

void gPress(void);
void printFrame(int16_t** buff, int);

QueueHandle_t accelFrameReadyMsgQ;
TaskHandle_t accelThreadHandle;

void aqManager(void* argument)
{
	volatile osEvent event;
	BaseType_t notifRcvd = pdFALSE;
	uint32_t notification;
	
	/* init aquisitors */
	initAccelAq();
	
	/* initialize accelerometer frame ready queue */
	accelFrameReadyMsgQ = xQueueCreate(10, sizeof(int16_t*[3]));
	
	/* initiate suspended thread */
	xTaskCreate(runAccelGest, "AccelGest", 128, NULL, 0, &accelThreadHandle);
	vTaskSuspend(accelThreadHandle);
	vTaskPrioritySet(accelThreadHandle, 2);
	
	while(1)
	{
		//event = osSignalWait(GStart | EqON, osWaitForever);
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
	volatile int16_t* buff[3];
	BaseType_t msgQRcvd = pdFALSE;
	BaseType_t notifRcvd = pdFALSE;
	uint32_t notification;
	
	vTaskResume(accelThreadHandle);
	
	ORANGE(1);

	while(1){
		/* wait for frame */
		msgQRcvd = xQueueReceive(accelFrameReadyMsgQ, (void*)buff, portMAX_DELAY);
		
		/* check if user released button */
		notifRcvd = xTaskNotifyWait(GStop, 0, &notification, 0);
		
		/* user gesture ended? discard frame */
		if(notifRcvd && (notification & GStop))
		{
			/* order aquisition thread to stop */;
			xTaskNotify(accelThreadHandle, STOP, eSetBits);
			break;
		}
		/* message received */
		if(msgQRcvd == pdTRUE){
			/* if end of sampling */
			if(buff == NULL){
				break;
			}
			/* we received a frame */
			else{
				/* deal with it */
				nFrames++;
				printFrame(buff, nFrames == 0);
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

void printFrame(int16_t** buff, int firstFrame)
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
		printf("%+06hd, %+06hd, %+06hd;\n", buff[0][i], 
																			  buff[1][i], 
																			  buff[2][i]);
	}
}
