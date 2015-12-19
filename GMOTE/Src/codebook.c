#include "codebook.h"

double dataTree[CODE_BOOK_SIZE][6] = 
{
{401.562500000000,  -1324.97500000000, 20098.2625000000, -1899.38750000000, -2257.65000000000, -6525.17500000000},
{-1120.84615384615, -2426.20000000000, 19962.8615384615, -4609.33846153846, -1639.58461538462, -4298.09230769231},
{1300.20987654321,  -1261.72839506173, 20929.7777777778, 2698.58024691358,  -1543.14814814815, -4290.76543209877},
{-1632.30232558140, -5212.39534883721, 14727.3255813954, -3969.09302325581, 5888.65116279070,  5272.37209302326},
{30.1538461538462,  -1425.46923076923, 18339.4923076923, -1123.41538461538, -195.169230769231, -551.838461538462},
{-1568.50000000000, -4406.96000000000, 16545.9800000000, -8538.44000000000, 2174.46000000000,  443.480000000000},
{1959.26153846154,  -2546.83076923077, 18649.0615384615, 6814.04615384615,  -787.492307692308, 702.369230769231},
{1116.69767441860,  -3941.86046511628, 15048.1860465116, 4270.06976744186,  3750.13953488372,  5179.93023255814},
{-650.266055045872, -2070.00917431193, 20103.7522935780, 272.862385321101,  -1460.05504587156, -3258.59633027523},
{-1258.73333333333, -3233.43333333333, 18900.3333333333, -6951.30000000000, 433.350000000000,  -1769.33333333333},
{1498.91780821918,  -2027.83561643836, 20594.3972602740, 5677.79452054795,  -2446.13698630137, -2084.01369863014},
{-828.846153846154, -4935.69230769231, 14420.0192307692, -1823.84615384615, 4996.19230769231,  6929.90384615385},
{1507.46875000000,  -830.796875000000, 17127.0937500000, 316.750000000000,  1346.48437500000,  322.343750000000},
{-1701,             -4994.31034482759, 15345.2758620690, -6227.89655172414, 4026.91379310345,  2983.51724137931},
{1605.07017543860,  -3385.87719298246, 16709.2456140351, 6411.43859649123,  1518.73684210526,  3432.10526315789},
{730.860000000000,  -4290.88000000000, 13985.6800000000, 1120.56000000000,  4429.82000000000,  6906.50000000000}
};

void codeBookTest()
{
	void *kd;
	struct kdres *res;
	int i = 0;

	kd = kd_create(6);
	
	for(i = 0; i < CODE_BOOK_SIZE; i++){
		if(kd_insert(kd, dataTree[i], (void*)i) < 0){
			error("Error building tree", 3);
		}
	}
	
	for(i = 0; i < CODE_BOOK_SIZE; i++){
		res = kd_nearest(kd, dataTree[i]);
		if(!res){
			error("Error finding near", 3);
		}
		
		if((int)kd_res_item_data(res) != i){
			error("Error confirming", 3);
		}
	}
}
