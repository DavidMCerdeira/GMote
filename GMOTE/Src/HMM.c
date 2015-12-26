#include "HMM.h"

HMM alphabet_Models[NUM_GEST];
forward fwData[NUM_GEST];

QueueHandle_t framesRdy;

TaskHandle_t forwardTsks[NUM_GEST];
TaskHandle_t hmmCtrlTsk;

EventGroupHandle_t goForward;
EventGroupHandle_t fwComplete;

QueueHandle_t likelyGest;

float32_t vec_content_sum(const float32_t* vector, const int size);

void HMM_Init(){
	
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
		alphabet_Models[i].At = (float**)AT[i];
		alphabet_Models[i].Bt = (float**)BT[i];
		alphabet_Models[i].N  = NR_OF_STATES;
		alphabet_Models[i].M  = CDBK_SIZE;

		alphabet_Models[i].pi   = (float*)Pi[i];
		alphabet_Models[i].gest = (gest)i;
	}
}

void HMM_ControlTsk(void *arg){
	int *buff;
	int i, most_likely = 0;
	EventBits_t fwFinished = 0;
	EventBits_t fwSetMask = 0;
	/* initializing the expected mask for the events that
	 * notify the end of a fw function*/
	for(i=0; i<NUM_GEST; i++)
			fwSetMask |= (0x01 << alphabet_Models[i].gest); 
	
	while(1)
	{
		/* waiting for frames */
		uxQueueMessagesWaitingFromISR(framesRdy);
		
		/* if what was inserted on the queue isn't null,
		 * the aquisition hasn't finished */
		xQueuePeek(framesRdy, buff, 1);
		if(buff != NULL)
		{
			/* notify forward tasks */
			xEventGroupSetBits(goForward, fwSetMask);
			
			/* check if all the forward algorithms ran */
			while(!(fwFinished & fwSetMask))
			{
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
		else 
		{
			/* notify interpret results function */
			for(i = 0; i < NUM_GEST; i++)
			{
				if(fwData[i].prob > fwData[most_likely].prob && fwData[i].prob == fwData[i].prob)
				{
					most_likely = i;
				}
				/* reset algorithm structures */
				fwData[i].firstTime = 1;
				fwData[i].prob = 0;
			}
			
			if(most_likely == 0 && fwData[0].prob != fwData[0].prob)
				most_likely = NOT_RECOGNIZED;
						
			xQueueSendToBack(likelyGest, (void*)&most_likely, 10);
		}
	}
}

void HMM_ForwardTsk(void* rModel){
	
	HMM *ownModel = (HMM*) rModel; // var with the content of the respective model
	EventBits_t waitingBits = 0;   // communication with the control task
	int fwIndex = ownModel->gest;  // to specify an index in the fwData	 
	int frame[FRAME_SIZE];				 // frame in each iteration
	int t, j, O;									 // indexation vars used in the algorithm
	float32_t *curLastFw;					 // stores fw(t-1)
	
	/* temporary vars, used to store data between calculations */
	float32_t temp1[ownModel->N];
	float32_t temp2[ownModel->N];
	
	/* init respetive forward struct */
	fwData[fwIndex].firstTime = 1;
	fwData[fwIndex].Cur_gest = ownModel->gest;
	fwData[fwIndex].N = ownModel->N;
	fwData[fwIndex].T = FRAME_SIZE;
	
	while(1)
	{
		/* waiting for frame */
		while(!(waitingBits & (0x01 << ownModel->gest)))
		{
		 waitingBits = xEventGroupWaitBits(goForward,(0x01 << ownModel->gest), pdTRUE, pdTRUE, portMAX_DELAY); 	
		}
		
		/* get frames values */
		xQueuePeek(framesRdy, frame, 10);
		
		/* prepares factor of scale vector */
		arm_fill_f32(0, fwData[fwIndex].C, FRAME_SIZE);
		
		for(t = 0; t < FRAME_SIZE; t++)
		{
			arm_fill_f32(0, temp2, ownModel->N);		// preparing temp2 var for calculations
			O = frame[t]; 													// sets current observation
			
			/* resets the fw[t] vector */
			arm_fill_f32(0, fwData[fwIndex].fw[t], FRAME_SIZE);
			
			/* being the first time, it requires a diferent calculation */
			if(fwData[fwIndex].firstTime)
			{
				arm_mult_f32(ownModel->pi, ownModel->Bt[O], (fwData[fwIndex].fw[t]), fwData[fwIndex].N);
			}
			else
			{
				if(t == 0) 
					curLastFw = fwData[fwIndex].last_fw;
				else
					curLastFw = fwData[fwIndex].fw[t-1];
				
				for(j = 0; j < ownModel->N; j++)
				{
					arm_mult_f32(ownModel->At[j], curLastFw, temp1, ownModel->N);
					
					/* stores the sum of each line of temp1 */
					temp2[j] = vec_content_sum(temp1, ownModel->N);
				}
				arm_mult_f32(temp2, ownModel->Bt[O], (fwData[fwIndex].fw[t]), fwData[fwIndex].N);
			}
			
			fwData[fwIndex].C[t] = (1.0/vec_content_sum(fwData[fwIndex].fw[t], fwData[fwIndex].N));
			arm_mult_f32(fwData[fwIndex].C, fwData[fwIndex].fw[t], temp2, fwData[fwIndex].N);
			arm_copy_f32(temp2, fwData[fwIndex].fw[t], fwData[fwIndex].N);
			
			/* probability calculation for the respetive model */
			fwData[fwIndex].prob += log10(fwData[fwIndex].C[t]);
		}
		
		/* notifies control task, that the frame's forward algorithm has finished */
		xEventGroupSetBits(fwComplete, (0x01 << ownModel->gest));
		arm_copy_f32(fwData[fwIndex].fw[FRAME_SIZE - 1], fwData[fwIndex].last_fw, fwData[fwIndex].N); 
	}	
}

float32_t vec_content_sum(const float32_t* vector, const int size){
	int i;
	float32_t sum = 0.0;
	
	for(i=0; i < size; i++)
		sum = sum + vector[i];

	return sum;
}
