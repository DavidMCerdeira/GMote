#include "sensor.h"

void printBuffer(aquisitn aq)
{
	int j = 0;

	for(j = 0; j < AQ_SIZE; j++){
		printf("%+06hd\t%+06hd\t%+06hd\n", aq.samples[0][j], 
																			 aq.samples[1][j], 
																			 aq.samples[2][j]);
	}
}

void initBuffer(aquisitn *aq)
{	
	aq->end = aq->start = 0;

}
