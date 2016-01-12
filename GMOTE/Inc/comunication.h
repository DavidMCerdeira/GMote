#ifndef _COMUNICATION_H_
#define _COMUNICATION_H_

#include "nrf24l01.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

#define CMD     0x00
#define NAV     0x80

#define CMD_OK  2

#define CMD_FF  3
#define CMD_RW  4

#define CMD_PIC 11
#define CMD_VID 12
#define CMD_MUS 13
#define CMD_SS  14
#define CMD_PP  5
#define CMD_FLS 10
#define CMD_NXT 7
#define CMD_PRV 8

#define NAV_UP  6
#define NAV_DWN 7
#define NAV_L   8
#define NAV_R   9

void communication_run(void *arg);

#endif
