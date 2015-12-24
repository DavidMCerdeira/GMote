#ifndef _ACCEL_AQ
#define _ACCEL_AQ
#include "Accelerometer.h"
#include "cmsis_os.h"
#include "sensor.h"

void runAccelGest(void* argument);
void runAccelSimple(void* argument);
void initAccelAq(void);

#endif
