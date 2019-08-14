#ifndef __ISR_H
#define __ISR_H

//#include <stdbool.h>
#include "sys.h"
#include "sfr.h"
#include "infrared_remote.h" 

extern uint32_t sys_time;
extern uint8_t system_flag_4ms_1;
extern uint8_t system_flag_4ms_2;

extern uint32_t systick_10us;  //11.93hÒç³ö
extern uint32_t systick_ms;    //1193hÒç³ö

void TIM4_IRQHandler(void);

#endif 
