#include "error.h"

void error(char* msg, int severity)
{
	int state = 0;
	
	printf("Error(%d): %s\n", severity, msg);
	
	switch(severity)
	{
		case 1: goto ERROR1;
		case 2: goto ERROR2;
		case 3: goto ERROR3;
	}
	
	ERROR1:
		while(1)
		{
			state = !state;
			ORANGE(state);
			HAL_Delay(500);
		}
	ERROR2:
		while(1)
		{
			state = !state;
			RED(state);
			HAL_Delay(500);
		}
	
	ERROR3:
		while(1)
		{
			state = !state;
			RED(state);
			ORANGE(state);
			GREEN(state);
			BLUE(state);
			HAL_Delay(500);
		}
}
