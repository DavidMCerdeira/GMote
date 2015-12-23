#include "pre_processing.h"

extern QueueHandle_t framesRdy;

void preprocessing(void *arg)
{
	int *idx;
	uint16_t pos[2];
	/*Receive frame for converting*/
	//accelMsgQRcvd = xQueueReceive(accelFrameReadyMsgQ, (void*)&accelRes, portMAX_DELAY);
	
	//idx = codebook_vecToIdx(**data, pos[0], pos[1]);
	xQueueSend(framesRdy, &idx, 10);
}