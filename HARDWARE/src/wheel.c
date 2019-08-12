/***********************************************************************
 *
 *  Subsystem:   
 *  File:         
 *  Author:      张溢炉
 *  Description:op-完成整个动作的一系列流程，action-细分动作，如左转 
 *  Others:         
 *
 ***************************************************************W******/
#include "wheel.h"
#include "car_system.h"

//void set_dc_motor_operation(enum DC_MOTOR_OP_TYPE type, uint32_t action_time);  //通过时间转弯时
//供应用层设置运动模式，在operation函数中执行
void set_dc_motor_operation(enum DC_MOTOR_OP_TYPE type) //通过姿态传感器来控制转动角度
{
	struct DC_Motor_Operation *op = &car.component.dc_motor.op;

	if(op->type!= type)
	{
		op->type = type;
		op->state = DC_MOTOR_OP_STATE_INIT;
	}
}
	
void dc_motor_op_advance(void)
{
	struct DC_Motor_Operation *op = &car.component.dc_motor.op;
	struct DC_Motor_Action *action = &car.component.dc_motor.action;

	switch(op->state)
	{
		case DC_MOTOR_OP_STATE_INIT:
			if(action->type != DC_MOTOR_ACTION_STOP)
			{
				action->type = DC_MOTOR_ACTION_BRAKE;
				
				op->target_time = systick_ms + 1000;
				op->state = DC_MOTOR_OP_STATE_ADVANCE;
			}
			
			else
			{
				op->state = DC_MOTOR_OP_STATE_ADVANCE;
			}
			break;
			
		case DC_MOTOR_OP_STATE_ADVANCE:
			if(systick_ms > op->target_time)
			{
				action->type = DC_MOTOR_ACTION_ADVANCE;
				op->state = DC_MOTOR_OP_STATE_FINISH;
			}
			break;
		
		case DC_MOTOR_OP_STATE_FINISH:			
			break;
		
		default:
			break;
	}
}
	
void dc_motor_op_back(void)
{
	struct DC_Motor_Operation *op = &car.component.dc_motor.op;
	struct DC_Motor_Action *action = &car.component.dc_motor.action;

	switch(op->state)
	{
		case DC_MOTOR_OP_STATE_INIT:
			if(action->type != DC_MOTOR_ACTION_STOP)
			{
				action->type = DC_MOTOR_ACTION_BRAKE;
				
				op->target_time = systick_ms + 1000;
				op->state = DC_MOTOR_OP_STATE_BACK;
			}
			
			else
			{
				op->state = DC_MOTOR_OP_STATE_BACK;
			}
			break;
			
		case DC_MOTOR_OP_STATE_BACK:
			if(systick_ms > op->target_time)
			{
				action->type = DC_MOTOR_ACTION_BACK;
				op->state = DC_MOTOR_OP_STATE_FINISH;
			}
			break;
		
		case DC_MOTOR_OP_STATE_FINISH:			
			break;
		
		default:
			break;
	}
}

void dc_motor_op_turn_left(void)
{
	struct DC_Motor_Operation *op = &car.component.dc_motor.op;
	struct DC_Motor_Action *action = &car.component.dc_motor.action;

	switch(op->state)
	{
		case DC_MOTOR_OP_STATE_INIT:
			if(action->type != DC_MOTOR_ACTION_STOP)
			{
				action->type = DC_MOTOR_ACTION_BRAKE;
				
				op->target_time = systick_ms + 1000;
				op->state = DC_MOTOR_OP_STATE_TURN_LEFT;
			}
			
			else
			{
				op->state = DC_MOTOR_OP_STATE_TURN_LEFT;
			}
			break;
			
		case DC_MOTOR_OP_STATE_TURN_LEFT:
			if(systick_ms > op->target_time)
			{
				action->type = DC_MOTOR_ACTION_TURN_LEFT;
				op->state = DC_MOTOR_OP_STATE_FINISH;
			}
			break;
		
		case DC_MOTOR_OP_STATE_FINISH:			
			break;
		
		default:
			break;
	}
}
	
