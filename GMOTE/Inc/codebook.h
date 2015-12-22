#include "kdtree.h"
#include "cmsis_os.h"
#include "HMM_param.h"
#include "error.h"

#define CODE_BOOK_SIZE 16


typedef struct kdTree codebook;

void codeBook_init(void);

//int codebook_idx(gest id, float *pos);
