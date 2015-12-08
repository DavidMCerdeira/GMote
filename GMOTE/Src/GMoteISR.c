#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "discoLeds.h"
#include "sensors.h"

/*TESTING PURPOSE*/
#include "GyroAq.h"


extern SemaphoreHandle_t accelDrdySemaph;
extern TaskHandle_t aqManagerHandle;

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	static int state = 0;
	static BaseType_t semophoreWoke;
	static BaseType_t notificationWoke;
	static int 	mpuFIFOCount;
	int retVal;
	
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

		xSemaphoreGiveFromISR(accelDrdySemaph, &semophoreWoke);
		portYIELD_FROM_ISR(semophoreWoke);
	}
	/*MPU ISR*/
		if(pin == GPIO_PIN_6){
			mpuFIFOCount++;
			if(MPU_Get_FIFOCount(&retVal)) ;
			if(retVal >= 24){
				mpuFIFOCount = 0;
				/*Function that reads sample*/
				 runGyroGest(NULL);
				/*Reset MPU*/
				//MPU_RESET();
		}	
	}	
}
