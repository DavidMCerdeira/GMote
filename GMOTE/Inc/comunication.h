#ifndef _COMUNICATION_H_
#define _COMUNICATION_H_

#include "nrf24l01.h"
#include "cmsis_os.h"

#define comunication_hw_init() nrf24l01_Init()
#define communication_send(...) nrfPrint(__VA_ARGS__)

#define CMD     0x00
#define NAV     0x80

#define CMD_PIC 1
#define CMD_VID 2
#define CMD_MUS 3
#define CMD_SS  4
#define CMD_PP  5
#define CMD_FLS 6
#define CMD_NXT 7
#define CMD_PRV 8

#define NAV_UP  9
#define NAV_DWN 10
#define NAV_L   11
#define NAV_R   12

void communication_run(void *arg);

#endif
