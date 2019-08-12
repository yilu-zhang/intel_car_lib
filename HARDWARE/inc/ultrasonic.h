#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

#include <stdbool.h>
#include "sys.h"
#include "sfr.h"

struct Ultrasonic
{
	bool open_flag;
	bool receive_data_flag;
	bool rising_edge_flag; //是否接收到上升沿
	bool open_pulse_wait_rising_edge_flag;
	uint32_t falling_target_time_10us;
	uint32_t open_time_ms;
	uint32_t pulse_value;  //脉宽，单位：us
	uint32_t update_time;  //用于保存距离更新的时间，用于判断距离是否可用，以及超声波是否没有数据了
	float obstacle_diatance;  //实际距离，单位：cm
};

void generate_ultrasonic_trigger_pulse(void);
void ultrasonic_task(void);


#endif