void dc_motor_op_turn_right(void)
{
	struct DC_Motor_Operation *op = &car.component.dc_motor.op;
	struct DC_Motor_Action *action = &car.component.dc_motor.action;

	switch(op->state)
	{
		case DC_MOTOR_OP_STATE_INIT:
			if(action->type != DC_MOTOR_ACTION_STOP)
			{
				action->type = DC_MOTOR_ACTION_BRAKE;
				
				op->target_time = systick_ms + 1000;
				op->state = DC_MOTOR_OP_STATE_TURN_RIGHT;
			}
			
			else
			{
				op->state = DC_MOTOR_OP_STATE_TURN_RIGHT;
			}
			break;
			
		case DC_MOTOR_OP_STATE_TURN_RIGHT:
			if(systick_ms > op->target_time)
			{
				action->type = DC_MOTOR_ACTION_TURN_RIGHT;
				op->state = DC_MOTOR_OP_STATE_FINISH;
			}
			break;
		
		case DC_MOTOR_OP_STATE_FINISH:			
			break;
		
		default:
			break;
	}
}
		
void dc_motor_op_stop(void)
{
	struct DC_Motor_Operation *op = &car.component.dc_motor.op;
	struct DC_Motor_Action *action = &car.component.dc_motor.action;

	switch(op->state)
	{
		case DC_MOTOR_OP_STATE_INIT:
			if(action->type != DC_MOTOR_ACTION_STOP)
			{
				action->type = DC_MOTOR_ACTION_BRAKE;
				
				op->target_time = systick_ms + 1000;
				op->state = DC_MOTOR_OP_STATE_STOP;
			}
			
			else
			{
				op->state = DC_MOTOR_OP_STATE_STOP;
			}
			break;
			
		case DC_MOTOR_OP_STATE_STOP:
			if(systick_ms > op->target_time)
			{
				action->type = DC_MOTOR_ACTION_STOP;
				op->state = DC_MOTOR_OP_STATE_FINISH;
			}
			break;
		
		case DC_MOTOR_OP_STATE_FINISH:			
			break;
		
		default:
			break;
	}
}
	
void dc_motor_action_advance(void)
{	
	MOTOR_LEFT_STBY_ON;
	MOTOR_RIGHT_STBY_ON;
	
	MOTOR_LEFT_UP_ADVANCE;
	MOTOR_LEFT_DOWN_ADVANCE;
	MOTOR_RIGHT_UP_ADVANCE;
	MOTOR_RIGHT_DOWN_ADVANCE;
		
	set_dc_motor_left_up_pwm(DC_MOTOR_HIGH_SPEED);
	set_dc_motor_left_down_pwm(DC_MOTOR_HIGH_SPEED);
	set_dc_motor_right_up_pwm(DC_MOTOR_HIGH_SPEED);
	set_dc_motor_right_down_pwm(DC_MOTOR_HIGH_SPEED);	
}
	
void dc_motor_action_back(void)
{
	MOTOR_LEFT_STBY_ON;
	MOTOR_RIGHT_STBY_ON;
	
	MOTOR_LEFT_UP_BACK;
	MOTOR_LEFT_DOWN_BACK;
	MOTOR_RIGHT_UP_BACK;
	MOTOR_RIGHT_DOWN_BACK;
		
	set_dc_motor_left_up_pwm(DC_MOTOR_HIGH_SPEED);
	set_dc_motor_left_down_pwm(DC_MOTOR_HIGH_SPEED);
	set_dc_motor_right_up_pwm(DC_MOTOR_HIGH_SPEED);
	set_dc_motor_right_down_pwm(DC_MOTOR_HIGH_SPEED);	
}

