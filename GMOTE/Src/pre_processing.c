#include "pre_processing.h"

extern QueueHandle_t framesRdy;
extern QueueHandle_t preProcFramReadyMsgQ;

void printIdx(unsigned int* idx);

void preprocessing(void *arg)
{
	unsigned int *idx;
	BaseType_t preProcMsgRcvd = pdFALSE;
	int aqSensorRes = 0;
	static int begin = 0;
	
	while(1){
		/*Receive frame for converting*/
		while(preProcMsgRcvd == pdFALSE){
			preProcMsgRcvd = xQueueReceive(preProcFramReadyMsgQ, (void*)&aqSensorRes, portMAX_DELAY);
		}
		preProcMsgRcvd = pdFALSE;
		
		/*convert data matrix*/
		idx = codebook_vecToIdx((codebook*)NULL, (int**)data, begin, begin + aqSensorRes);
		/*save last value*/
		begin += aqSensorRes;
		/*send decoded data*/
		printIdx(idx);
		//xQueueSend(framesRdy, &idx, 10);
	}
}

void printIdx(unsigned int* idx)
{
	int i = 0;
	
	printf("Idx:\n");
	for(i = 0; i < 20; i++)
	{
			printf("%d\n", idx[i]);
	}
	printf("end\n");
	
	myfree(idx);
}

