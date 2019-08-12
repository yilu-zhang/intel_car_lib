#ifndef __CAR_SYSTEM_H
#define __CAR_SYSTEM_H
#include "sys.h"
#include "wheel.h"
#include "mpu6050.h"
#include "parameter.h"
#include "ultrasonic.h"
#include "infrared_remote.h"
#include "steering_engine.h"
#include "application.h"
#include "flow.h"

enum CAR_FLOW_TYPE
{
	CAR_NULL_FLOW=0,								//空
	CAR_FLOW_TYPE_INIT,
	CAR_FLOW_TYPE_MANUAL,
	CAR_FLOW_TYPE_AUTO,
	CAR_FLOW_TYPE_END,
};

struct Flow
{
	enum CAR_FLOW_TYPE type;	//当前正在执行的流程
	enum CAR_FLOW_TYPE switch_type;	 //在flow_switch()函数中切换用
    enum CAR_FLOW_TYPE cmd_switch_type; //手动切换
       
	enum CAR_FLOW_TYPE pre_type;
	enum CAR_FLOW_TYPE  next_type;
	
	bool  allow_swtich_flag;		//zhang
	uint8_t action_type;
	uint32_t flow_start_time;
	uint32_t action_start_time;
	
	uint32_t private_data;
	
	void (*fin_fun)(enum CAR_FLOW_TYPE next_flow_type);  //复杂函数切换时使用
	void (*init_fun)(enum CAR_FLOW_TYPE flow_type);
};

struct Motion_Component
{
	struct DC_Motor dc_motor;
	struct Mpu6050 mpu6050;
	struct Ultrasonic ultrasonic;
	struct Infrared_Remote infrared_remote;
	struct Steering_Engine steering_engine;
};

struct Car
{
	enum CAR_FLOW_TYPE flow_type;  //流程状态
	
	struct Flow *flow;  //当前流程，会使用指针不断切换，如：手动、自动流程
	struct Motion_Component component;  //机器人电机等设备
};

extern struct Car car;

void car_init(void);

#endif
