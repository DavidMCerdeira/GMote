#ifndef _HMM_PARAM_H
#define _HMM_PARAM_H

#define NR_OF_STATES 4
#define CDBK_SIZE 16
#define NR_OF_DIM 6

enum gest {pictures = 0, video, music, settings, play_pause, next, previous, NUM_GEST};
typedef enum gest gest;

extern const float A[NUM_GEST][NR_OF_STATES][NR_OF_STATES];
extern const float B[NUM_GEST][NR_OF_STATES][CDBK_SIZE];
extern const float Pi[NUM_GEST][NR_OF_STATES];
extern const float codeBookData[NUM_GEST][CDBK_SIZE][NR_OF_DIM];

#endif
