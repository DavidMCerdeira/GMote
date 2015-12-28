#ifndef _GYROAQ_H
#define _GYROAQ_H

#include "mpu6050_gyro.h"
#include "cmsis_os.h"
#include "sensor.h"

void runGyroGest(void * argument);
void initGyroAq(void);

void mpuTest(void);

#endif
