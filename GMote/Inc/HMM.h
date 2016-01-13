#include "codebook.h"

#include "cmsis_os.h"
#define ARM_MATH_CM4
#include "arm_math.h"
#include "HMM_param.h"
#include "string.h"
#include "HMM_param.h"
#include "math.h"
#include "priorities.h"



#define FRAME_SIZE 20

typedef struct forward forward;

struct forward
{
	unsigned int N;
	unsigned int T;
	float32_t C[FRAME_SIZE];
	float32_t prob;
	float32_t fw[FRAME_SIZE][NR_OF_STATES];
	float32_t last_fw[NR_OF_STATES];
	uint16_t firstTime;
	gest Cur_gest;
};

typedef struct HMM HMM;
struct HMM
{
	unsigned int N; //number of states
	unsigned int M; //codebook size
	float32_t (*At)[NR_OF_STATES][NR_OF_STATES]; //transition matrix
	float32_t (*Bt)[CDBK_SIZE][NR_OF_STATES];
	float32_t (*pi)[NR_OF_STATES];
	//!Probabilidade referencia do modelo;
	gest gest;
};

void HMM_Init(void);

void HMM_Init_models(void);

void HMM_ControlTsk(void*);

void HMM_ForwardTsk(void* rModel);

