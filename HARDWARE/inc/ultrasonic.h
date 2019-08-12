#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

#include <stdbool.h>
#include "sys.h"
#include "sfr.h"

struct Ultrasonic
{
	bool open_flag;
	bool receive_data_flag;
	bool rising_edge_flag; //�Ƿ���յ�������
	bool open_pulse_wait_rising_edge_flag;
	uint32_t falling_target_time_10us;
	uint32_t open_time_ms;
	uint32_t pulse_value;  //������λ��us
	uint32_t update_time;  //���ڱ��������µ�ʱ�䣬�����жϾ����Ƿ���ã��Լ��������Ƿ�û��������
	float obstacle_diatance;  //ʵ�ʾ��룬��λ��cm
};

void generate_ultrasonic_trigger_pulse(void);
void ultrasonic_task(void);


#endif

