#ifndef _ACCEL_AQ
#define _ACCEL_AQ
#include "Accelerometer.h"
#include "cmsis_os.h"
#include "sensor.h"

#define NORMAL_SPEED HZ_100
#define LOW_SPEED    HZ_3_125

void runAccelGest(void* argument);
void runAccelSimple(void* argument);
void initAccelAq(void);

#endif
