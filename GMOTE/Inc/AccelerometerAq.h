#ifndef _ACCEL_AQ
#define _ACCEL_AQ
#include "Accelerometer.h"
#include "cmsis_os.h"

#define SAMPLE_SIZE   6     //in bytes
#define AQ_SIZE       300   //number of samples
#define FRAME_SIZE    24    //in samples
#define FRAME_OVERLAP 6     //in samples

typedef
struct aquisitn
{
	uint32_t start;
	uint32_t end;
	int16_t samples[3][AQ_SIZE];
}aquisitn;

void runAccelGest(void* argument);
void initAccelAq(void);

#endif
