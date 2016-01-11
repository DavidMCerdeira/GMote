#include "codebook.h"
#include "codebook_param.h"

struct kdtree* codebook;

void codeBook_init(void)
{
	struct kdres *res;
	volatile int i = 0;
	volatile int k = 0;
	int data;

	codebook = kd_create(NR_OF_DIM);
	
	for(i = 0; i < CDBK_SIZE; i++)
	{
		data = i;
		if(kd_insertf(codebook, codeBookData[i], (void*)data) < 0){
			error("Error building tree", 3);
		}
	}
	
	for(i = 0; i < CDBK_SIZE; i++){
		res = kd_nearestf(codebook, codeBookData[i]);
		if(!res){
			error("Error finding near", 3);
		}
		
		if((int)kd_res_item_data(res) != (i)){
			error("Error confirming", 3);
		}
		
		kd_res_free(res);
	}
}

int codebook_idx(float *pos)
{
	struct kdres *res;
	int idx = 0;
	
	/*get nearest point*/
	res = kd_nearestf(codebook, pos);
	if(!res){
		error("Error finding near", 3);
	}
	
	/*get nearest point's index*/
	idx = (int)kd_res_item_data(res);
	
	/*clean result*/
	kd_res_free(res);
	
	return idx;
}

unsigned int* codebook_vecToIdx(float **vec, unsigned int rows, unsigned int cols)
{
	unsigned int *idx = NULL;
	int i = 0;
	
	/* check that pointers are valid */
	if((vec != NULL) && (codebook != NULL))
	{
		/* alloc buffer for results */
		idx = (unsigned int*)myalloc(sizeof(int)*(rows));
		/* error? */
		if(idx == NULL){
			error("Error allocating memory in idx", 3);
		}
		
		/* go trough all columns and retreive indexes*/
		for(i = 0; i < rows; i++){
			idx[i] = codebook_idx((float*)(vec += cols));
		}
	}
	
	return idx;
}	
