#ifndef _SIMPLE_PROC_
#define _SIMPLE_PROC_

#include "stdint.h"
#include "comunication.h"

/* outputs */
#define RESND  0 /* not define */
#define RESXp  1 /* x+ */
#define RESXm  2 /* x- */
#define RESYp  3 /* y+ */
#define RESYm  4 /* y- */

int simpleProcessing(int16_t input[3]);

#endif
