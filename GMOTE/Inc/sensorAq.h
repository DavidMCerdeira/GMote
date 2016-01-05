#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "AccelerometerAq.h"
#include "GyroAq.h"
#include "sensor.h"
#include "processing.h"
#include "priorities.h"

void aqManager(void* argument);
