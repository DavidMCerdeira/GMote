#ifndef _SENSOR_H
#define _SENSOR_H

#include "stm32f4xx_hal.h"
#include <stdio.h>

#define SAMPLE_SIZE   6     //in bytes
#define AQ_SIZE       300   //number of samples
#define FRAME_SIZE    24    //in samples
#define FRAME_OVERLAP 6     //in samples 
#define NR_OF_AXES 3				//number of Axes per sensor
	
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
	int16_t samples[NR_OF_AXES][AQ_SIZE];
}aquisitn;

void printBuffer(aquisitn aq);

void initBuffer(aquisitn *aq);

int get_nextFrame(int16_t** buff, aquisitn *m_aq, int *firstTime);
#endif
