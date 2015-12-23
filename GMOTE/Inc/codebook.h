#include "kdtree.h"
#include "cmsis_os.h"
#include "HMM_param.h"
#include "sensor.h"
#include "error.h"

#define CODE_BOOK_SIZE 16

typedef struct kdtree codebook;

void codeBook_init(codebook* codebook, float **data);

int codebook_idx(codebook *codebook, float *pos);

int* codebook_vecToIdx(codebook *codebook, int **vec, unsigned int start, unsigned int end);