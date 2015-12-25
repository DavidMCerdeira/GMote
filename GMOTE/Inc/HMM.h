#include "codebook.h"

#include "cmsis_os.h"
#include "arm_math.h"
#include "HMM_param.h"
#include "string.h"
#include "HMM_param.h"

#define FRAME_SIZE 20

typedef struct forward forward;

struct forward
{
	unsigned int N;
	unsigned int T;
	float32_t C;
	float32_t fw[FRAME_SIZE][NR_OF_STATES];
	uint16_t firstTime;
	gest Cur_gest;
};

typedef struct HMM HMM;
struct HMM
{
	unsigned int N; //number of states
	unsigned int M; //codebook size
	float32_t** A; //transition matrix
	float32_t** B;
	float32_t *pi;
	//!Probabilidade referencia do modelo;
	gest gest;
};

void HMM_Init(void);

void HMM_Init_models(void);

void HMM_ControlTsk(void*);

void HMM_ForwardTsk(void* rModel);

