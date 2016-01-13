#ifndef _SENSOR_H
#define _SENSOR_H

#include "stm32f4xx_hal.h"
#include <stdio.h>

#define SAMPLE_SIZE   6     //in bytes
#define AQ_SIZE       300   //number of samples
#define FRAME_SIZE    20    //in samples
#define NR_OF_AXES 3				//number of Axes per sensor

#define ACCEL_X 0
#define ACCEL_Y 1
#define ACCEL_Z 2
#define GYRO_X  3
#define GYRO_Y  4
#define GYRO_Z  5
	
/* USER SIGNALS */
#define GStart 0x1
#define GStop  0x2
#define EqON   0x4
#define EqOFF  0x8

/* SENSOR SIGNALS */
#define STOP   0x10

typedef struct aquisitn
{
	uint32_t start;
	uint32_t end;
}aquisitn;

extern float data[300][6];

void printBuffer(aquisitn aq);

void initBuffer(aquisitn *aq);

int get_nextFrame(int16_t** buff, aquisitn *m_aq, int *firstTime);
#endif
