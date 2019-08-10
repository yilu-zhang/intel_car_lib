#include "ultrasonic.h"

struct Ultrasonic ultrasonic;

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
		ultrasonic.obstacle_diatance = ultrasonic.pulse_value*0.017; //µ¥Î»cm
	}
};

