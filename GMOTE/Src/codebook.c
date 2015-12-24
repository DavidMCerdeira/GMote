#include "codebook.h"

struct kdtree* codebook;

void codeBook_init(void)
{
	struct kdres *res;
	volatile int i = 0;
	volatile int k = 0;

	codebook = kd_create(NR_OF_DIM);
	
	for(i = 0; i < CODE_BOOK_SIZE; i++)
	{
		if(kd_insertf(codebook, codeBookData[i], (void*)i) < 0){
			error("Error building tree", 3);
		}
	}
	
	for(i = 0; i < CODE_BOOK_SIZE; i++){
		res = kd_nearestf(codebook, codeBookData[i]);
		if(!res){
			error("Error finding near", 3);
		}
		
		if((int)kd_res_item_data(res) != i){
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

unsigned int* codebook_vecToIdx(int **vec, unsigned int start, unsigned int end)
{
	unsigned int *idx = NULL;
	unsigned int size = (end - start);
	int i = 0;
	
	if((vec != NULL) && (codebook != NULL))
	{
		idx = (unsigned int*)myalloc(sizeof(int)*(size));
		
		for(i = 0; i < size; i++){
			idx[i] = codebook_idx((float*)vec[start + i]);
		}
	}
	
	return idx;
}	
