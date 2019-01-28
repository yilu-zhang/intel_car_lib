#ifndef __TIM_H
#define __TIM_H
#include "sys.h"
#include "sfr.h"

void motor_left_pwm_init(u32 arr3,u32 psc3);
void motor_right_pwm_init(u32 arr3,u32 psc3);
void sys_time_init(u32 arr,u32 psc);

#endif
