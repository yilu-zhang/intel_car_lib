#include "flow.h"

struct Flow init_flow;
struct Flow manual_flow;
struct Flow auto_flow;

struct Flow *flow_map[CAR_FLOW_TYPE_END];

/****************************************************************************
 *
 * Function Name:    init_flow_map
 * Input:            None;
 * Output:           None;
 * Returns:          None;
 * Description:      将Flow结构体变量manual_flow、auto_flow等映射到Flow数组flow_map[].
 * Note:                        
 *
 ***************************************************************************/
void init_flow_map(void)
{
	flow_map[CAR_NULL_FLOW] = 0;
	flow_map[CAR_FLOW_TYPE_INIT] = &init_flow;
	flow_map[CAR_FLOW_TYPE_MANUAL] = &manual_flow;
	flow_map[CAR_FLOW_TYPE_AUTO] = &auto_flow;
}
	
/****************************************************************************
 *
 * Function Name:    get_flow_from_type
 * Input:            type-机器人流程类型;
 * Output:           None;
 * Returns:          flow_map[type]-机器人流程;
 * Description:      通过机器人类型获得机器人流程.
 * Note:                        
 *
 ***************************************************************************/
static struct Flow *get_flow_from_type(enum CAR_FLOW_TYPE type)
{
    return flow_map[type];
}

/****************************************************************************
 *
 * Function Name:    flow_switch_to
 * Input:            current_flow-机器人当前流程;
 *                   new_flow-将切换的新流程；
 * Output:           None;
 * Returns:          None;
 * Description:      将机器人从当前流程切换为新的流程.
 * Note:                       
 *
 ***************************************************************************/
void flow_switch_to(enum CAR_FLOW_TYPE current_flow, enum CAR_FLOW_TYPE new_flow)
{
	//复杂流程切换之间预处理，暂时没用
	if(car.flow->fin_fun)
	{
		car.flow->fin_fun(new_flow);
	}
		
    car.flow_type = new_flow;	
	car.flow = get_flow_from_type(new_flow);  //改变flow指针的指向
	car.flow->pre_type = current_flow;
	car.flow->action_start_time = systick_ms;
	car.flow->action_type = 0;
	car.flow->cmd_switch_type = CAR_NULL_FLOW;
	car.flow->switch_type = CAR_NULL_FLOW;

	//复杂流程切换之间预处理，暂时没用
	if(car.flow->init_fun)
	{
		car.flow->init_fun(current_flow);
	}
}

void init_flow_switch(void)
{
	if(init_flow.switch_type == CAR_FLOW_TYPE_MANUAL)	
	{
		flow_switch_to(CAR_FLOW_TYPE_INIT, CAR_FLOW_TYPE_MANUAL);
	}
	
	if(init_flow.switch_type == CAR_FLOW_TYPE_AUTO)	
	{
		flow_switch_to(CAR_FLOW_TYPE_INIT, CAR_FLOW_TYPE_AUTO);
	}
}

void init_flow_process(void)
{
	
}

void manual_flow_switch(void)
{
	if(manual_flow.switch_type == CAR_FLOW_TYPE_INIT)	
	{
		flow_switch_to(CAR_FLOW_TYPE_MANUAL, CAR_FLOW_TYPE_INIT);
	}
	
	if(manual_flow.switch_type == CAR_FLOW_TYPE_AUTO)	
	{
		flow_switch_to(CAR_FLOW_TYPE_MANUAL, CAR_FLOW_TYPE_AUTO);
	}
}

void manual_flow_process(void)
{
	float getting_steering_angle;
	struct Infrared_Remote *infra = &car.component.infrared_remote;
	
	switch(infra->key)
	{
		case INFRARED_REMOTE_KEY_ADVANCE:
			set_dc_motor_operation(DC_MOTOR_OP_ADVANCE);
			LED1=!LED1;
			break;
		
		case INFRARED_REMOTE_KEY_BACK:
			set_dc_motor_operation(DC_MOTOR_OP_BACK);
			LED1=!LED1;
			break;
		
		case INFRARED_REMOTE_KEY_TURN_LEFT:
			set_dc_motor_operation(DC_MOTOR_OP_TURN_LEFT);
			LED1=!LED1;
			break;
		
		case INFRARED_REMOTE_KEY_TURN_RIGHT:
			set_dc_motor_operation(DC_MOTOR_OP_TURN_RIGHT);
			LED1=!LED1;
			break;
		
		case INFRARED_REMOTE_KEY_STOP:
			set_dc_motor_operation(DC_MOTOR_OP_STOP);
			LED1=!LED1;
			break;
		
		case INFRARED_REMOTE_KEY_STEERIN_ENGINE_TURN_LEFT:
			getting_steering_angle = get_steering_engine_angle();
			set_steering_engine_angle(getting_steering_angle+10);
			LED1=!LED1;
			break;
		
		case INFRARED_REMOTE_KEY_STEERIN_ENGINE_TURN_RIGHT:
			getting_steering_angle = get_steering_engine_angle();
			set_steering_engine_angle(getting_steering_angle-10);
			LED1=!LED1;
			break;
		
		
		default:
			set_dc_motor_operation(DC_MOTOR_OP_STOP);
			break;
	}
}

void auto_flow_switch(void)
{
	if(auto_flow.switch_type == CAR_FLOW_TYPE_MANUAL)	
	{
		flow_switch_to(CAR_FLOW_TYPE_AUTO, CAR_FLOW_TYPE_MANUAL);
	}
	
	if(auto_flow.switch_type == CAR_FLOW_TYPE_INIT)	
	{
		flow_switch_to(CAR_FLOW_TYPE_AUTO, CAR_FLOW_TYPE_INIT);
	}
}

void auto_flow_process(void)
{
	
}

void flow_switch(void)
{
	switch(car.flow_type)
	{
		case CAR_FLOW_TYPE_INIT:
			init_flow_switch();
			break;
		
		case CAR_FLOW_TYPE_MANUAL:
			manual_flow_switch();
			break; 
		
		case CAR_FLOW_TYPE_AUTO:
			auto_flow_switch();
			break;
		
		default:
			break;
			
	}
}
	
void flow_process(void)
{
	switch(car.flow_type)
	{
		case CAR_FLOW_TYPE_INIT:
			init_flow_process();
			break;
		
		case CAR_FLOW_TYPE_MANUAL:
			manual_flow_process();
			break; 
		
		case CAR_FLOW_TYPE_AUTO:
			auto_flow_process();
			break;
		
		default:
			break;
			
	}
}

