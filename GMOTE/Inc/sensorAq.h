#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "AccelerometerAq.h"
#include "GyroAq.h"
#include "sensor.h"
#include "pre_processing.h"

void aqManager(void* argument);
