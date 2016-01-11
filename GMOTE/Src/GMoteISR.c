#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "discoLeds.h"
#include "sensor.h"
#include "mpu6050_gyro.h"
#include "keypad.h"
#include "priorities.h"
#include "GMotePwrCtrl.h"

extern SemaphoreHandle_t accelDrdySemaph;
extern SemaphoreHandle_t gyroDrdySemaph;
extern QueueHandle_t keypadMsgQ;
extern SemaphoreHandle_t GMotePwrCtrl_Sem;

TaskHandle_t dummy;

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	BLUE(0);
	static BaseType_t woke;
	ORANGE(1);
	if((pin >= GMOTE_BUTTON_0_PIN) && (pin <= GMOTE_BUTTON_13_PIN))
	{
		woke = pdFALSE;
		xQueueSendFromISR(keypadMsgQ, &pin, &woke);
		portYIELD_FROM_ISR(woke);
		GMotePwrCtrl_RefreshTimeoutTimer();
	}
	if(pin == GPIO_PIN_0){
		/* increment semaphore */
		woke = pdFALSE;
		xSemaphoreGiveFromISR(accelDrdySemaph, &woke);
		portYIELD_FROM_ISR(woke);
		GMotePwrCtrl_RefreshTimeoutTimer();
	}
	/*MPU ISR*/
	if(pin == GPIO_PIN_1){			
		woke = pdFALSE;
		xSemaphoreGiveFromISR(gyroDrdySemaph, &woke);
		portYIELD_FROM_ISR(woke);
		GMotePwrCtrl_RefreshTimeoutTimer();
	}	
ORANGE(0);
}	




