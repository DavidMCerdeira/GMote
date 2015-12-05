#include "usDelay.h"

#define TIMOVRFLOW_FLAG 0x01

extern TIM_HandleTypeDef htim6;

void usDelay(uint16_t usSeconds)
{
	htim6.Init.Period = usSeconds;
	HAL_TIM_Base_Init(&htim6);
	
	TIM6->SR &= (~TIMOVRFLOW_FLAG);
	HAL_TIM_OC_Start(&htim6, 0);
	
	while( !(TIM6->SR & TIMOVRFLOW_FLAG));
	
	HAL_TIM_OC_Stop(&htim6, 0);
	TIM6->SR &= (~TIMOVRFLOW_FLAG);
	
}
