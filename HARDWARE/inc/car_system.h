#ifndef __CAR_SYSTEM_H
#define __CAR_SYSTEM_H
#include "sys.h"
#include "control.h"
#include "parameter.h"

extern struct Car car;
enum CAR_FLOW_TYPE
{
	CAR_FLOW_TYPE_INIT,
	CAR_FLOW_TYPE_MANUAL,
	CAR_FLOW_TYPE_END,
};

struct Car
{
	//enum RUN_MODE run_mode;
	//struct System_Setting system_setting;  //系统设置
	//struct Coordinate coordinate;
	
	enum CAR_FLOW_TYPE flow_type;  //流程状态
	
	//struct Flow *flow;
	struct Motion_Component component;  //机器人电机等设备
	
	//uint32_t abnormal_status[ABNORMAL_ARRAY_SIZE];  //异常
	//uint32_t abnormal_mask[ABNORMAL_ARRAY_SIZE];
		
	//uint32_t switch_status;
	
	//struct Wireless wireless;
	//struct Wire wire;
		
	//enum DEBUG_MODE debug_mode;
};

void car_init(void);

#endif
