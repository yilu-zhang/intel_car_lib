#ifndef __BSP_H
#define __BSP_H

#include "sfr.h"

#define DC_MOTOR_MIN_PWM 0
#define DC_MOTOR_MAX_PWM 1999

void set_dc_motor_left_up_pwm(uint32_t pwm);
void set_dc_motor_left_down_pwm(uint32_t pwm);
void set_dc_motor_right_up_pwm(uint32_t pwm);
void set_dc_motor_right_down_pwm(uint32_t pwm);

#endif
