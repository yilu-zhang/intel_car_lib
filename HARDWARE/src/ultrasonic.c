#include "ultrasonic.h"

struct Ultrasonic ultrasonic;

//�������������������Ϊ30us����
void generate_ultrasonic_trigger_pulse(void)
{	
	if(ultrasonic.open_flag)
	{
		if(ultrasonic.open_pulse_wait_rising_edge_flag)
		{
			ultrasonic.falling_target_time_10us = systick_10us + 3;
			OPEN_RISING_EDGE; //��������ߵ�ƽ
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0	���ó���������Ϊ�����ز���
			ultrasonic.open_pulse_wait_rising_edge_flag = false;
		}
		
		else if(systick_10us >= ultrasonic.falling_target_time_10us)
		{
			OPEN_FALLING_EDGE;  //��������͵�ƽ
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
		ultrasonic.obstacle_diatance = ultrasonic.pulse_value*0.017; //��λcm
	}
};

