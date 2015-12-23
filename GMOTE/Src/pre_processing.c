#include "pre_processing.h"

QueueHandle_t framesRdy;

void preprocessing(void*)
{
	int *idx;
	
	//idx = codebook_idx(
	xQueueSend(framesRdy, &idx, 10);			
	
}