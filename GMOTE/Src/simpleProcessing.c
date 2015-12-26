#include "simpleProcessing.h"

#define abs(n) (n > 0) ? (n) : (-n)

int simpleProcessing(int16_t input[NR_OF_AXES])
{
	volatile int a = abs(input[ACCEL_X]);
	volatile int b = abs(input[ACCEL_Y]);
	
	if(a > b)
	{
		if((input[ACCEL_X] > 0) && (input[ACCEL_X] > TRESHOLDXp))
		{
			return RESXp;
		}
		else if((input[ACCEL_X] < 0) && (input[ACCEL_X] < TRESHOLDXm))
		{
			return RESXm;
		}
	}
	else if(a < b)
	{
		if((input[ACCEL_Y] > 0) && (input[ACCEL_Y] > TRESHOLDYp))
		{
			return RESYp;
		}
		else if((input[ACCEL_Y] < 0) && (input[ACCEL_Y] < TRESHOLDYm))
		{
			return RESYm;
		}
	}
	
	return RESND;
}
