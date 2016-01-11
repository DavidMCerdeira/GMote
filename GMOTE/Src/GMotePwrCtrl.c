#include "GMotePwrCtrl.h"
#include "DiscoLeds.h"

#define EXPECTED_SLEEP_TIME 0xFFFFFFFF

SemaphoreHandle_t GMotePwrCtrl_Sem;

extern TIM_HandleTypeDef htim7;

void GMotePwrCtrl_StartTimeOutTimer(void);
void GMotePrwCtrl_StopTimeOutTimer(void);

void GMotePwrCtrl_Init()
{
	GMotePwrCtrl_Sem = xSemaphoreCreateBinary();
	GMotePwrCtrl_StartTimeOutTimer();
}

void GMotePwrCtrl_RefreshTimeoutTimer()
{
		htim7.Instance->CNT = 0;
}

void GMotePwrCtrl_StartTimeOutTimer()
{
		htim7.Instance->CNT = 0;
		HAL_TIM_Base_Start_IT(&htim7);
}

void GMotePrwCtrl_StopTimeOutTimer()
{
		HAL_TIM_Base_Stop_IT(&htim7);
}

void GMotePwrCtrl_Run(void *arg)
{
	BaseType_t rcvd; 
	GMotePwrCtrl_Init();
	
	while(1)
	{
		rcvd = pdFALSE;
		while(rcvd == pdFALSE){
			rcvd = xSemaphoreTake(GMotePwrCtrl_Sem, portMAX_DELAY);
		}
		
		GMotePrwCtrl_StopTimeOutTimer();
		BLUE(1);
		//vPortSuppressTicksAndSleep(EXPECTED_SLEEP_TIME);
		BLUE(0);
		GMotePwrCtrl_StartTimeOutTimer();
	}
}
	
