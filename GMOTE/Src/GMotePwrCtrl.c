#include "GMotePwrCtrl.h"

SemaphoreHandle_t GMotePwrCtrl_Sem;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim7;

void GMotePwrCtrl_Init()
{
	GMotePwrCtrl_Sem = xSemaphoreCreateBinary();
	GMotePwrCtrl_RefreshTimeoutTimer();
}

void GMotePwrCtrl_RefreshTimeoutTimer()
{
	HAL_TIM_Base_Start_IT(&htim7);
}

void GMotePwrCtrl_StartSleepingTimer()
{
	HAL_TIM_Base_Start_IT(&htim2);
}

void GMotePwrCtrl_StopSleepingTimer()
{
	HAL_TIM_Base_Stop_IT(&htim2);
}

void GMotePwrCtrl_Run(void *arg)
{
	BaseType_t rcvd; 
	uint32_t start, end;
	HAL_TIM_StateTypeDef timState;
	GMotePwrCtrl_Init();
	
	while(1)
	{
		rcvd = pdFALSE;
		while(rcvd == pdFALSE){
			rcvd = xSemaphoreTake(GMotePwrCtrl_Sem, portMAX_DELAY);
		}
		
		/*start sysTick substitute*/
		GMotePwrCtrl_StartSleepingTimer();
		
		/*disable SysTick*/
		
		/*get current time*/
		start = htim2.Instance->CNT;
		
		/*sleep*/
		HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
		
		/*get current time*/
		end = htim2.Instance->CNT;
		
		/* set systick offset */
		
		//(end-start);
		/*enable SysTick again*/
	}
}
	
