#include "common.h"

void test(void)
{
	dc_motor_action_advance();
}

void infrared_remote_test(void)
{
	infrared_remote_task();
	switch(infrared_remote.key)
	{
		case INFRARED_REMOTE_KEY_ADVANCE:
			//dc_motor_action_brake();
			dc_motor_action_advance();
			LED1=!LED1;
			break;
		
		case INFRARED_REMOTE_KEY_BACK:
			//dc_motor_action_brake();
			dc_motor_action_back();
			LED1=!LED1;
			break;
		
		case INFRARED_REMOTE_KEY_TURN_LEFT:
			//dc_motor_action_brake();
			dc_motor_action_turn_left();
			LED1=!LED1;
			break;
		
		case INFRARED_REMOTE_KEY_TURN_RIGHT:
			//dc_motor_action_brake();
			dc_motor_action_turn_right();
			LED1=!LED1;
			break;
		
		case INFRARED_REMOTE_KEY_STOP:
			dc_motor_action_stop();
			LED1=!LED1;
			break;
		
		default:
			dc_motor_action_stop();
			break;
	}

}
