#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

#include <stdbool.h>
#include "sys.h"
#include "sfr.h"

struct Window_Filter_Struct
{
	uint16_t counter;
	uint16_t data[8];
	uint32_t acc;
	uint32_t result;
};

struct Ultrasonic
{
	bool open_flag;
	bool receive_data_flag;
	bool rising_edge_flag; //�Ƿ���յ�������
	bool open_pulse_wait_rising_edge_flag;
	
	uint16_t pulse_value;  //������λ��us
	
	uint32_t falling_target_time_10us;
	uint32_t open_time_ms;
	uint32_t update_time;  //���ڱ��������µ�ʱ�䣬�����жϾ����Ƿ���ã��Լ��������Ƿ�û��������
	struct Window_Filter_Struct filter;  //�˲���Ӧ̫������С��һֱ���˶�������Ƶ�ʽϵͣ��˲����������󣬴���ӡ�۲�����
};

void generate_ultrasonic_trigger_pulse(void);
void ultrasonic_task(void);


#endif

