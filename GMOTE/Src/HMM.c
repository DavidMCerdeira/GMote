#include "HMM.h"

HMM alphabet_Models[NUM_GEST];

QueueHandle_t framesRdy;
EventGroupHandle_t goForward;
SemaphoreHandle_t forwardFin;
QueueHandle_t likelyGest;

void HMM_Init(){
	TaskHandle_t forwardTsks[NUM_GEST], hmmCtrlTsk;
	int i;
	char hmm_frwrd[] = {'H','M','M','_','F','R','W','R','D', 0, 0};
	char temp[1];

	/* prepares a structure for each gest the alphabet */
	HMM_Init_models();
	
	/* prepare semaphore for forward */
	forwardFin = xSemaphoreCreateBinary();
	likelyGest = xQueueCreate(5, sizeof(gest));
	
	/* prepare event*/
	goForward = xEventGroupCreate();
	
	/* whenever the a frame is ready this will store it */
	framesRdy = xQueueCreate( MAX_FRAMES_NR, sizeof(int*));		
	
	/* creating the HMM main task */
	xTaskCreate(HMM_ControlTsk, "HMM_CTRL", 128, NULL, 0, &hmmCtrlTsk);
	
	/* creating a forward task for each model */
	for(i = 0; i < NUM_GEST; i++)
	{
		temp[0] = '0' + i;
		strcat(hmm_frwrd, temp);
		xTaskCreate(HMM_ForwardTsk, hmm_frwrd, 128,(void*)&alphabet_Models[i], 0, &forwardTsks[i]);
		vTaskSuspend(forwardTsks[i]);
	}	
}

void HMM_Init_models(){
	int i;
	/* prepares each model's matrixes, with the respectives ones 
	 * prepared in HMM_Parm.h */
	for(i = 0; i < NUM_GEST; i++){
		alphabet_Models[i].A = (float**)A[i];
		alphabet_Models[i].B = (float**)B[i];
		alphabet_Models[i].pi = (float*)Pi[i];
		codeBook_init(alphabet_Models[i].codebook, (float**)codeBookData[i]);
		alphabet_Models[i].gest = i;
	}
}

void HMM_ControlTsk(void *arg){
	int *buff, count_frwrd = 0;
	gest i, most_likely;
	
	while(1){
		/* waiting for frames */
		uxQueueMessagesWaitingFromISR(framesRdy);
		
		/* if what was inserted on the queue isn't null,
		 * the aquisition hasn't finished */
		xQueuePeek(framesRdy, buff, 1);
		if(buff != NULL){
			
			/* notify forward tasks */
			for(i = 0; i < NUM_GEST; i++)
				xEventGroupSetBits(goForward,(0x01 << i));
			
			/* check if all the forward algorithms ran */
			while(count_frwrd < NUM_GEST){
				xSemaphoreTake(forwardFin, portMAX_DELAY);
				count_frwrd++;
			}

			/* reset counter of forward algorithm */
			count_frwrd = 0;
			
			/* once every forward of every model has performed,
			 * the resource is consumed*/
			xQueueReceive(framesRdy, buff, 1);
			buff = NULL;
		}
		/* otherwise sends the ID of the most likely gesture */ 
		else {
			/* notify interpret results function*/
			
			/*AVALIAR AQUI QUAL O MELHOR GESTO!! OU NADA*/
			
			//xQueueSendToBack(likelyGest, (void*)&most_likely, 10);
		}
	}
}

void HMM_ForwardTsk(void* rModel){
	HMM *ownModel = (HMM*) rModel;
	

	
}
