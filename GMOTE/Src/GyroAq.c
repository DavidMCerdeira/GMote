#include "GyroAq.h"


volatile int interruptEn = 0;
osSemaphoreId gyroDrdySemaph;
extern volatile osMessageQId gyroFrameReadyMsgQ;

void  runGyroGest(const void * argument){
	

}

void initGyroAq(void){
	MPU_WAKEUP();
	//osSemaphoreDel();
	//gyroDrdySemaph = osSemaphoreCreate(osSemaphore(gyroDRDY),AQ_SIZE);
	
}

