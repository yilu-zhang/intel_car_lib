#include "ultrasonic.h"
#include "car_system.h"

//�������������������Ϊ30us����
void generate_ultrasonic_trigger_pulse(void)
{
	struct Ultrasonic *ultra = &car.component.ultrasonic; //����д��ʽ����ָֹ��ͽṹ��ͬ������ʹûʲôӰ��
	if(ultra->open_flag)
	{
		if(ultra->open_pulse_wait_rising_edge_flag)
		{
			ultra->falling_target_time_10us = systick_10us + 3;
			OPEN_RISING_EDGE; //��������ߵ�ƽ
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0	���ó���������Ϊ�����ز���
			ultra->open_pulse_wait_rising_edge_flag = false;
		}
		
		else if(systick_10us >= ultra->falling_target_time_10us)
		{
			OPEN_FALLING_EDGE;  //��������͵�ƽ
			ultra->open_flag = false;
			ultra->receive_data_flag = false;
			ultra->rising_edge_flag  = false;
			ultra->open_pulse_wait_rising_edge_flag = true;
		}
	}
}

void ultrasonic_task(void)
{
	struct Ultrasonic *ultra = &car.component.ultrasonic;
	if((systick_ms-ultra->open_time_ms)>=100)
	{
		ultra->open_flag = true;
		ultra->open_pulse_wait_rising_edge_flag=true;
		ultra->open_time_ms = systick_ms;		
	}
	
	if(ultra->receive_data_flag)
	{
		ultra->receive_data_flag = false;
		ultra->obstacle_diatance = ultra->pulse_value*0.017; //��λcm
	}
};

