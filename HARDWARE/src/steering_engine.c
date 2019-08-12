#include "steering_engine.h"
#include "car_system.h"

float get_steering_engine_angle(void)
{
	return car.component.steering_engine.setting_angle;
}

void set_steering_engine_angle(float angle)
{
	struct Steering_Engine *steer = &car.component.steering_engine;
	if(angle>180)
	{
		angle = 180;
	}
	
	if(angle<0)
	{
		angle = 0;
	}

	//保证每次动作完成，没有霍尔传感器的情况下可以将设置值看成舵机的角度
	//当steer->op.state == STEERING_ENGINE_OP_STATE_END时，角度才有效
	if(steer->op.state == STEERING_ENGINE_OP_STATE_FINISH)
	{
		steer->setting_angle = angle;
		steer->setting_pulse = (int)(angle*10+500);
		steer->op.state = STEERING_ENGINE_OP_STATE_ACTION;
	}
}

void steering_engine_op_turn_fix_angle(void)
{
	struct Steering_Engine_Operation *op = &car.component.steering_engine.op;
	
	switch(op->state)
	{
		case STEERING_ENGINE_OP_STATE_ACTION:
			op->target_time = systick_ms + 1000;
			op->state = STEERING_ENGINE_OP_STATE_WAIT;
			break;
		
		case STEERING_ENGINE_OP_STATE_WAIT:
			if(systick_ms>op->target_time)
			{
				op->state = STEERING_ENGINE_OP_STATE_FINISH;
			}
			break;
			
		case STEERING_ENGINE_OP_STATE_FINISH:
			break;
		
		default:
			break;	
	}
}

void steering_engine_action_turn_fix__angle(void)
{
	TIM_SetCompare2(STEERING_ENGINE_TIM,car.component.steering_engine.setting_pulse);
}

void init_steering_engine(void)
{
	struct Steering_Engine_Operation *op = &car.component.steering_engine.op;
	struct Steering_Engine_Action *action = &car.component.steering_engine.action;
	
	op->fun.f[STEERING_ENGINE_OP_TURN_FIX_ANGLE] = steering_engine_op_turn_fix_angle;
	action->fun.f[STEERING_ENGINE_ACTION_TURN_FIX_ANGLE] = steering_engine_action_turn_fix__angle;
}
