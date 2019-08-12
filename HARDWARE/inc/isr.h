#ifndef __ISR_H
#define __ISR_H

//#include <stdbool.h>
#include "sys.h"
#include "sfr.h"
#include "infrared_remote.h" 

extern uint32_t sys_time;
extern uint8_t system_flag_4ms_1;
extern uint8_t system_flag_4ms_2;

void TIM4_IRQHandler(void);

#endif 
