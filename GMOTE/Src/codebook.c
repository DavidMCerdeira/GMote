#include "codebook.h"

struct kdtree* codebook;

const float codeBookData[CDBK_SIZE][NR_OF_DIM]={
{00220.241071, -1749.232143, 23648.910714, 07534.375000, -1633.071429, -1177.892857},
{01257.600000, -2852.617391, 17782.765217, 00129.643478, 01316.000000, 11391.530435},
{00332.583333, -1544.916667, 21228.291667, 02680.108333, -2623.716667, -10551.716667},
{00607.082126, -1849.212560, 23050.091787, -0392.246377, 00355.584541, -1416.850242},
{06514.096386, -0998.228916, 19697.542169, 06254.590361, -3079.783133, -6909.554217},
{-6359.428571, -4637.071429, 20480.238095, 03841.535714, 02546.428571, 04249.488095},
{04953.187970, -4054.781955, 20335.631579, -4664.142857, -0552.428571, -5835.398496},
{-0840.808081, -2872.015152, 17343.858586, -7429.974747, 01038.000000, -0893.222222},
{-0018.839599, -2027.523810, 20561.318296, 03019.493734, -1811.586466, -3373.679198},
{06406.193548, -1262.645161, 16459.596774, 02193.048387, -0173.709677, 09796.274194},
{-0732.584098, -1960.920489, 19657.116208, -1447.813456, -1898.305810, -7456.376147},
{02644.256818, -3427.084091, 16842.025000, -0686.495455, 00343.440909, 01164.327273},
{01449.961957, -2727.972826, 17209.206522, 06047.298913, 00311.500000, 02825.951087},
{-1392.452055, -4913.589041, 14651.226027, -2630.650685, 05419.472603, 05775.143836},
{-0106.779412, -2228.841912, 20563.183824, -5655.948529, -1077.882353, -3828.080882},
{-0941.165939, -4274.550218, 16653.087336, -0871.017467, 00487.480349, -0506.026201},
{01167.227513, -2001.555556, 18993.206349, 07497.687831, -1538.164021, -1342.603175},
{03271.437500, -0040.979167, 14925.125000, -4194.604167, -1907.270833, 09581.354167},
{02642.556291, -3552.178808, 17514.364238, 00322.192053, -2380.072848, -6890.231788},
{-0620.019868, -1647.646799, 18951.189845, -0269.929360, -0618.055188, -2119.077263},
{08542.723684, -1184.434211, 17281.368421, 05182.210526, -1171.381579, 01815.500000},
{-3306.375940, -4537.548872, 19753.022556, -1040.789474, 00728.924812, 04566.090226},
{05498.308017, -2130.413502, 18825.101266, 00373.430380, -0484.362869, -1840.392405},
{-1724.127119, -4957.440678, 15566.483051, -6441.457627, 04107.457627, 02344.177966},
{-5094.697674, -3776.651163, 17128.465116, 04487.011628, -1072.558140, -5337.406977},
{06020.073446, -1388.310734, 16576.740113, -0499.282486, -0382.683616, 04802.881356},
{-3088.279476, -3725.406114, 17894.938865, -1666.515284, -0610.052402, -5729.218341},
{01105.231855, -0720.747984, 17780.375000, 00092.114919, 00520.455645, 00525.235887},
{00809.246575, -1562.136986, 13357.178082, 03550.684932, -0226.082192, -0910.595890},
{00580.944056, -4278.937063, 14615.139860, 02439.419580, 03871.825175, 06112.188811},
{-0440.690722, -2910.654639, 15599.185567, -5534.211340, -0515.257732, -5234.721649},
{-0365.355401, -2998.142857, 14139.202091, -1971.372822, -0027.595819, -0902.320557}
};

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
	
	//printf("Free heap %d bytes\n", xPortGetFreeHeapSize());
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
