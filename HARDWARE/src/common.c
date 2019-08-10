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

u8 res;
void mpu6050_test(void)
{
	//res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,14,mpu6050.data_buff);
	mpu6050_task();
}

void flash_test(void)
{
	if(!mpu6050.get_offset_flag)
	{
		flash_data.float_data[FLASH_ADDR_MPU6050_GYROX_OFFSET]=(float)1;
		flash_data.float_data[FLASH_ADDR_MPU6050_GYROY_OFFSET]=(float)2;
		flash_data.float_data[FLASH_ADDR_MPU6050_GYROZ_OFFSET]=(float)3;
		store_config_data();		
	}
	
}

uint32_t old_time;
void systick_test(void)
{
	if((systick_ms-old_time)>=1000)
	{
		old_time=systick_ms;
		LED0=!LED0;
	}
}

void ultrasonic_test(void)
{
	ultrasonic_task();
}

