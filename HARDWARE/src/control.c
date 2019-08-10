/***********************************************************************
 *
 *  Subsystem:   
 *  File:         
 *  Author:      张溢炉
 *  Description: 
 *  Others:         
 *
 ***************************************************************W******/
#include "control.h"
#include "car_system.h"

struct Car car;

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
				op->state = DC_MOTOR_OP_STATE_ADVANCE_WAIT;
			}
			break;
		
		case DC_MOTOR_OP_STATE_ADVANCE_WAIT:
			if(op->state != DC_MOTOR_OP_ADVANCE)
			{
				action->type = DC_MOTOR_ACTION_BRAKE;
				
				op->target_time = systick_ms + 1000;
				op->state = DC_MOTOR_OP_STATE_FINISH;
			}
		
		case DC_MOTOR_OP_STATE_FINISH:
			if(systick_ms > op->target_time)
			{
				action->type = DC_MOTOR_ACTION_STOP;
			}
			break;
		
		default:
			break;
	}
}
	
void dc_motor_op_back(void)
{}

void dc_motor_op_turn_left(void)
{}
	
void dc_motor_op_turn_right(void)
{}
		
void dc_motor_op_stop(void)
{}
	
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
void dc_motor_control(void)
{
	struct DC_Motor_Operation *op = &car.component.dc_motor.op;
	struct DC_Motor_Action *action = &car.component.dc_motor.action;
	
	op->fun.f[op->type];
	action->fun.f[action->type];
}

void motion_init(void)
{
    init_dc_motor();    
}

void motion_control(void)
{	
	dc_motor_control();
}
