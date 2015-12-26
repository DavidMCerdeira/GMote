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
void test_DSP_mult(float32_t *src1, float32_t *src2, int size);
void test_DSP_scale(float32_t *src1, float32_t scale, int size);

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
	framesRdy = xQueueCreate(15, sizeof(int*));		
	
	/* creating the HMM main task */
	xTaskCreate(HMM_ControlTsk, "HMM_CTRL", 256, NULL, GestProcManPriority, &hmmCtrlTsk);
	
	/* creating a forward task for each model */
	for(i = 0; i < NUM_GEST; i++)
	{
		temp[0] = '0' + i;
		hmm_frwrd[10] = temp[0];
		xTaskCreate(HMM_ForwardTsk, hmm_frwrd, 256,(void*)&alphabet_Models[i], GestProcPriority, &forwardTsks[i]);
		//vTaskSuspend(forwardTsks[i]);
	}	
}

void HMM_Init_models(){
	int i;
	/* prepares each model's matrixes, with the respectives ones 
	 * prepared in HMM_Parm.h */
	for(i = 0; i < (int)NUM_GEST; i++){
		alphabet_Models[i].At = (float32_t (*)[NR_OF_STATES][NR_OF_STATES])&AT[i];
		alphabet_Models[i].Bt = (float32_t (*)[CDBK_SIZE][NR_OF_STATES])&BT[i];
		alphabet_Models[i].N  = NR_OF_STATES;
		alphabet_Models[i].M  = CDBK_SIZE;

		alphabet_Models[i].pi   = (float32_t (*)[NR_OF_STATES])&Pi[i];
		alphabet_Models[i].gest = (gest)i;
	}
}

void HMM_ControlTsk(void *arg){
	int *buff;
	int i;
	gest most_likely = 0;
	EventBits_t fwFinished = 0;
	EventBits_t fwSetMask = 0;
	UBaseType_t QMsgW8 = pdFALSE;
	
	/* initializing the expected mask for the events that
	 * notify the end of a fw function*/
	for(i=0; i<NUM_GEST; i++)
			fwSetMask |= (0x01 << (int)alphabet_Models[i].gest); 
	
	while(1)
	{
		/* waiting for frames */
		while(QMsgW8 == pdFALSE){
			QMsgW8 = xQueuePeek(framesRdy, (void*)&buff, portMAX_DELAY);
		}
		QMsgW8 = pdFALSE;
		
		/* if what was inserted on the queue isn't null,
		 * the aquisition hasn't finished */		
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
		}
		/* otherwise sends the ID of the most likely gesture */ 
		else 
		{
			/* notify interpret results function */
			for(i = 0; i < NUM_GEST; i++)
			{
				if((fwData[i].prob == fwData[i].prob) && (fwData[i].prob > fwData[most_likely].prob))
				{
					most_likely = i;
				}
				/* reset algorithm structures */
				fwData[i].firstTime = 1;
				
			}
			
			if(fwData[most_likely].prob != fwData[most_likely].prob)
				most_likely = NOT_RECOGNIZED;
						
			xQueueSendToBack(likelyGest, (void*)&most_likely, 10);
			
			printf("Gesture %d with P = %f\n", most_likely, fwData[most_likely].prob);
			
			for(i = 0; i < NUM_GEST; i++)
			{
				fwData[i].prob = 0;
			}
		}	
		/* once every forward of every model has performed,
		* the resource is consumed */
		xQueueReceive(framesRdy, buff, 1);
		buff = NULL;
	}
}

