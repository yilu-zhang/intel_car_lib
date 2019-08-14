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
		set_steering_engine_angle(90);
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
		set_steering_engine_angle(90);
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
	struct Flow *flow = &auto_flow;
	struct Ultrasonic *ultra = &car.component.ultrasonic;
	
	static int8_t angle_flag;//向右为正，向左为负
	
	switch(flow->action_type)
	{
		case 0:
			if(ultra->obstacle_diatance > 50)
			{
				set_dc_motor_operation(DC_MOTOR_OP_ADVANCE);
			}
			
			else
			{
				set_dc_motor_operation(DC_MOTOR_OP_STOP);
				flow->action_type = 1;
				flow->action_start_time = systick_ms;
			}
			break;
			
		case 1:
			set_steering_engine_angle(45);
			if(systick_ms-flow->action_start_time>1200)
			{
				if(ultra->obstacle_diatance > 100)
				{
					angle_flag = 1;
					flow->action_type = 6;
				}
				
				else
				{
					flow->action_type = 2;
					flow->action_start_time = systick_ms;
				}
			}
			break;
			
		case 2:
		set_steering_engine_angle(135);
		if(systick_ms-flow->action_start_time>1200)
		{
			if(ultra->obstacle_diatance > 100)
			{
				angle_flag = -1;
				flow->action_type = 6;
			}
			
			else
			{
				flow->action_type = 3;
				flow->action_start_time = systick_ms;
			}
		}
		break;
		
		case 3:
		set_steering_engine_angle(180);
		if(systick_ms-flow->action_start_time>1200)
		{
			if(ultra->obstacle_diatance > 100)
			{
				angle_flag = -2;
				flow->action_type = 6;
			}
			
			else
			{
				flow->action_type = 4;
				flow->action_start_time = systick_ms;
			}
		}
		break;
		
		case 4:
		set_steering_engine_angle(0);
		if(systick_ms-flow->action_start_time>1200)
		{
			if(ultra->obstacle_diatance > 100)
			{
				angle_flag = 2;
				flow->action_type = 6;
			}
			
			else
			{
				flow->action_type = 5;
				flow->action_start_time = systick_ms;
			}
		}
		break;
		
		case 5:
			set_dc_motor_operation(DC_MOTOR_OP_BACK);
			if(systick_ms-flow->action_start_time>1200)
			{
				set_dc_motor_operation(DC_MOTOR_OP_STOP);
				flow->action_type = 1;
				flow->action_start_time = systick_ms;
			}
			break;
				
		case 6:
			//set_steering_engine_angle(90);
			car.component.mpu6050.target_angle = 0;
			if(angle_flag > 0)
			{
				set_dc_motor_operation(DC_MOTOR_OP_TURN_RIGHT);
			}
			
			else
			{
				set_dc_motor_operation(DC_MOTOR_OP_TURN_LEFT);
			}
			flow->action_type = 7;
		    break;
		
		case 7:
			//右转角度为正，左转角度为负
			if((angle_flag > 0&&car.component.mpu6050.target_angle>=(45*angle_flag))||\
				(angle_flag < 0&&car.component.mpu6050.target_angle<=(45*angle_flag)))
			{
				set_steering_engine_angle(90);
				set_dc_motor_operation(DC_MOTOR_OP_STOP);
				flow->action_start_time = systick_ms;
				flow->action_type = 8;
			}
			break;
				
		case 8:
			if(systick_ms-flow->action_start_time>2000)
			{
				set_steering_engine_angle(90);
				flow->action_type = 0;
			}
			
		
		default:
			break;							
	}
	
//	switch(flow->action_type)
//	{
//		case 0:
//			car.component.mpu6050.target_angle = 0;
//			set_dc_motor_operation(DC_MOTOR_OP_TURN_LEFT);
//			flow->action_type = 1;
//		    break;
//		
//		case 1:
//			//右转角度为正，左转角度为负
//			if(car.component.mpu6050.target_angle<=-45)
//			{
//				set_dc_motor_operation(DC_MOTOR_OP_STOP);
//				flow->action_type = 2;
//			}
//			
//		case 2:
//			break;
//		
//		default:
//			break;			
//	}
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

