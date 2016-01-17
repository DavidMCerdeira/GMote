#include "sensorAq.h"

//#define TRAIN

void gPress(void);
void gEquilib(void);
void printFrame(int idx);

QueueHandle_t accelFrameReadyMsgQ;
QueueHandle_t accelSampleReadyMsgQ;
QueueHandle_t gyroFrameReadyMsgQ;

extern QueueHandle_t preProcFramReadyMsgQ;
extern QueueHandle_t simpleProcFramReadyMsgQ;

extern TaskHandle_t aqManagerHandle;
TaskHandle_t accelGestThreadHandle;
TaskHandle_t accelSimpleThreadHandle;
TaskHandle_t gyroThreadHandle;

uint32_t notification;

int last = 0;

void aqManager(void* argument)
{
	BaseType_t notifRcvd = pdFALSE;
	
	accelFrameReadyMsgQ  = xQueueCreate(15, sizeof(uint32_t)); /* initialize accelerometer frame ready queue */
	accelSampleReadyMsgQ = xQueueCreate(6, sizeof(int16_t)*3); /* initialize accelerometer sampleQ */
	gyroFrameReadyMsgQ   = xQueueCreate(15, sizeof(uint32_t)); /* initialize gyroScope msgQ */
	
	/* init aquisitors */
	initAccelAq();
	initGyroAq();
	
	/* initiate suspended threads */
	xTaskCreate(runAccelGest,   "AccelGest",   128, NULL, 0, &accelGestThreadHandle);
	xTaskCreate(runGyroGest,    "GyroGest",    128, NULL, 0, &gyroThreadHandle);
	xTaskCreate(runAccelSimple, "AccelSimple", 128, NULL, 0, &accelSimpleThreadHandle);
	
	/*suspend lowered priority threads*/
	vTaskSuspend(accelGestThreadHandle);
	vTaskSuspend(gyroThreadHandle);
	vTaskSuspend(accelSimpleThreadHandle);
	
	/*Now that they are suspended we can raise their priority*/
	vTaskPrioritySet(accelGestThreadHandle, AqSensorPriority);
	vTaskPrioritySet(gyroThreadHandle, AqSensorPriority);
	vTaskPrioritySet(accelSimpleThreadHandle, AqSensorPriority);
	

	/* infinite cycle */
	while(1)
	{
		/* rececive notification*/
		notifRcvd = xTaskNotifyWait(0, GStart | GStop | EqON | EqOFF, &notification, portMAX_DELAY);
		
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
				gEquilib();			
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
	
	/* wait for threads to be actualy suspended */
	while(eTaskGetState(accelGestThreadHandle) != eSuspended){}
	while(eTaskGetState(gyroThreadHandle)  != eSuspended){}
	while(eTaskGetState(accelSimpleThreadHandle) != eSuspended){}
	
	/* wake up tasks */
	vTaskResume(accelGestThreadHandle);
	vTaskResume(gyroThreadHandle);
	
	GREEN(1);
	while(1){
		/* wait for frames */
		accelMsgQRcvd = xQueueReceive(accelFrameReadyMsgQ, (void*)&accelRes, 1000);
		gyroMsgQRcvd =  xQueueReceive(gyroFrameReadyMsgQ,  (void*)&gyroRes,  1000);
		
		/* check if user stopped gesture */
		notifRcvd = xTaskNotifyWait(0, GStop, &notification, 0);
		
		/* user gesture ended?*/
		if((notifRcvd == pdTRUE) && (notification & GStop))
		{
			/* order aquisition thread to stop */;
			xTaskNotify(accelGestThreadHandle,      STOP, eSetBits);
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
				xTaskNotify(gyroThreadHandle, STOP, eSetBits);
				//printf("Accel %d - Gyro %d\n", accelRes, gyroRes);
				error("Error aquiring: different Lenghts", 5);
			}
			/* we received a frame */
			else{
				/* deal with it */
				nFrames++;
				#ifndef TRAIN
				xQueueSend(preProcFramReadyMsgQ, &accelRes, 10);
				#endif
			}
		}
		else{
			break;
		}
	}
	gyroRes = 0;

	#ifdef TRAIN
	printFrame(nFrames*FRAME_SIZE);	
	#else 
	xQueueSend(preProcFramReadyMsgQ, &gyroRes, 10);
	#endif

	last = 0;

	nFrames = 0;
	GREEN(0);
}

void printFrame(int idx)
{
	int i = 0;
	for(; i < (last + idx); i++)
	{
		nrfPrint("%+06.0f, %+06.0f, %+06.0f, %+06.0f, %+06.0f, %+06.0f\n", 
					data[i][ACCEL_X], 
					data[i][ACCEL_Y], 
					data[i][ACCEL_Z],
					data[i][GYRO_X], 
					data[i][GYRO_Y], 
					data[i][GYRO_Z]);
	}
	
	
	last += idx;
}

void gEquilib(void)
{
	BaseType_t notifRcvd = pdFALSE;
	BaseType_t accelMsgQRcvd = pdFALSE;
	int16_t Qdata[NR_OF_AXES];
	
	/* wait for threads to be actualy suspended */
	while(eTaskGetState(accelGestThreadHandle) != eSuspended){}
	while(eTaskGetState(gyroThreadHandle)  != eSuspended){}
	while(eTaskGetState(accelSimpleThreadHandle) != eSuspended){}
		
	/* resume task */
	vTaskResume(accelSimpleThreadHandle);
		
	RED(1);
	while(1)
	{
		notifRcvd = accelMsgQRcvd = pdFALSE;
		while((accelMsgQRcvd == pdFALSE) && (notifRcvd == pdFALSE))
		{
			/* wait for data */
			accelMsgQRcvd = xQueueReceive(accelSampleReadyMsgQ, (void*)Qdata, portMAX_DELAY);
			/* stop? */
			notifRcvd = xTaskNotifyWait(0, EqOFF, &notification, 0);
		}
		
		/* No more equilib? */
		if((notifRcvd == pdTRUE) && (notification & EqOFF))
		{
			xTaskNotify(aqManagerHandle, notification & ~EqOFF, eSetBits);
			/* order aquisition thread to stop */;
			xTaskNotify(accelSimpleThreadHandle, STOP, eSetBits);
			break;
		}
		/* Data received? */
		else if(accelMsgQRcvd == pdTRUE){
			xQueueSend(simpleProcFramReadyMsgQ, Qdata, 10);		
		}
	}
	RED(0);
}
