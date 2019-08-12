#include "car_system.h"

struct Car car;

//初始化使小车进入待机状态，设置一些重要参数
void car_init(void)
{	
	init_flow_map();
	
	motion_init();
	
	car.flow_type = CAR_FLOW_TYPE_INIT;
	car.flow = &init_flow;

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
		
	car.component.dc_motor.op.type = DC_MOTOR_OP_STOP;
	car.component.dc_motor.op.state = DC_MOTOR_OP_STATE_INIT;
	car.component.dc_motor.op.target_time = 0;
	car.component.dc_motor.action.type = DC_MOTOR_ACTION_STOP;
	
	car.component.steering_engine.setting_angle = 90;
	car.component.steering_engine.setting_pulse = 1400;
	car.component.steering_engine.op.type = STEERING_ENGINE_OP_TURN_FIX_ANGLE;
	car.component.steering_engine.action.type = STEERING_ENGINE_ACTION_TURN_FIX_ANGLE;
	
	car.component.infrared_remote.key = INFRARED_REMOTE_KEY_STOP;
	
	car.component.mpu6050.quaternion.q0 =1;	
}
