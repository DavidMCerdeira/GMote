#include "error.h"

void error(char* msg, int code)
{
	/* disable all interrupts to stop the system */
	portDISABLE_INTERRUPTS();
	/* turn everything off? */
	
	switch(code)
	{
		case 1: goto ERROR1;
		case 2: goto ERROR2;
		case 3: goto ERROR3;
		case 4: goto ERROR4;
		case 5: goto ERROR5;
	}
	
	ERROR1:
		ORANGE(1);
		while(1);
		
	ERROR2:
		RED(1);		
		while(1);
	
	ERROR3:
		GREEN(1);
		while(1);
		
	ERROR4:
		BLUE(1);
		while(1);
		
	ERROR5:
		BLUE(1);
		GREEN(1);
		RED(1);
		ORANGE(1);
}
