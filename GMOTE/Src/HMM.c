#include "HMM.h"

HMM alphabet_Models[NUM_GEST];
forward fwData[NUM_GEST];

QueueHandle_t framesRdy;

EventGroupHandle_t goForward;
EventGroupHandle_t fwComplete;

QueueHandle_t likelyGest;

void HMM_Init(){
	TaskHandle_t forwardTsks[NUM_GEST], hmmCtrlTsk;
	int i;
	char hmm_frwrd[] = {'H','M','M','_','F','R','W','R','D', 0, 0};
	char temp[1];

	/* prepares a structure for each gest the alphabet */
	HMM_Init_models();
	
	/* preparing queue to store the likely gests processing */
	likelyGest = xQueueCreate(5, sizeof(gest));
	
	/* prepare event for fw processing */
	goForward = xEventGroupCreate();
	fwComplete = xEventGroupCreate();
	
	/* whenever the a frame is ready this will store it */
	framesRdy = xQueueCreate( FRAME_SIZE, sizeof(int*));		
	
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
	for(i = 0; i < (int)NUM_GEST; i++){
		alphabet_Models[i].A = (float**)AT[i];
		alphabet_Models[i].B = (float**)BT[i];
		alphabet_Models[i].N = NR_OF_STATES;
		alphabet_Models[i].M = CDBK_SIZE;

		alphabet_Models[i].pi = (float*)Pi[i];
		alphabet_Models[i].gest = (gest)i;
	}
}

void HMM_ControlTsk(void *arg){
	int *buff;
	int i, most_likely;
	EventBits_t fwFinished = 0;
	EventBits_t fwSetMask = 0;
	
	/* initializing the expected mask for the events that
	 * notify the end of a fw function*/
	for(i=0; i<NUM_GEST; i++)
			fwSetMask |= (0x01 << alphabet_Models[i].gest); 
	
	while(1){
		/* waiting for frames */
		uxQueueMessagesWaitingFromISR(framesRdy);
		
		/* if what was inserted on the queue isn't null,
		 * the aquisition hasn't finished */
		xQueuePeek(framesRdy, buff, 1);
		if(buff != NULL){
			
			/* notify forward tasks */
			xEventGroupSetBits(goForward, fwSetMask);
			
			/* check if all the forward algorithms ran */
			while(!(fwFinished & fwSetMask)){
				fwFinished = xEventGroupWaitBits(fwComplete, fwSetMask, pdTRUE, pdTRUE, portMAX_DELAY );
			}
			/* Reset waiting for forward algorithm */
			fwFinished = 0;
			
			/* once every forward of every model has performed,
			 * the resource is consumed */
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
	EventBits_t waitingBits = 0;
	forward ownFw;
	int fwIndex = ownModel->gest;
	
	/* init respetive forward struct */
	fwData[fwIndex].firstTime = 1;
	fwData[fwIndex].Cur_gest = ownModel->gest;
	fwData[fwIndex].N = ownModel->N;
	fwData[fwIndex].T = FRAME_SIZE;
	
	while(1){
		while(!(waitingBits & (0x01 << ownModel->gest))){
		 waitingBits = xEventGroupWaitBits(goForward,(0x01 << ownModel->gest), pdTRUE, pdTRUE, portMAX_DELAY ); 	
		}
		
		/* fw algoritmo */
		
	
		xEventGroupSetBits(fwComplete, (0x01 << ownModel->gest));
	}	
}