void HMM_ForwardTsk(void* rModel){
	
	/**TESTE APAGGAR QUANDO n�o precisarmos ->*/// float32_t *TESTE; 
	
	HMM *ownModel = (HMM*) rModel; // var with the content of the respective model
	EventBits_t waitingBits = 0;   // communication with the control task
	int fwIndex = ownModel->gest;  // to specify an index in the fwData	 
	int (*frame)[FRAME_SIZE];				 // frame in each iteration
	int t, j, O;									 // indexation vars used in the algorithm
	float32_t (*curLastFw)[ownModel->N];					 // stores fw(t-1)
		
	BaseType_t semRes = pdFALSE;
	float32_t (*curFw)[ownModel->N];
	
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
		while(semRes == pdFALSE){
			semRes = xQueuePeek(framesRdy, (void*)&frame, 10);
		}
		semRes = pdFALSE;
		
		/* prepares factor of scale vector */
		arm_fill_f32(0, fwData[fwIndex].C, FRAME_SIZE);
		
		for(t = 0; t < FRAME_SIZE; t++)
		{
			arm_fill_f32(0, temp2, ownModel->N);		// preparing temp2 var for calculations
			O = (*frame)[t]; 													// sets current observation
			
			/* resets the fw[t] vector */
			arm_fill_f32(0, fwData[fwIndex].fw[t], FRAME_SIZE);
			
			/* being the first time, it requires a diferent calculation */
			if(fwData[fwIndex].firstTime)
			{
<<<<<<< HEAD
				arm_mult_f32(*(ownModel->pi), (*(ownModel->Bt))[O], (fwData[fwIndex].fw[t]), fwData[fwIndex].N);
=======
<<<<<<< HEAD
				arm_mult_f32(*(ownModel->pi), (*(ownModel->Bt))[O], (fwData[fwIndex].fw[t]), fwData[fwIndex].N);
=======
				arm_mult_f32(*(ownModel->pi), *(ownModel->Bt)[O], (fwData[fwIndex].fw[t]), fwData[fwIndex].N);
>>>>>>> 118dc4133a8dcbbcea7db803c848239ac1c97b5e
>>>>>>> 1c566d3395135c27e7a4cfd6b15f26cf02d324aa
				fwData[fwIndex].firstTime = 0;
			}
			else
			{
				if(t == 0) 
					curLastFw = &fwData[fwIndex].last_fw;
				else
					curLastFw = &(fwData[fwIndex].fw[t-1]);
				
				for(j = 0; j < ownModel->N; j++)
				{
<<<<<<< HEAD
					arm_mult_f32((*(ownModel->At))[j], (float32_t*)(*curLastFw), temp1, ownModel->N);
=======
<<<<<<< HEAD
					arm_mult_f32((*(ownModel->At))[j], (float32_t*)(*curLastFw), temp1, ownModel->N);
					/* stores the sum of each line of temp1 */
					temp2[j] = vec_content_sum(temp1, ownModel->N);
				}
				arm_mult_f32(temp2, (*(ownModel->Bt))[O], (fwData[fwIndex].fw[t]), fwData[fwIndex].N);
=======
					arm_mult_f32(*(ownModel->At)[j], (float32_t*)(*curLastFw), temp1, ownModel->N);
>>>>>>> 1c566d3395135c27e7a4cfd6b15f26cf02d324aa
					
					/* stores the sum of each line of temp1 */
					temp2[j] = vec_content_sum(temp1, ownModel->N);
				}
<<<<<<< HEAD
				arm_mult_f32(temp2, (*(ownModel->Bt))[O], (fwData[fwIndex].fw[t]), fwData[fwIndex].N);
=======
				arm_mult_f32(temp2, *(ownModel->Bt)[O], (fwData[fwIndex].fw[t]), fwData[fwIndex].N);
>>>>>>> 118dc4133a8dcbbcea7db803c848239ac1c97b5e
>>>>>>> 1c566d3395135c27e7a4cfd6b15f26cf02d324aa
			}
			fwData[fwIndex].C[t] = ((float)1.0/vec_content_sum(fwData[fwIndex].fw[t], fwData[fwIndex].N));
<<<<<<< HEAD
=======
			
			test_DSP_scale((float32_t*)fwData[fwIndex].fw[t], fwData[fwIndex].C[t], fwData[fwIndex].N); //TESTE
			
>>>>>>> 1c566d3395135c27e7a4cfd6b15f26cf02d324aa
			arm_scale_f32((float32_t*)fwData[fwIndex].fw[t], fwData[fwIndex].C[t], temp2, fwData[fwIndex].N);
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

void test_DSP_mult(float32_t *src1, float32_t *src2, int size){
	//float32_t src1[] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0};
	//float32_t src2[] = {2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0};
	float32_t dest[8];
	arm_mult_f32(src1,src2,dest, size);
}

void test_DSP_scale(float32_t *src1, float32_t scale, int size){
	float32_t dest[8];

	arm_scale_f32(src1, (float32_t)scale, dest, size);
}
