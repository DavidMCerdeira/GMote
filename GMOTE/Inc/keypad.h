#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "comunication.h"
#include "sensor.h"
#include "discoLeds.h"

#define DEBOUNCE_TIME 10
#define N_BUTTONS 8
#define DEBOUNCE_MAXIMUM 6

#define GBUTTON_PORT GPIOA
#define GBUTTON_PIN GPIO_PIN_1
extern const int GBUTTON;



void keypad_run(void *arg);

#endif
