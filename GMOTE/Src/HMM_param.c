#include "HMM_param.h"


const float AT[NUM_GEST][NR_OF_STATES][NR_OF_STATES]={
{{0.943515, 0.000000, 0.000000, 0.010007, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.910077, 0.000000, 0.000000, 0.082115, 0.000000, 0.000000, 0.000000},
{0.000000, 0.008992, 0.929188, 0.000000, 0.000000, 0.000000, 0.034118, 0.000000},
{0.052219, 0.000000, 0.000000, 0.968625, 0.000000, 0.018298, 0.000000, 0.011901},
{0.000000, 0.000000, 0.070812, 0.000000, 0.917885, 0.000000, 0.000000, 0.000000},
{0.004266, 0.000000, 0.000000, 0.021369, 0.000000, 0.900355, 0.000000, 0.004053},
{0.000000, 0.080931, 0.000000, 0.000000, 0.000000, 0.000000, 0.939347, 0.035884},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.081347, 0.026536, 0.948163}},

{{0.859100, 0.000000, 0.000000, 0.059264, 0.000000, 0.012986, 0.000000, 0.000000},
{0.026781, 0.904110, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.053571},
{0.000000, 0.000000, 0.878607, 0.000000, 0.005895, 0.051890, 0.056401, 0.000000},
{0.073946, 0.000000, 0.000000, 0.940736, 0.005918, 0.000000, 0.000000, 0.000000},
{0.006696, 0.000000, 0.065343, 0.000000, 0.970413, 0.064981, 0.000000, 0.000000},
{0.000000, 0.000000, 0.056051, 0.000000, 0.011857, 0.857158, 0.007012, 0.035714},
{0.000000, 0.082192, 0.000000, 0.000000, 0.000000, 0.000000, 0.929541, 0.071429},
{0.033476, 0.013699, 0.000000, 0.000000, 0.005917, 0.012986, 0.007046, 0.839286}},

{{0.952655, 0.015210, 0.013599, 0.000000, 0.014710, 0.009346, 0.000000, 0.000000},
{0.037934, 0.904082, 0.006573, 0.000000, 0.051467, 0.000000, 0.000000, 0.000000},
{0.006274, 0.035499, 0.920644, 0.000000, 0.000000, 0.074766, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.903614, 0.000000, 0.000000, 0.000000, 0.055944},
{0.000000, 0.045209, 0.000000, 0.000000, 0.867647, 0.000000, 0.117647, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.066176, 0.915888, 0.000000, 0.000000},
{0.003136, 0.000000, 0.000000, 0.096386, 0.000000, 0.000000, 0.882353, 0.006993},
{0.000000, 0.000000, 0.059184, 0.000000, 0.000000, 0.000000, 0.000000, 0.937063}},

{{0.926395, 0.000000, 0.006173, 0.000000, 0.005872, 0.000000, 0.011905, 0.000000},
{0.000000, 0.684211, 0.000000, 0.037500, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.315789, 0.993827, 0.018750, 0.000000, 0.000000, 0.000000, 0.000000},
{0.006684, 0.000000, 0.000000, 0.875000, 0.011602, 0.105882, 0.095238, 0.000000},
{0.066921, 0.000000, 0.000000, 0.018750, 0.924516, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.050000, 0.005801, 0.894118, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.892857, 0.112500},
{0.000000, 0.000000, 0.000000, 0.000000, 0.052208, 0.000000, 0.000000, 0.887500}},

{{0.845528, 0.000000, 0.000000, 0.105263, 0.000000, 0.000000, 0.088993, 0.042857},
{0.000000, 0.926230, 0.000000, 0.000000, 0.105263, 0.000000, 0.000000, 0.007143},
{0.000000, 0.073770, 0.933824, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.842105, 0.000000, 0.000000, 0.044497, 0.007143},
{0.040650, 0.000000, 0.000000, 0.052632, 0.894737, 0.000000, 0.000000, 0.014286},
{0.000000, 0.000000, 0.066176, 0.000000, 0.000000, 0.866483, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.133517, 0.866510, 0.000000},
{0.113821, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.928571}},

{{0.897807, 0.000000, 0.000000, 0.038948, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.829340, 0.072165, 0.000001, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.927835, 0.000000, 0.000000, 0.024815, 0.000000, 0.146341},
{0.000000, 0.170660, 0.000000, 0.766312, 0.000000, 0.000000, 0.000000, 0.024390},
{0.000000, 0.000000, 0.000000, 0.000000, 0.891574, 0.040810, 0.000000, 0.000000},
{0.068129, 0.000000, 0.000000, 0.000000, 0.041110, 0.910082, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.194740, 0.000000, 0.000000, 1.000000, 0.000000},
{0.034064, 0.000000, 0.000000, 0.000000, 0.067316, 0.024293, 0.000000, 0.829268}},

