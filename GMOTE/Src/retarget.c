#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "nrf24l01.h"

extern UART_HandleTypeDef huart2;

struct __FILE {
  int handle;                 // Add whatever you need here 
};

FILE __stdout;
FILE __stdin;

FILE __nrfOut = { 10 };


/*----------------------------------------------------------------------------
  fputc
 *----------------------------------------------------------------------------*/
int fputc(int ch, FILE *f) {
  
	if(f == &__stdout)
			HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 1000);
	
	else if(f == &__nrfOut)
		nrf24l01_txSend((char*)&ch, 0);
    return ch;
}

/*----------------------------------------------------------------------------
  fgetc
 *----------------------------------------------------------------------------*/
int fgetc(FILE *f) {
	char ch;
	if(f == &__stdin)
			HAL_UART_Receive(&huart2, (uint8_t*)&ch, 1, 1000);
	
	return ch;
}

/*----------------------------------------------------------------------------
  _ttywrch
 *----------------------------------------------------------------------------*/
void _ttywrch(int ch) {
	//write to console
 HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 1000);
}

/*----------------------------------------------------------------------------
  ferror
 *----------------------------------------------------------------------------*/
int ferror(FILE *f) {
                              // Your implementation of ferror
  return EOF;
}

/*----------------------------------------------------------------------------
  _sys_exit
 *----------------------------------------------------------------------------*/
void _sys_exit(int return_code) {
label:  goto label;           // endless loop
}

