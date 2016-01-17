#ifndef _ERROR_H
#define _ERROR_H

#include "discoLeds.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "freeRTOS.h"
#include "portmacro.h"

void error(char* msg, int severity);

#endif
