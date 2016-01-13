#ifndef _COMUNICATION_H_
#define _COMUNICATION_H_

#include "nrf24l01.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

#define CMD     0x00
#define NAV     0x80

#define CMD_VOLp  0
#define CMD_VOLm  1
#define CMD_OK    2
#define CMD_FF    3
#define CMD_RW    4
#define NAV_UP    5
#define NAV_DWN   6
#define NAV_L     7
#define NAV_R     8
#define CMD_PP    9
#define CMD_FLS  10
#define CMD_PIC  11
#define CMD_VID  12
#define CMD_MUS  13
#define CMD_SS   14
#define CMD_NXT  15
#define CMD_PRV  16

#define INFO_EQON  (20)
#define INFO_EQOFF (21)

#define NO_CMD (30)

void communication_run(void *arg);

#endif
