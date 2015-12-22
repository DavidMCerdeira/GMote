
#define N 3 /*number of state*/
#define M 16 /*codebook size*/


enum gest { PICTURE = 0, /*VIDEO, MUSIC, SETTUNGS, PLAY_PAUSE, FULLSCREEN, NEXT, PREVIOUS,*/ N_GEST};
typedef enum gest gest;

float A[N_GEST][N][N] = 
{
	{
	{0,0,0},
	{0,0,0},
	{0,0,0}
	},
};

float B[N_GEST][N][M] =
{
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	}
};
