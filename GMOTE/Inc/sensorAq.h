#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "AccelerometerAq.h"
#include "GyroAq.h"
#include "sensor.h"
#include "nrf24l01.h"

void aqManager(void* argument);
