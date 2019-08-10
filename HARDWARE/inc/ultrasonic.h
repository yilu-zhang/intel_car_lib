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
	uint32_t pulse_value;
	float obstacle_diatance;
};

extern struct Ultrasonic ultrasonic;

void ultrasonic_task(void);

#endif

