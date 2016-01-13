#ifndef _HMM_PARAM_H
#define _HMM_PARAM_H

#include "HMM_param.h"
#include "codebook_param.h"
#define NR_OF_STATES 10
enum gest {pictures = 0, video, music, settings, play_pause, fullscreen, next, previous, NUM_GEST, NOT_RECOGNIZED};
typedef enum gest gest;

extern const float AT[NUM_GEST][NR_OF_STATES][NR_OF_STATES];
extern const float BT[NUM_GEST][CDBK_SIZE][NR_OF_STATES];
extern const float Pi[NUM_GEST][NR_OF_STATES];

#endif
