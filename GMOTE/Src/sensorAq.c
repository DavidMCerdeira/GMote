#include "sensorAq.h"

void gPress(void);
void printFrame(int16_t** buff, int);

osMessageQId accelFrameReadyMsgQ;
osThreadId accelThreadId;

void aqManager(void const * argument)
{
	volatile osEvent event;
	
	/* init aquisitors */
	initAccelAq();
	
	/* accelerometer frame ready queue */
	osMessageQDef(accelFrameReady, 7, int16_t**);
	accelFrameReadyMsgQ = osMessageCreate(osMessageQ(accelFrameReady), NULL);
	
	/* initiate suspended thread */
	osThreadDef(accelTask, runAccelGest, osPriorityHigh, 0, 128);	
	accelThreadId = osThreadCreate(osThread(accelTask), NULL);
	osThreadSuspend(accelThreadId);
	osThreadSetPriority(accelThreadId, 2);	
	
	while(1)
	{
		event = osSignalWait(GStart | EqON, osWaitForever);
		if(event.value.signals & GStart)
			gPress();
		else if(event.value.signals & EqON)
			/* equilibrium mode */;
	}
}

void gPress(void)
{
	volatile osEvent eventAccel;
	volatile osEvent eventUser;
	static int nFrames = 0;
	
	osThreadResume(accelThreadId);
	
	ORANGE(1);
	
	while(1){
		eventAccel = osMessageGet(accelFrameReadyMsgQ, osWaitForever);
		eventUser = osSignalWait(GStop, 0);
		
		/* user gesture ended? discard frame */
		if((eventUser.status == osEventSignal) && (eventUser.value.signals & GStop))
		{
			osSignalSet(accelThreadId, STOP);
			break;
		}
		/* message received */
		if(eventAccel.status == osEventMessage){
			/* if end of sampling */
			if(eventAccel.value.v == NULL){
				break;
			}
			/* we received a frame */
			else{
				nFrames++;
				//printFrame(eventAccel.value.p, nFrames == 0);
				printf("Frame Received!\n");
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
		nrfPrint("%+06hd, %+06hd, %+06hd;\n", buff[0][i], 
																			  buff[1][i], 
																			  buff[2][i]);
	}
}
