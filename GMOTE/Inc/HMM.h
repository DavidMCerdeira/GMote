#include "codebook.h"
#include "cmsis_os.h"
#include "HMM_param.h"
#include "string.h"

#define MAX_FRAMES_NR 10

typedef struct forward forward;

struct forward
{
	unsigned int N;
	unsigned int T;
	float C;
	float **fw;
};

typedef struct HMM HMM;
struct HMM
{
	unsigned int N; //number of states
	unsigned int M; //codebook size
	float **A;
	float **B;
	float *pi;
	//Probabilidade referencia do modelo;
	gest gest;
	codebook *codebook;
};

void HMM_Init();

void HMM_Init_models();

void HMM_ControlTsk();

void HMM_ForwardTsk(void* rModel);
