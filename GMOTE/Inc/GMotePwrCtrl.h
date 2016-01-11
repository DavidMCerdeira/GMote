#ifndef GMOTE_PWR_CTRL
#define GMOTE_PWR_CTRL

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

extern SemaphoreHandle_t GMotePwrCtrl_Sem;

void GMotePwrCtrl_RefreshTimeoutTimer(void);

void GMotePwrCtrl_Run(void *arg);

#endif
