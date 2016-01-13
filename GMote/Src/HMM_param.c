#include "HMM_param.h"


const float AT[NUM_GEST][NR_OF_STATES][NR_OF_STATES]={
{{0.928433, 0.025345, 0.000000, 0.013396},
{0.000000, 0.914928, 0.086316, 0.000000},
{0.000000, 0.032965, 0.910430, 0.034170},
{0.071567, 0.026762, 0.003253, 0.952434}},

{{0.820905, 0.001805, 0.027091, 0.034153},
{0.006389, 0.992572, 0.019790, 0.005829},
{0.083105, 0.005623, 0.949624, 0.116273},
{0.089601, 0.000000, 0.003495, 0.843745}},

{{0.914914, 0.016665, 0.117388, 0.007042},
{0.020072, 0.943997, 0.013353, 0.115185},
{0.034286, 0.034531, 0.866699, 0.001895},
{0.030728, 0.004807, 0.002560, 0.875878}},

{{0.887708, 0.011865, 0.046489, 0.033572},
{0.014732, 0.966559, 0.061899, 0.024638},
{0.089524, 0.004014, 0.891612, 0.001471},
{0.008035, 0.017562, 0.000000, 0.940319}},

{{0.765876, 0.047302, 0.007996, 0.045446},
{0.040191, 0.877963, 0.008980, 0.037665},
{0.086876, 0.046798, 0.951810, 0.025278},
{0.107057, 0.027938, 0.031214, 0.891611}},

{{0.887167, 0.034044, 0.025534, 0.008087},
{0.005912, 0.945880, 0.006679, 0.091116},
{0.106921, 0.001498, 0.903516, 0.009052},
{0.000000, 0.018578, 0.064272, 0.891746}},

{{0.737799, 0.002732, 0.000000, 0.022375},
{0.054586, 0.911880, 0.078088, 0.122071},
{0.000000, 0.070562, 0.921912, 0.003505},
{0.207615, 0.014826, 0.000000, 0.852050}}
};

const float BT[NUM_GEST][CDBK_SIZE][NR_OF_STATES]={
{{0.001777, 0.000000, 0.000000, 0.512425},
{0.000890, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000890, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.001081, 0.122980},
{0.000000, 0.000000, 0.000000, 0.031386},
{0.000000, 0.000000, 0.000000, 0.016654},
{0.000000, 0.000000, 0.000000, 0.024981},
{0.000000, 0.000000, 0.000000, 0.290159},
{0.000890, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.002670, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.011869, 0.000000},
{0.586518, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000190, 0.000886, 0.000000},
{0.005340, 0.000000, 0.000000, 0.000000},
{0.005340, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.004316, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.044501, 0.000000, 0.000000, 0.000000},
{0.155565, 0.000000, 0.000000, 0.001415},
{0.000890, 0.000000, 0.525451, 0.000000},
{0.000000, 0.629529, 0.000000, 0.000000},
{0.000000, 0.000000, 0.456398, 0.000000},
{0.015130, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.057667, 0.010853, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.121932, 0.000000, 0.000000, 0.000000},
{0.000000, 0.282863, 0.000000, 0.000000},
{0.000000, 0.076564, 0.000000, 0.000000}},

{{0.000000, 0.104387, 0.616821, 0.000000},
{0.000000, 0.001703, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.002913},
{0.000000, 0.000000, 0.374192, 0.000000},
{0.000000, 0.040864, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.002913},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.002406, 0.000000, 0.000000, 0.127608},
{0.000000, 0.069810, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.903503, 0.000000, 0.004260, 0.010978},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.075956, 0.000000, 0.000679, 0.000622},
{0.000000, 0.000000, 0.000000, 0.002913},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.017478},
{0.000000, 0.776425, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.006811, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000935, 0.808358},
{0.018135, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.026217},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.003113, 0.000000}},

{{0.000000, 0.343183, 0.005557, 0.087060},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.314141, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000947, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.908861, 0.000000, 0.002443, 0.000000},
{0.000000, 0.000598, 0.195991, 0.036912},
{0.000000, 0.000000, 0.000000, 0.001772},
{0.000000, 0.177925, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.001127, 0.000073, 0.000000, 0.872484},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.231925, 0.000000},
{0.055838, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.001772},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.335107, 0.000000},
{0.000000, 0.000410, 0.224563, 0.000000},
{0.034173, 0.000000, 0.003468, 0.000000},
{0.000000, 0.163670, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000}},

