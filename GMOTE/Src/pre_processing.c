#include "pre_processing.h"

extern QueueHandle_t framesRdy;

QueueHandle_t preProcFramReadyMsgQ;
QueueHandle_t simpleProcFramReadyMsgQ;

TaskHandle_t simpleProcTaskHandle;

void printIdx(unsigned int* idx);
void simpleProc(void *arg);

void processing_init()
{
	/* initialize pre proc msgQ */
	preProcFramReadyMsgQ  = xQueueCreate(30, sizeof(uint32_t)); 
	/* initialize simple proc msgQ */
	simpleProcFramReadyMsgQ = xQueueCreate(30, sizeof(int32_t)*3); 
	
	/* create thread to deal with equilibrium mode */
	xTaskCreate(simpleProc, "SimpleProcessing", 128, NULL, 3, &simpleProcTaskHandle);
}

void preprocessing(void *arg)
{
	unsigned int *idx;
	BaseType_t preProcMsgRcvd = pdFALSE;
	int aqSensorRes = 0;
	static int begin = 0;
	
	/* init */
	processing_init();
	/* init codebook */
	codeBook_init();
	
	while(1){
		/*Receive frame for converting*/
		while(preProcMsgRcvd == pdFALSE){
			preProcMsgRcvd = xQueueReceive(preProcFramReadyMsgQ, (void*)&aqSensorRes, portMAX_DELAY);
		}
		/* reset flag */
		preProcMsgRcvd = pdFALSE;
		
		/*convert data matrix*/
		idx = codebook_vecToIdx((float**)&data[begin],  begin + aqSensorRes, 6);
		/*save last value*/
		begin += aqSensorRes;
		/*send decoded data*/
		printIdx(idx);
		//xQueueSend(framesRdy, &idx, 10);
	}
}

void simpleProc(void *arg)
{
	BaseType_t preProcMsgRcvd = pdFALSE;
	int16_t Qdata[NR_OF_AXES];
	
	while(1)
	{
		/*Receive frame for converting*/
		while(preProcMsgRcvd == pdFALSE){
			preProcMsgRcvd = xQueueReceive(simpleProcFramReadyMsgQ, (void*)Qdata, portMAX_DELAY);
		}
		/* reset flag */
		preProcMsgRcvd = pdFALSE;	
	}
}

void printIdx(unsigned int* idx)
{
	int i = 0;
	
	printf("Idx:\n");
	for(i = 0; i < 20; i++)
	{
			printf("%d ", idx[i]);
	}
	printf("\nend\n");
	
	myfree(idx);
}

