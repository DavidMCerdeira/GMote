#include "sensor.h"

float data[300][6];

void initBuffer(aquisitn *aq)
{
	aq->end = aq->start = 0;
}
