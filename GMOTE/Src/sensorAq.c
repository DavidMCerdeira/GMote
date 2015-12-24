#include "sensorAq.h"
#include "pre_processing.h"

void gPress(void);
void printFrame(int idx);

QueueHandle_t accelFrameReadyMsgQ;
QueueHandle_t accelSampleReadyMsgQ;
QueueHandle_t gyroFrameReadyMsgQ;
QueueHandle_t preProcFramReadyMsgQ;

TaskHandle_t accelGestThreadHandle;
TaskHandle_t accelSimpleThreadHandle;

TaskHandle_t gyroThreadHandle;
TaskHandle_t preProcThreadHandle;

void aqManager(void* argument)
{
	volatile osEvent event;
	BaseType_t notifRcvd = pdFALSE;
	uint32_t notification;	
	
	accelFrameReadyMsgQ  = xQueueCreate(30, sizeof(uint32_t)); /* initialize accelerometer frame ready queue */
	accelSampleReadyMsgQ = xQueueCreate(30, sizeof(int16_t)*3); /* initialize accelerometer sampleQ */
	gyroFrameReadyMsgQ   = xQueueCreate(30, sizeof(uint32_t)); /* initialize gyroScope msgQ */
	
	preProcFramReadyMsgQ = xQueueCreate(30, sizeof(uint32_t)); /* initialize pre proc msgQ */
	
	/* init aquisitors */
	initAccelAq();
	initGyroAq();
	
	/* initiate suspended threads */
	xTaskCreate(runAccelGest,   "AccelGest",   128, NULL, 0, &accelGestThreadHandle);
	xTaskCreate(runGyroGest,    "GyroGest",    128, NULL, 0, &gyroThreadHandle);
	xTaskCreate(runAccelSimple, "AccelSimple", 128, NULL, 0, &accelSimpleThreadHandle);
	
	/* initiate pre processing thread; empirically 128 bytes is not enough */
	xTaskCreate(preprocessing, "PreProcessing", 512, NULL, 1, &preProcThreadHandle);
	
	/*suspend lowered priority threads*/
	vTaskSuspend(accelGestThreadHandle);
	vTaskSuspend(gyroThreadHandle);
	vTaskSuspend(accelSimpleThreadHandle);
	
	/*Now that they are suspended we can raise their priority*/
	vTaskPrioritySet(runAccelGest, 2);
	vTaskPrioritySet(gyroThreadHandle, 2);
	vTaskPrioritySet(accelSimpleThreadHandle, 2);
	
	/* infinite cycle */
	while(1)
	{
		/* rececive notification*/
		notifRcvd = xTaskNotifyWait(0, 0, &notification, portMAX_DELAY);
		
		/* notification received */
		if(notifRcvd == pdTRUE){
			/* start gesture?*/
			if(notification & GStart){
				/*gesture mode*/
				gPress();
			}
			/* start equilib? */
			else if(notification & EqON){
				/* equilibrium mode */			
			}
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
	
	/* wait for threads to be actualy suspended */
	while(eTaskGetState(accelGestThreadHandle) != eSuspended){}
	while(eTaskGetState(gyroThreadHandle)  != eSuspended){}
	
	/* wake up tasks */
	vTaskResume(accelGestThreadHandle);
	vTaskResume(gyroThreadHandle);
	
	ORANGE(1);
	while(1){
		
		/* wait for frames */
		accelMsgQRcvd = xQueueReceive(accelFrameReadyMsgQ, (void*)&accelRes, portMAX_DELAY);
		gyroMsgQRcvd =  xQueueReceive(gyroFrameReadyMsgQ,  (void*)&gyroRes,  portMAX_DELAY);
		
		/* check if user stopped gesture */
		notifRcvd = xTaskNotifyWait(GStop, 0, &notification, 0);
		

		/* user gesture ended?*/
		if(notifRcvd && (notification & GStop))
		{
			/* order aquisition thread to stop */;
			xTaskNotify(runAccelGest,      STOP, eSetBits);
			xTaskNotify(gyroThreadHandle,  STOP, eSetBits);
			break;
		}
		/* message received */
		if(accelMsgQRcvd == pdTRUE && gyroMsgQRcvd == pdTRUE){
			/* gyro stoped? */
			if((gyroRes) == 0){
				xTaskNotify(accelGestThreadHandle, STOP, eSetBits);
				break;
			}
			/*accel stoped?*/
			if((accelRes) == 0){
				xTaskNotify(gyroThreadHandle,  STOP, eSetBits);
				break;
			}
			/*something went wrong just cancel everything*/
			else if((gyroRes) != (accelRes)){
				xTaskNotify(accelGestThreadHandle, STOP, eSetBits);
				xTaskNotify(gyroThreadHandle,      STOP, eSetBits);
				printf("Accel %d - Gyro %d\n", accelRes, gyroRes);
				error("Error aquiring: different Lenghts", 3);
			}
			/* we received a frame */
			else{
				/* deal with it */
				nFrames++;
				//printFrame(accelRes);
				xQueueSend(preProcFramReadyMsgQ, &accelRes, 10);
				//printf("Frame Received!\n");
			}
		}
	}	
	//printf("Received a total of %d frames\n", nFrames);
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
