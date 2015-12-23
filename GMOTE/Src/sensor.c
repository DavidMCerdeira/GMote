#include "sensor.h"

int16_t data[6][300];

void initBuffer(aquisitn *aq)
{
	aq->end = aq->start = 0;
}
