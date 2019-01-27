#include "stm32f4xx.h"
#include  "delay.h"
#include "self_define.h"

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);
	led_init();
	car_gpio_init();
	motor_left_pwm_init(1999,21);
	motor_right_pwm_init(1999,21); //84M/84=1Mhz的计数频率,重装载值20000，所以PWM频率为 1M/20000=50hz.	
	LED0_ON;
	LED1_OFF;
	MOTOR_LEFT_STBY_ON;
	MOTOR_RIGHT_STBY_ON;
	MOTOR_LEFT_ADVANCE;
	MOTOR_RIGHT_ADVANCE;
	
	while(1)
	{
		TIM_SetCompare1(TIM3,1999);
		TIM_SetCompare2(TIM3,1999);
		TIM_SetCompare3(TIM3,1999);
		TIM_SetCompare4(TIM3,1999);
		delay_ms(5000);
		TIM_SetCompare1(TIM3,1000);
		TIM_SetCompare2(TIM3,1000);
		TIM_SetCompare3(TIM3,1000);
		TIM_SetCompare4(TIM3,1000);
		delay_ms(5000);		
		TIM_SetCompare1(TIM3,1);
		TIM_SetCompare2(TIM3,1);
		TIM_SetCompare3(TIM3,1);
		TIM_SetCompare4(TIM3,1);
		delay_ms(5000);	
		MOTOR_LEFT_BACK;
		MOTOR_RIGHT_BACK;
		TIM_SetCompare1(TIM3,1999);
		TIM_SetCompare2(TIM3,1999);
		TIM_SetCompare3(TIM3,1999);
		TIM_SetCompare4(TIM3,1999);
		delay_ms(5000);
		
		TIM_SetCompare1(TIM3,1000);
		TIM_SetCompare2(TIM3,1000);
		TIM_SetCompare3(TIM3,1000);
		TIM_SetCompare4(TIM3,1000);
		delay_ms(5000);		
		TIM_SetCompare1(TIM3,1);
		TIM_SetCompare2(TIM3,1);
		TIM_SetCompare3(TIM3,1);
		TIM_SetCompare4(TIM3,1);
		delay_ms(5000);	
		
		//转弯问题待解决
		MOTOR_RIGHT_ADVANCE;
		TIM_SetCompare1(TIM3,1000);
		TIM_SetCompare2(TIM3,1000);
		TIM_SetCompare3(TIM3,500);
		TIM_SetCompare4(TIM3,500);
		delay_ms(5000);	
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   		
		MOTOR_LEFT_STBY_OFF;
		MOTOR_RIGHT_STBY_OFF;
		LED1_ON;
	    LED0_OFF;
	}

}
