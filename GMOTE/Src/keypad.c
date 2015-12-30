#include "keypad.h"

extern QueueHandle_t communicationMsgQ;
extern TaskHandle_t aqManagerHandle;
QueueHandle_t keypadMsgQ;

int buttons[N_BUTTONS] = {0};

void keypad_init(void);
int  keypad_buttonState(int button);
void disableInterrupt(int button);
void enableInterrupt(int button);
int  keypad_debounceButton(int i);
int  keypad_getCMD(int button);

void keypad_actionReleased(int button);
void keypad_actionPressed(int button);

const int GBUTTON = 0;

void keypad_run(void *arg)
{
	int button;
	int before;
	int after;
	BaseType_t QRes = pdFALSE;
	
	keypad_init();
	
	while(1)
	{
		while(QRes == pdFALSE){
			QRes = xQueueReceive(keypadMsgQ, &button, portMAX_DELAY);
		}
		QRes = pdFALSE;
		
		before = buttons[button];
		disableInterrupt(button);
		after = buttons[button] = keypad_debounceButton(button);
		enableInterrupt(button);
		
		if(after != before){
			if(after == 1)
				keypad_actionPressed(button);
			else
				keypad_actionReleased(button);
		}
	}
}

void keypad_init(void)
{
	/* init Q */ 
	keypadMsgQ = xQueueCreate(5, sizeof(int));
	
	/* init gpio */
	HAL_NVIC_SetPriority(EXTI1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);
	
//	HAL_NVIC_SetPriority(EXTI2_IRQn, 5, 0);
//  HAL_NVIC_EnableIRQ(EXTI2_IRQn);
//	
//	HAL_NVIC_SetPriority(EXTI3_IRQn, 5, 0);
//  HAL_NVIC_EnableIRQ(EXTI3_IRQn);
//	
//	HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
//  HAL_NVIC_EnableIRQ(EXTI4_IRQn);
//	
//  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
//	
//	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
//  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void keypad_actionReleased(int button)
{
	if(button == GBUTTON)
	{
		GREEN(0);
		/* signal aqManager to stop aquiring gesture */
		xTaskNotify(aqManagerHandle, GStop, eSetBits);
	}
}

void keypad_actionPressed(int button)
{
	BaseType_t QRes = pdFALSE;
	int cmd;
	
	if(button == GBUTTON)
	{
		GREEN(1);
		/* signal aqManager to start aquiring gesture */ //osSignalSet(aqManagerId, GStart);
		xTaskNotify(aqManagerHandle, GStart, eSetBits);
	}
	else{
	
	while(QRes == pdFALSE){
		cmd = keypad_getCMD(button);
		QRes = xQueueSend(communicationMsgQ, &cmd, 10);
	}
	}
}

int keypad_getCMD(int button)
{
	return CMD_PP;
}

void disableInterrupt(int button)
{
	if(button == GBUTTON){
		/* enable apropriate interrupt */
		HAL_NVIC_DisableIRQ(EXTI1_IRQn);
	}
}

void enableInterrupt(int button)
{
		if(button == GBUTTON){
		/* disable apropriate interrupt */
		HAL_NVIC_EnableIRQ(EXTI1_IRQn);
	}
}

int keypad_debounceButton(int i)
{
	int buttonCounter = 0;
	int input = 0;
	int output = 0;
	TickType_t start = xTaskGetTickCount();
	
	/* while debounce_time */
	while((xTaskGetTickCount() - start) < DEBOUNCE_TIME){
		
			input = keypad_buttonState(i);
			/* increment or decrement integrator */
			if(input == 0){
				if(buttonCounter > 0)
					buttonCounter--;
			}
			else{
				if(buttonCounter < DEBOUNCE_MAXIMUM){
					buttonCounter++;
				}
			}	
			/* set button according to integrator */
			if(buttonCounter <= 0){
				output = 0;
				buttonCounter = 0; //defensive code to avoid counter corruption
			}
			else if(buttonCounter >= DEBOUNCE_MAXIMUM){
				output = 1;
				buttonCounter = DEBOUNCE_MAXIMUM; //defensive code to avoid counter corruption
			}
	}
	return output;
}

int keypad_buttonState(int button)
{
	if(button == GBUTTON){
		return HAL_GPIO_ReadPin(GBUTTON_PORT, GBUTTON_PIN);;
	} 
	else if(button == 2){
		return 1;
	}
	/* etc */
	else 
		return -1;
}

