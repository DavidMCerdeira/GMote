#include "kdtree.h"
#include "error.h"

#define CODE_BOOK_SIZE 16

enum gest { PICTURE = 0, /*, VIDEO, MUSIC, SETTUNGS, PLAY_PAUSE, FULLSCREEN, NEXT, PREVIOUS*/ N_GEST};
typedef enum gest gest;

void codeBook_init(void);

int codebook_idx(gest id, float *pos);