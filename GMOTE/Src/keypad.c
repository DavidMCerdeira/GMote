#include "keypad.h"

extern QueueHandle_t communicationMsgQ;
extern TaskHandle_t aqManagerHandle;
extern TaskHandle_t accelSimpleThreadHandle;
QueueHandle_t keypadMsgQ;

int buttons[N_BUTTONS] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void keypad_init(void);
int  keypad_buttonState(int button);
void setInterruptState(int button, int state);
int  keypad_debounceButton(int i);
int  keypad_getCMD(int button);

void keypad_actionReleased(int button);
void keypad_actionPressed(int button);

const int GMOTE_BUTTON_0 =   0;
const int GMOTE_BUTTON_1 =   1;
const int GMOTE_BUTTON_2 =   2;
const int GMOTE_BUTTON_3 =   3;
const int GMOTE_BUTTON_4 =   4;
const int GMOTE_BUTTON_5 =   5;
const int GMOTE_BUTTON_6 =   6;
const int GMOTE_BUTTON_7 =   7;
const int GMOTE_BUTTON_8 =   8;
const int GMOTE_BUTTON_9 =   9;
const int GMOTE_BUTTON_10 = 10;
const int GMOTE_BUTTON_11 = 11;
const int GMOTE_BUTTON_12 = 12;
const int GMOTE_BUTTON_13 = 13;

int keypad_getButtonFromPin(uint32_t pin)
{
	int idx = 0;
	
	while((GMOTE_BUTTON_0_PIN << idx) != pin)
	{
		idx++;
	}
	
	return idx;
}

void keypad_run(void *arg)
{
	int button;
	int pin;
	int before;
	int after;
	BaseType_t QRes = pdFALSE;
	
	keypad_init();
	
	while(1)
	{
		while(QRes == pdFALSE){
			QRes = xQueueReceive(keypadMsgQ, &pin, portMAX_DELAY);
		}
		QRes = pdFALSE;
		
		button = keypad_getButtonFromPin(pin);
		
		before = buttons[button];
		setInterruptState(button, 0);
		after = buttons[button] = keypad_debounceButton(button);
		setInterruptState(button, 1);
		
		if(after != before){
			if(!after){				
				keypad_actionPressed(button);
			}
			else{
				keypad_actionReleased(button);
			}
			//printf("Button %d->%d\n", button, after);
		}
	}
}

