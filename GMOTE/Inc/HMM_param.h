#ifndef _HMM_PARAM_H
#define _HMM_PARAM_H

#define NR_OF_STATES 8
#define CDBK_SIZE 32
#define NR_OF_DIM 6

enum gest {pictures = 0, video, music, settings, play_pause, next, previous, NUM_GEST};
typedef enum gest gest;

extern const float AT[NUM_GEST][NR_OF_STATES][NR_OF_STATES];
extern const float BT[NUM_GEST][CDBK_SIZE][NR_OF_STATES];
extern const float Pi[NUM_GEST][NR_OF_STATES];
extern const float codeBookData[CDBK_SIZE][NR_OF_DIM];

#endif
