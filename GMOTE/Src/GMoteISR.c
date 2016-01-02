#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "discoLeds.h"
#include "sensor.h"
#include "mpu6050_gyro.h"
#include "keypad.h"
#include "priorities.h"

extern SemaphoreHandle_t accelDrdySemaph;
extern SemaphoreHandle_t gyroDrdySemaph;
extern QueueHandle_t keypadMsgQ;

TaskHandle_t dummy;

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	static BaseType_t woke;

	if(pin == GBUTTON_PIN)
	{
		woke = pdFALSE;
		xQueueSendFromISR(keypadMsgQ, &GBUTTON, &woke);
		portYIELD_FROM_ISR(woke);
	}
	if(pin == GPIO_PIN_0){
		/* increment semaphore */
		woke = pdFALSE;
		xSemaphoreGiveFromISR(accelDrdySemaph, &woke);
		portYIELD_FROM_ISR(woke);
	}
	/*MPU ISR*/
	if(pin == GPIO_PIN_6){			
		woke = pdFALSE;
		xSemaphoreGiveFromISR(gyroDrdySemaph, &woke);
		portYIELD_FROM_ISR(woke);
	}	
}	


