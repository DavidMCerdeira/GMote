#include "codebook.h"

QueueHandle_t framesRdy;

void codeBook_init()
{
	struct kdres *res;
	volatile int i = 0;
	volatile int k = 0;

	kdTree = kd_create(6);
	
	printf("Heap size left %d\n",xPortGetFreeHeapSize());
	
	for(k = 0; k < N_GEST; k++)
	{
		for(i = 0; i < CODE_BOOK_SIZE; i++)
		{
			if(kd_insertf(kdTree, dataTree[k][i], (void*)i) < 0){
				error("Error building tree", 3);
			}
		}
		
		for(i = 0; i < CODE_BOOK_SIZE; i++){
			res = kd_nearestf(kdTree, dataTree[k][i]);
			if(!res){
				error("Error finding near", 3);
			}
			
			if((int)kd_res_item_data(res) != i){
				error("Error confirming", 3);
			}
			
			kd_res_free(res);
		}
	}
	
	printf("Everything is A-Ok!\n");
	printf("Heap size left %d\n",xPortGetFreeHeapSize());
}


int codebook_idx(gest id, float *pos)
{
	struct kdres *res;
	int idx = 0;
	
	/*get nearest point*/
	res = kd_nearestf(kdTree, pos);
	if(!res){
		error("Error finding near", 3);
	}
	
	/*get nearest point's index*/
	idx = (int)kd_res_item_data(res);
	
	/*clean result*/
	kd_res_free(res);
	
	return idx;
}
