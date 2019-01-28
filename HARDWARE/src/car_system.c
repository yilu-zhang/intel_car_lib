#include "car_system.h"

void car_init(void)
{
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
	
	motion_init();
	
	car.component.dc_motor.op.type = DC_MOTOR_OP_STOP;
	car.component.dc_motor.op.state = DC_MOTOR_OP_STATE_INIT;
	car.component.dc_motor.op.target_time = 0;
	car.component.dc_motor.action.type = DC_MOTOR_ACTION_STOP;
	
}
