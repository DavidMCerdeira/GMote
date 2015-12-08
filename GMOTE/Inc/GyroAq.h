#ifndef _GYROAQ_H
#define _GYROAQ_H

#include "mpu6050_gyro.h"
#include "cmsis_os.h"

//typedef
//struct aquisitn
//{
//	uint32_t start;
//	uint32_t end;
//	int16_t samples[3][200];
//}aquisitn;

void runGyroGest(void const * argument);
void initGyroAq(void);

#endif
