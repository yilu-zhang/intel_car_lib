#ifndef __ISR_H
#define __ISR_H

#include "sys.h"
#include "sfr.h"
#include "infrared_remote.h" 

extern uint32_t sys_time;

void TIM4_IRQHandler(void);

#endif 
