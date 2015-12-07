#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "discoLeds.h"
#include "sensors.h"

extern osSemaphoreId drdySemaph;
extern osThreadId aqManagerId;
extern osThreadId accelThreadId;

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	static int state = 0;

	if(pin == GPIO_PIN_1)
	{
		/* toggle aquisition */
		GREEN(state = !state);
		
		if(state){
			osSignalSet(aqManagerId, GStart);
		}
		else{
			osSignalSet(aqManagerId, GStop);		
		}
	}
	if(pin == GPIO_PIN_0){
		osSemaphoreRelease(drdySemaph);
	}
}
