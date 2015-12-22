#include "codebook.h"

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
	
	//gest gest;
	codebook *codebook;
};

void HMM_init(HMM *gest)
{
	
}