{{0.381935, 0.440431, 0.000000, 0.014146},
{0.000000, 0.018227, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.010564},
{0.000000, 0.180704, 0.000000, 0.000000},
{0.020653, 0.000000, 0.000000, 0.000000},
{0.327817, 0.002233, 0.000000, 0.000000},
{0.000000, 0.025028, 0.000000, 0.001416},
{0.003442, 0.015623, 0.000000, 0.000000},
{0.000000, 0.002604, 0.000000, 0.000000},
{0.000000, 0.189557, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.024147},
{0.039011, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.617050, 0.000000},
{0.016793, 0.000000, 0.000000, 0.002059},
{0.000000, 0.102590, 0.000000, 0.000000},
{0.020887, 0.000000, 0.000978, 0.000000},
{0.001252, 0.000502, 0.000000, 0.099520},
{0.000000, 0.000000, 0.000000, 0.692704},
{0.002817, 0.020072, 0.000000, 0.000001},
{0.000000, 0.001908, 0.146685, 0.000000},
{0.158337, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000521, 0.084813, 0.000000},
{0.000000, 0.000000, 0.000000, 0.155443},
{0.026389, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.003688, 0.000000},
{0.000667, 0.000000, 0.146787, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000}},

{{0.000000, 0.069914, 0.410794, 0.002956},
{0.002478, 0.000000, 0.000000, 0.001166},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.257267, 0.004298},
{0.000000, 0.022880, 0.000000, 0.000000},
{0.000000, 0.000000, 0.072192, 0.000000},
{0.000000, 0.000000, 0.088521, 0.000000},
{0.000000, 0.000000, 0.018907, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.002542, 0.000000, 0.000000},
{0.002071, 0.035989, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.225903},
{0.000000, 0.000000, 0.000000, 0.008236},
{0.000000, 0.271255, 0.000000, 0.001528},
{0.294557, 0.000006, 0.000919, 0.000000},
{0.009824, 0.000000, 0.000000, 0.000000},
{0.011543, 0.000000, 0.000000, 0.061535},
{0.000000, 0.000000, 0.058441, 0.000000},
{0.000000, 0.000000, 0.017189, 0.000000},
{0.000093, 0.000000, 0.001861, 0.353912},
{0.142453, 0.000001, 0.000000, 0.000000},
{0.491221, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.067035, 0.000000},
{0.041754, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.216086, 0.000000, 0.000000},
{0.000000, 0.000000, 0.006875, 0.000000},
{0.004005, 0.000000, 0.000000, 0.114563},
{0.000000, 0.000000, 0.000000, 0.004706},
{0.000000, 0.000000, 0.000000, 0.221197},
{0.000000, 0.317773, 0.000000, 0.000000},
{0.000000, 0.063555, 0.000000, 0.000000}},

{{0.077630, 0.083465, 0.144233, 0.000044},
{0.000000, 0.000000, 0.001677, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.007063, 0.000000, 0.002563, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.043609, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.017993, 0.000000, 0.000000},
{0.679511, 0.000000, 0.000000, 0.000000},
{0.107609, 0.000000, 0.000000, 0.005205},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.494266, 0.005723},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.251592, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.880549, 0.000000, 0.000919},
{0.000000, 0.000000, 0.055350, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.002470},
{0.000000, 0.000000, 0.000000, 0.012352},
{0.000000, 0.000000, 0.006709, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.017993, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.126137, 0.000000, 0.000000, 0.000000},
{0.002051, 0.000000, 0.000000, 0.973287},
{0.000000, 0.000000, 0.000000, 0.000000}},

{{0.022675, 0.010212, 0.542881, 0.059371},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.041786},
{0.000000, 0.000000, 0.348586, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.035449, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.049384},
{0.015029, 0.000000, 0.000000, 0.000000},
{0.076203, 0.985037, 0.009455, 0.026018},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.011396},
{0.000000, 0.000000, 0.000000, 0.011396},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.761225, 0.000000, 0.010024, 0.000000},
{0.000000, 0.002220, 0.000000, 0.025874},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.001732, 0.053604, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.003799},
{0.120229, 0.000000, 0.000000, 0.000000},
{0.004640, 0.000798, 0.000000, 0.770975},
{0.000000, 0.000000, 0.000000, 0.000000},
{0.000000, 0.000000, 0.000000, 0.000000}}
};

const float Pi[NUM_GEST][NR_OF_STATES]={
{0.250000, 0.250000, 0.250000, 0.250000},

{0.250000, 0.250000, 0.250000, 0.250000},

{0.250000, 0.250000, 0.250000, 0.250000},

{0.250000, 0.250000, 0.250000, 0.250000},

{0.250000, 0.250000, 0.250000, 0.250000},

{0.250000, 0.250000, 0.250000, 0.250000},

{0.250000, 0.250000, 0.250000, 0.250000}
};