void keypad_init(void)
{
	/* init Q */ 
	keypadMsgQ = xQueueCreate(5, sizeof(int));
	
	/* init gpio */	
	HAL_NVIC_SetPriority(GMOTE_BUTTON_0_EXTI, GMOTE_BUTTONS_IT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(GMOTE_BUTTON_0_EXTI);

	HAL_NVIC_SetPriority(GMOTE_BUTTON_1_EXTI,  GMOTE_BUTTONS_IT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(GMOTE_BUTTON_1_EXTI);

	HAL_NVIC_SetPriority(GMOTE_BUTTON_2_EXTI,  GMOTE_BUTTONS_IT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(GMOTE_BUTTON_2_EXTI);

	HAL_NVIC_SetPriority(GMOTE_BUTTON_3_EXTI,  GMOTE_BUTTONS_IT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(GMOTE_BUTTON_3_EXTI);

	HAL_NVIC_SetPriority(GMOTE_BUTTON_4_EXTI,  GMOTE_BUTTONS_IT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(GMOTE_BUTTON_4_EXTI);

	HAL_NVIC_SetPriority(GMOTE_BUTTON_5_EXTI,  GMOTE_BUTTONS_IT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(GMOTE_BUTTON_5_EXTI);

	HAL_NVIC_SetPriority(GMOTE_BUTTON_6_EXTI,  GMOTE_BUTTONS_IT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(GMOTE_BUTTON_6_EXTI);

	HAL_NVIC_SetPriority(GMOTE_BUTTON_7_EXTI,  GMOTE_BUTTONS_IT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(GMOTE_BUTTON_7_EXTI);

	HAL_NVIC_SetPriority(GMOTE_BUTTON_8_EXTI,  GMOTE_BUTTONS_IT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(GMOTE_BUTTON_8_EXTI);

	HAL_NVIC_SetPriority(GMOTE_BUTTON_9_EXTI,  GMOTE_BUTTONS_IT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(GMOTE_BUTTON_9_EXTI);

	HAL_NVIC_SetPriority(GMOTE_BUTTON_10_EXTI, GMOTE_BUTTONS_IT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(GMOTE_BUTTON_10_EXTI);

	HAL_NVIC_SetPriority(GMOTE_BUTTON_11_EXTI, GMOTE_BUTTONS_IT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(GMOTE_BUTTON_11_EXTI);

//	HAL_NVIC_SetPriority(GMOTE_BUTTON_12_EXTI, GMOTE_BUTTONS_IT_PRIORITY, 0);
//	HAL_NVIC_EnableIRQ(GMOTE_BUTTON_12_EXTI);

}

void keypad_actionReleased(int button)
{
	if((button == GMOTE_BUTTON_0) || (button == GMOTE_BUTTON_8))
	{
		/* signal aqManager to stop aquiring gesture */
		xTaskNotify(aqManagerHandle, GStop, eSetBits);
	}
	else if(button == GMOTE_BUTTON_3)
	{
		
	}
}

void keypad_actionPressed(int button)
{
	BaseType_t QRes = pdFALSE;
	int cmd;
	static int aux_button_1 = 0;
	
	if((button == GMOTE_BUTTON_0 ) || (button == GMOTE_BUTTON_8))
	{
		xTaskNotify(aqManagerHandle, EqOFF, eSetBits);
		/* signal aqManager to start aquiring gesture */
		xTaskNotify(aqManagerHandle, GStart, eSetBits);
	}
	else if(button == GMOTE_BUTTON_3)
	{
		/* signal aqManager to start equilib mode */
		
		if((aux_button_1 = !aux_button_1)){
			xTaskNotify(aqManagerHandle, GStop, eSetBits);
			xTaskNotify(aqManagerHandle, EqON, eSetBits);
		} else {
			xTaskNotify(aqManagerHandle, EqOFF, eSetBits);
		}
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
	int cmd = 0;
	
	if(button == GMOTE_BUTTON_0){
		
	}
	else if(button == GMOTE_BUTTON_1){
		cmd = NAV_DWN;
	}
	else if(button == GMOTE_BUTTON_2){
		cmd = CMD_RW;
	}
	else if(button == GMOTE_BUTTON_3){
		
	}
	else if(button == GMOTE_BUTTON_4){
		cmd = NAV_L;
	}
	else if(button == GMOTE_BUTTON_5){
		cmd = CMD_PP;
	}
	else if(button == GMOTE_BUTTON_6){
		cmd = CMD_VOLm;
	}
	else if(button == GMOTE_BUTTON_7){
		cmd = NAV_UP;
	}
	else if(button == GMOTE_BUTTON_8){
		/*gbutton*/
	}
	else if(button == GMOTE_BUTTON_9){
		cmd = CMD_OK;
	}
	else if(button == GMOTE_BUTTON_10){
		cmd = NAV_R;
	}
	else if(button == GMOTE_BUTTON_11){
		cmd = CMD_FF;
	}
	else if(button == GMOTE_BUTTON_12){
		/*equilb toggle*/
	}
	else if(button == GMOTE_BUTTON_13){
		cmd = CMD_VOLp;
	}
	else{
		cmd = -1;
	}
	
	return cmd;
}

void setInterruptState(int button, int state)
{
	int exti;
	
	if(button == GMOTE_BUTTON_0){
		exti = GMOTE_BUTTON_0_EXTI;
	}
	else if(button == GMOTE_BUTTON_1){
		exti = GMOTE_BUTTON_1_EXTI;
	}
	else if(button == GMOTE_BUTTON_2){
		exti = GMOTE_BUTTON_2_EXTI;
	}
	else if(button == GMOTE_BUTTON_3){
		exti = GMOTE_BUTTON_3_EXTI;
	}
	else if(button == GMOTE_BUTTON_4){
		exti = GMOTE_BUTTON_4_EXTI;
	}
	else if(button == GMOTE_BUTTON_5){
		exti = GMOTE_BUTTON_5_EXTI;
	}
	else if(button == GMOTE_BUTTON_6){
		exti = GMOTE_BUTTON_6_EXTI;
	}
	else if(button == GMOTE_BUTTON_7){
		exti = GMOTE_BUTTON_7_EXTI;
	}
	else if(button == GMOTE_BUTTON_8){
		exti = GMOTE_BUTTON_8_EXTI;
	}
	else if(button == GMOTE_BUTTON_9){
		exti = GMOTE_BUTTON_9_EXTI;
	}
	else if(button == GMOTE_BUTTON_10){
		exti = GMOTE_BUTTON_10_EXTI;
	}
	else if(button == GMOTE_BUTTON_11){
		exti = GMOTE_BUTTON_11_EXTI;
	}
	else if(button == GMOTE_BUTTON_12){
		exti = GMOTE_BUTTON_12_EXTI;
	}
	else if(button == GMOTE_BUTTON_13){
		exti = GMOTE_BUTTON_13_EXTI;
	}
	
	if(state){
		/* enable apropriate interrupt */
		HAL_NVIC_EnableIRQ(exti);
	} else {
		/* disable apropriate interrupt */
		HAL_NVIC_DisableIRQ(exti);
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
	
	if(button == GMOTE_BUTTON_0){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_0_PORT, GMOTE_BUTTON_0_PIN);
	} 
	if(button == GMOTE_BUTTON_1){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_1_PORT, GMOTE_BUTTON_1_PIN);
	} 
	if(button == GMOTE_BUTTON_2){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_2_PORT, GMOTE_BUTTON_2_PIN);
	} 
	if(button == GMOTE_BUTTON_3){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_3_PORT, GMOTE_BUTTON_3_PIN);
	} 
	if(button == GMOTE_BUTTON_4){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_4_PORT, GMOTE_BUTTON_4_PIN);
	} 
	if(button == GMOTE_BUTTON_5){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_5_PORT, GMOTE_BUTTON_5_PIN);
	} 
	if(button == GMOTE_BUTTON_6){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_6_PORT, GMOTE_BUTTON_6_PIN);
	} 
	if(button == GMOTE_BUTTON_7){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_7_PORT, GMOTE_BUTTON_7_PIN);
	} 
	if(button == GMOTE_BUTTON_8){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_8_PORT, GMOTE_BUTTON_8_PIN);
	} 
	if(button == GMOTE_BUTTON_9){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_9_PORT, GMOTE_BUTTON_9_PIN);
	} 
	if(button == GMOTE_BUTTON_10){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_10_PORT, GMOTE_BUTTON_10_PIN);
	} 
	if(button == GMOTE_BUTTON_11){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_11_PORT, GMOTE_BUTTON_11_PIN);
	}
	if(button == GMOTE_BUTTON_12){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_12_PORT, GMOTE_BUTTON_12_PIN);
	} 
	if(button == GMOTE_BUTTON_13){
		return HAL_GPIO_ReadPin(GMOTE_BUTTON_13_PORT, GMOTE_BUTTON_13_PIN);
	} 
	else 
		return -1;
	
}

