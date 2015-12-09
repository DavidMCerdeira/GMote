#include "sensor.h"

void printBuffer(aquisitn aq)
{
	int j = 0;

	for(j = 0; j < AQ_SIZE; j++){
		printf("%+06hd\t%+06hd\t%+06hd\n", aq.samples[0][j], 
																			 aq.samples[1][j], 
																			 aq.samples[2][j]);
	}
}

void initBuffer(aquisitn *aq)
{	
	aq->end = aq->start = 0;

}

// each frame contains FRAME_OVERLAP + FRAME_SIZE elements
// the first samples from the previous frame
// and the rest from the current
// return  0 if ok
// return -1 if not enough samples
// note: a conditional variable should be used in order to avoid polling
int get_nextFrame(int16_t** buff, aquisitn *m_aq, int *firstTime)
{	
	// are there previous samples 
	if(m_aq->start >= (FRAME_OVERLAP - 1)){
		// if there are enough samples to make a frame
		if((m_aq->end - m_aq->start) >= (FRAME_SIZE-1)){
			buff[0] = &m_aq->samples[0][m_aq->start - FRAME_OVERLAP];
			buff[1] = &m_aq->samples[1][m_aq->start - FRAME_OVERLAP];
			buff[2] = &m_aq->samples[2][m_aq->start - FRAME_OVERLAP];
			m_aq->start += FRAME_SIZE;
			goto OK;
		}
	}
	// if it's the first time and there are enough samples to make a frame 
	else if(firstTime && (m_aq->end - m_aq->start) >= ((FRAME_SIZE-1) + FRAME_OVERLAP)){
		buff[0] = &m_aq->samples[0][m_aq->start];
		buff[1] = &m_aq->samples[1][m_aq->start];
		buff[2] = &m_aq->samples[2][m_aq->start];
		
		m_aq->start += FRAME_SIZE + FRAME_OVERLAP;
		firstTime = 0;
		goto OK;
	}
	
	return -1;
	
OK:
	return 0;
}
