#ifndef _DISCO_LEDS
#define _DISCO_LEDS

#include "stm32f4xx_hal.h"

#define GREEN(s) 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, (s) ? GPIO_PIN_SET : GPIO_PIN_RESET);
#define ORANGE(s) HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, (s) ? GPIO_PIN_SET : GPIO_PIN_RESET);
#define RED(s) 	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, (s) ? GPIO_PIN_SET : GPIO_PIN_RESET);
#define BLUE(s) 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, (s) ? GPIO_PIN_SET : GPIO_PIN_RESET);

#endif
