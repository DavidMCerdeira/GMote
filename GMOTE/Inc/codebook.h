#ifndef _CODEBOOK_H
#define _CODEBOOK_H

#include "kdtree.h"
#include "cmsis_os.h"
#include "HMM_param.h"
#include "sensor.h"
#include "error.h"


#define myalloc(__SIZE__) pvPortMalloc(__SIZE__)
#define myfree(ptr)       vPortFree(ptr)

void codeBook_init(void);

int codebook_idx(float *pos);

unsigned int* codebook_vecToIdx(float **vec, unsigned int rows, unsigned int columns);

#endif
