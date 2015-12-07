#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "discoLeds.h"
#include "sensors.h"

extern SemaphoreHandle_t drdySemaph;
extern TaskHandle_t aqManagerHandle;

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	static int state = 0;
	static BaseType_t semophoreWoke;
	static BaseType_t notificationWoke;
	
	if(pin == GPIO_PIN_1)
	{
		/* toggle aquisition */
		GREEN(state = !state);
		
		if(state){
			/* signal aqManager to start aquiring gesture */ //osSignalSet(aqManagerId, GStart);
			xTaskNotifyFromISR(aqManagerHandle, GStart, eSetBits, &notificationWoke);
			portYIELD_FROM_ISR(notificationWoke);			
		}
		else{
			/* signal aqManager to stop aquiring gesture */ //osSignalSet(aqManagerId, GStop);		
			xTaskNotifyFromISR(aqManagerHandle, GStop, eSetBits, &notificationWoke);
			portYIELD_FROM_ISR(notificationWoke);	
		}
	}
	if(pin == GPIO_PIN_0){
		/* increment semaphore */ //osSemaphoreRelease(drdySemaph);
		semophoreWoke = pdFALSE;

		xSemaphoreGiveFromISR(drdySemaph, &semophoreWoke);
		portYIELD_FROM_ISR(semophoreWoke);
	}
}
