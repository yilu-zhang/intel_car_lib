#include "bsp.h"

/*******************************motor***********************************/
void set_dc_motor_left_up_pwm(uint32_t pwm)
{
	if(pwm > DC_MOTOR_MAX_PWM)
	{
		pwm = DC_MOTOR_MAX_PWM;
	}
	
	TIM_SetCompare3(MOTOR_TIM,pwm);
}

void set_dc_motor_left_down_pwm(uint32_t pwm)
{
	if(pwm > DC_MOTOR_MAX_PWM)
	{
		pwm = DC_MOTOR_MAX_PWM;
	}
	
	TIM_SetCompare4(MOTOR_TIM,pwm);
}

void set_dc_motor_right_up_pwm(uint32_t pwm)
{
	if(pwm > DC_MOTOR_MAX_PWM)
	{
		pwm = DC_MOTOR_MAX_PWM;
	}
	
	TIM_SetCompare1(MOTOR_TIM,pwm);
}

void set_dc_motor_right_down_pwm(uint32_t pwm)
{
	if(pwm > DC_MOTOR_MAX_PWM)
	{
		pwm = DC_MOTOR_MAX_PWM;
	}
	
	TIM_SetCompare2(MOTOR_TIM,pwm);
}

