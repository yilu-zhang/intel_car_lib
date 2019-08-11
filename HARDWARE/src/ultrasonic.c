#include "ultrasonic.h"

struct Ultrasonic ultrasonic;

//开启超声波，产生宽度为30us脉冲
void generate_ultrasonic_trigger_pulse(void)
{	
	if(ultrasonic.open_flag)
	{
		if(ultrasonic.open_pulse_wait_rising_edge_flag)
		{
			ultrasonic.falling_target_time_10us = systick_10us + 3;
			OPEN_RISING_EDGE; //引脚输出高电平
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0	设置超声波输入为上升沿捕获
			ultrasonic.open_pulse_wait_rising_edge_flag = false;
		}
		
		else if(systick_10us >= ultrasonic.falling_target_time_10us)
		{
			OPEN_FALLING_EDGE;  //引脚输出低电平
			ultrasonic.open_flag = false;
			ultrasonic.receive_data_flag = false;
			ultrasonic.rising_edge_flag  = false;
			ultrasonic.open_pulse_wait_rising_edge_flag = true;
		}
	}
}

void ultrasonic_task(void)
{
	if((systick_ms-ultrasonic.open_time_ms)>=100)
	{
		ultrasonic.open_flag = true;
		ultrasonic.open_pulse_wait_rising_edge_flag=true;
		ultrasonic.open_time_ms = systick_ms;		
	}
	
	if(ultrasonic.receive_data_flag)
	{
		ultrasonic.receive_data_flag = false;
		ultrasonic.obstacle_diatance = ultrasonic.pulse_value*0.017; //单位cm
	}
};