{{0.900888, 0.000000, 0.000000, 0.000000, 0.023808, 0.000000, 0.107143, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000007, 0.000000, 0.090631, 0.000000, 0.000000},
{0.000000, 0.432011, 0.828571, 0.019178, 0.000000, 0.000000, 0.035714, 0.000000},
{0.021936, 0.567989, 0.142857, 0.893301, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.809535, 0.000000, 0.000000, 0.190465},
{0.077176, 0.000000, 0.000000, 0.000000, 0.000000, 0.909369, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.166656, 0.000000, 0.857143, 0.000000},
{0.000000, 0.000000, 0.028571, 0.087513, 0.000000, 0.000000, 0.000000, 0.809535}}
};

const float BT[NUM_GEST][CDBK_SIZE][NR_OF_STATES]={
{{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.027109, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.011727, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.962178, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.474918, 0.000000, 0.022697, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.004780, 0.000000, 0.000000, 0.000000, 0.401726},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.010411, 0.000000, 0.598274},
{0.000000, 0.000000, 0.991362, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.010845, 0.000000, 0.000000, 0.000000, 0.000000, 0.469514, 0.000000},
{0.013324, 0.000000, 0.008638, 0.000000, 0.031040, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.912674, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.027109, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.499572, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.004691, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.968960, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.986676, 0.000000, 0.000000, 0.004313, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.530486, 0.000000},
{0.000000, 0.026977, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000}},

{{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.168812, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.989968, 0.000000, 0.000000, 0.000115, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.767857},
{0.000000, 0.000000, 0.000000, 0.000000, 0.977400, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.028184, 0.000000},
{0.000000, 0.000000, 0.000000, 0.362427, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.007124, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.010032, 0.000000, 0.000000, 0.000000, 0.971816, 0.000000},
{0.029241, 0.000000, 0.000000, 0.457805, 0.000000, 0.000000, 0.000000, 0.000000},
{0.092607, 0.000000, 0.000000, 0.000000, 0.022600, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.831073, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.021319, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.010660, 0.000000, 0.000000, 0.000000, 0.232143},
{0.031415, 0.000000, 0.000000, 0.147050, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.839613, 0.000000, 0.000000, 0.000740, 0.000000, 0.000000, 0.000000, 0.000000}},

{{0.000000, 0.479823, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.278972, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.137883, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.019218, 0.000034, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.029989, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.002992, 0.490154, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.054512, 0.000000, 0.000000, 0.000000, 0.000000, 0.018692, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.019239, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.337435, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.003207, 0.000000, 0.000000, 0.000000, 0.474453, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000},
{0.012610, 0.000000, 0.013162, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.525547, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000},
{0.471367, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.981308, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.649403, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000}},

{{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.525000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000},
{0.000000, 0.000000, 0.494118, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.063553, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.046407, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.365459, 0.000000, 0.000000, 0.000000},
{0.451933, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.021184, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.069611, 0.000000, 0.000000, 0.000000},
{0.303643, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.406065, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.475000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.070615, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.505882, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.018457, 0.000000, 0.000000, 0.000000, 0.077652, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.034806, 0.000000, 0.000000, 0.000000},
{0.056492, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.014123, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000}},

{{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.055556},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.904412, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.008621, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.095588, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.171053, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.013158, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.208333},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.416667},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.319444},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.439655, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.057377, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.551724, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.026316, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.942623, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.789474, 0.000000, 0.000000, 0.000000}},

{{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.051020, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.013345, 0.000000, 0.000000, 0.000000, 0.147110, 0.973604, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.040816, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.121951},
{0.274765, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.878049},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.142857, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.499572, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.212318, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.755102, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.852890, 0.026396, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.010204, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000}},

{{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.384489, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.012933, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.571838, 0.000000, 0.990283, 0.000000, 0.027806, 0.000000, 0.000000},
{0.000000, 0.000000, 0.342857, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.064665, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.840643, 0.000000, 0.000000},
{0.000000, 0.000000, 0.057143, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.038799, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.557255, 0.000000, 0.000000, 0.000000, 0.000000, 0.015154, 0.000000, 0.000000},
{0.058256, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.485714, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.142688, 0.114286, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.142786, 0.000000, 0.009717, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.142688, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000}}
};

const float Pi[NUM_GEST][NR_OF_STATES]={
{0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000},

{0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000},

{0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000},

{0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000},

{0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000},

{0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000},

{0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000, 0.125000}
};

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
