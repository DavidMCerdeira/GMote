#include "pre_processing.h"

extern QueueHandle_t framesRdy;
extern QueueHandle_t likelyGest;
extern QueueHandle_t communicationMsgQ;

QueueHandle_t preProcFramReadyMsgQ;
QueueHandle_t simpleProcFramReadyMsgQ;

TaskHandle_t simpleProcTaskHandle;

void printIdx(unsigned int* idx);
void simpleProc(void *arg);
void gestReconResult(void *arg);

extern float deita[120][6];

#define buffer_that_holds_the_data data

#define gest_processing_init() HMM_Init()

void processing_init()
{
	/* initialize pre proc msgQ */
	preProcFramReadyMsgQ  = xQueueCreate(30, sizeof(uint32_t)); 
	/* initialize simple proc msgQ */
	simpleProcFramReadyMsgQ = xQueueCreate(30, sizeof(int32_t)*3); 
	
	/* init codebook */
	codeBook_init();
	/* init HMM */
	gest_processing_init();
	
	/* create thread to deal with equilibrium mode */
	xTaskCreate(simpleProc, "SimpleProcessing", 128, NULL, SimpleProcPrioity, &simpleProcTaskHandle);
}

void preprocessing(void *arg)
{
	unsigned int *idx;
	BaseType_t preProcMsgRcvd = pdFALSE;
	int aqSensorRes = 0;
	static int begin = 0;
	
	/* init */
	processing_init();
	
	while(1){
		/*Receive frame for converting*/
		while(preProcMsgRcvd == pdFALSE){
			preProcMsgRcvd = xQueueReceive(preProcFramReadyMsgQ, (void*)&aqSensorRes, portMAX_DELAY);
		}
		/* reset flag */
		preProcMsgRcvd = pdFALSE;
		
		if(aqSensorRes != 0)
		{
			/*convert data matrix*/
			idx = codebook_vecToIdx((float**)&buffer_that_holds_the_data[begin],  begin + aqSensorRes, 6);
			/*save last value*/
			begin += aqSensorRes;
			/*send decoded data*/
			printIdx(idx);
		}
		else
		{
			begin = 0;
			idx = NULL;
		}
		
		xQueueSend(framesRdy, &idx, 10);
	}
}

void gestReconResult(void *arg)
{
	BaseType_t QRes;
	gest Gesture = pictures;
	int cmd;
	
	while(QRes == pdFALSE){
		QRes = xQueueReceive(likelyGest, (void*)&Gesture, portMAX_DELAY);
	}
	QRes = pdFALSE;
	
	if(Gesture == pictures){
		cmd = CMD_PIC;
	}
	else if(Gesture == video){
		cmd = CMD_VID;
	}
	else if(Gesture == music){
		cmd = CMD_MUS;
	}
	else if(Gesture == settings){
		cmd = CMD_SS;
	}
	else if(Gesture == play_pause){
		cmd = CMD_PP;
	}
	else if(Gesture == next){
		cmd = CMD_NXT;
	}
	else if(Gesture == previous){
		cmd = CMD_PRV;
	}
	else{
		cmd = 0;
	}
	
	printf("%d ", Gesture);
	
	xQueueSend(communicationMsgQ, &cmd, 10);
}

void simpleProc(void *arg)
{
	BaseType_t preProcMsgRcvd = pdFALSE;
	int16_t QData[NR_OF_AXES];
	int simpleRes;
	int send;
	char c;
	
	while(1)
	{
		/*Receive frame for converting*/
		while(preProcMsgRcvd == pdFALSE){
			preProcMsgRcvd = xQueueReceive(simpleProcFramReadyMsgQ, (void*)QData, portMAX_DELAY);
		}
		/* reset flag */
		preProcMsgRcvd = pdFALSE;	
		
		/* process data */
		simpleRes = simpleProcessing(QData);
		
		/* evaluate result */
		if(simpleRes == RESXp)
		{
			send = NAV_R;	
			c = 'X';
			printf("%c", c);
		}
		else if(simpleRes == RESXm)
		{
			send = NAV_L;
			c = 'x';
			printf("%c", c);
		}
		else if(simpleRes == RESYp)
		{
			send = NAV_DWN;
			c = 'y';
			printf("%c", c);
		}
		else if(simpleRes == RESYm)
		{
			send = NAV_UP;
			c = 'Y';
			printf("%c", c);
		}
		else
		{
			send = 0;
		}
			
		//xQueueSend(communicationMsgQ, &send, 10);
	}
}

void printIdx(unsigned int* idx)
{
	int i = 0;
	
	for(i = 0; i < 20; i++)
	{
			printf("%2d\n", idx[i]);
	}
		
	myfree(idx);
}