void dc_motor_action_turn_left(void)
{
	MOTOR_LEFT_STBY_ON;
	//MOTOR_RIGHT_STBY_ON;
	MOTOR_RIGHT_STBY_OFF;
	
	MOTOR_LEFT_UP_BACK;
	MOTOR_LEFT_DOWN_BACK;
	MOTOR_RIGHT_UP_ADVANCE;
	MOTOR_RIGHT_DOWN_ADVANCE;
		
	set_dc_motor_left_up_pwm(DC_MOTOR_TURN_UP_HIGH_SPEED);
	set_dc_motor_left_down_pwm(DC_MOTOR_TURN_DOWN_HIGH_SPEED);
	set_dc_motor_right_up_pwm(DC_MOTOR_TURN_UP_LOW_SPEED);
	set_dc_motor_right_down_pwm(DC_MOTOR_TURN_DOWN_LOW_SPEED);
}
	
void dc_motor_action_turn_right(void)
{
	//MOTOR_LEFT_STBY_ON;
	MOTOR_LEFT_STBY_OFF;
	MOTOR_RIGHT_STBY_ON;	

	MOTOR_LEFT_UP_ADVANCE;
	MOTOR_LEFT_DOWN_ADVANCE;
	MOTOR_RIGHT_UP_BACK;
	MOTOR_RIGHT_DOWN_BACK;	
	
		
	set_dc_motor_left_up_pwm(DC_MOTOR_TURN_UP_LOW_SPEED);
	set_dc_motor_left_down_pwm(DC_MOTOR_TURN_DOWN_LOW_SPEED);
	set_dc_motor_right_up_pwm(DC_MOTOR_TURN_UP_HIGH_SPEED);
	set_dc_motor_right_down_pwm(DC_MOTOR_TURN_DOWN_HIGH_SPEED);	
}

//制动完成再停止	
void dc_motor_action_stop(void)
{
	//后期可根据实际删减部分
	MOTOR_LEFT_STBY_OFF;
	MOTOR_RIGHT_STBY_OFF;
	
	MOTOR_LEFT_UP_STOP;
	MOTOR_LEFT_DOWN_STOP;
	MOTOR_RIGHT_UP_STOP;
	MOTOR_RIGHT_DOWN_STOP;
	
	set_dc_motor_left_up_pwm(DC_MOTOR_STOP_SPEED);
	set_dc_motor_left_down_pwm(DC_MOTOR_STOP_SPEED);
	set_dc_motor_right_up_pwm(DC_MOTOR_STOP_SPEED);
	set_dc_motor_right_down_pwm(DC_MOTOR_STOP_SPEED);
}

//通过减小pwm波占空比至零制动
void dc_motor_action_brake(void)
{
	set_dc_motor_left_up_pwm(DC_MOTOR_STOP_SPEED);
	set_dc_motor_left_down_pwm(DC_MOTOR_STOP_SPEED);
	set_dc_motor_right_up_pwm(DC_MOTOR_STOP_SPEED);
	set_dc_motor_right_down_pwm(DC_MOTOR_STOP_SPEED);
}
	
void init_dc_motor(void)
{
	struct DC_Motor_Operation *op = &car.component.dc_motor.op;
	struct DC_Motor_Action *action = &car.component.dc_motor.action;
	
	op->fun.f[DC_MOTOR_OP_ADVANCE] = dc_motor_op_advance;
	op->fun.f[DC_MOTOR_OP_BACK] = dc_motor_op_back;
	op->fun.f[DC_MOTOR_OP_TURN_LEFT] = dc_motor_op_turn_left;
	op->fun.f[DC_MOTOR_OP_TURN_RIGHT] = dc_motor_op_turn_right;
	op->fun.f[DC_MOTOR_OP_STOP] = dc_motor_op_stop;
	
	action->fun.f[DC_MOTOR_ACTION_ADVANCE] = dc_motor_action_advance;
	action->fun.f[DC_MOTOR_ACTION_BACK] = dc_motor_action_back;
	action->fun.f[DC_MOTOR_ACTION_TURN_LEFT] = dc_motor_action_turn_left;
	action->fun.f[DC_MOTOR_ACTION_TURN_RIGHT] = dc_motor_action_turn_right;
	action->fun.f[DC_MOTOR_ACTION_BRAKE] = dc_motor_action_brake;
	action->fun.f[DC_MOTOR_ACTION_STOP] = dc_motor_action_stop;
}

