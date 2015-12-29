#include "comunication.h"

QueueHandle_t communicationMsgQ;

int communication_validate(int8_t byte);
#define comunication_hw_init() nrf24l01_Init()

void communication_init(void)
{
	/* init comunicationQ`*/
	communicationMsgQ  = xQueueCreate(30, sizeof(int8_t));
	/*init comunication hardware*/
	comunication_hw_init();
}

void communication_run(void *arg)
{
	BaseType_t msgQrcvd = pdFALSE;
	int8_t byte = 0;
	
	communication_init();
	
	while(1)
	{
		while(msgQrcvd == pdFALSE)
		{
			msgQrcvd = xQueueReceive(communicationMsgQ, &byte, portMAX_DELAY);
		}
		msgQrcvd = pdFALSE;
		
		if(communication_validate(byte)){		
			communication_send("%c", byte);	
		}
	}
}

int communication_validate(int8_t byte)
{
	
	return 1;
}
