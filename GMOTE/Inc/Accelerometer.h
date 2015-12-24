#ifndef _ACCEL_H
#define _ACCEL_H

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "error.h"
#include "discoLeds.h"
#include "sensors.h"

//LIS3DSH

#define ACCEL_INFO1     (0x0D)
#define ACCEL_INFO2     (0x0E)
#define ACCEL_WHO_AM_I  (0x0F)

#define ACCEL_CTRL_REG3 (0x23)
#define ACCEL_CTRL_REG4 (0x20)
#define ACCEL_CTRL_REG5 (0x24)
#define ACCEL_CTRL_REG6 (0x25)

#define ACCEL_OUT_T     (0x0C) //temperature
#define ACCEL_OUT_XL    (0x28)
#define ACCEL_OUT_XH    (0x29)
#define ACCEL_OUT_YL    (0x2A)
#define ACCEL_OUT_YH    (0x2B)
#define ACCEL_OUT_ZL    (0x2C)
#define ACCEL_OUT_ZH    (0x2D)

#define ACCEL_FIFO_CTRL (0x2E)

#define HZ_0					 0
#define HZ_3_125 		0x10
#define HZ_6_25			0x20
#define HZ_12_5			0x30
#define HZ_25				0x40
#define HZ_50				0x50
#define HZ_100			0x60
#define HZ_400			0x70
#define HZ_800 			0x80
#define HZ_1600			0x90
#define EN_ALL_AX 	0x07

void start_accel(int speed);  
void pause_accel(void);

void accel_byteByByte(void);
void accel_fifoEnable(void);

void accelInit(void);
void read_sample(uint8_t* buff);

#endif
