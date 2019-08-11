#include "test.h"

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

//1米内测试正常，误差1cm左右
void ultrasonic_test(void)
{
	ultrasonic_task();
}

//用target_time可以减少运算量
uint32_t test_steering_time=0;
uint8_t test_steering_state=0;
void steering_engine_test(void)
{
	switch(test_steering_state)
	{
		case 0:
			if(systick_ms>=test_steering_time)
			{
				TIM_SetCompare2(STEERING_ENGINE_TIM,500); //0度
				test_steering_state=1;
				test_steering_time = systick_ms + 5000;			
			}
			break;
		
		case 1:
			if(systick_ms>=test_steering_time)
			{
				TIM_SetCompare2(STEERING_ENGINE_TIM,950); //45度
				test_steering_state=2;
				test_steering_time = systick_ms + 5000;			
			}
			break;
			
		case 2:
			if(systick_ms>=test_steering_time)
			{
				TIM_SetCompare2(STEERING_ENGINE_TIM,1400); //90度
				test_steering_state=3;
				test_steering_time = systick_ms + 5000;			
			}
			break;
		
		case 3:
			if(systick_ms>=test_steering_time)
			{
				TIM_SetCompare2(STEERING_ENGINE_TIM,1850); //135度
				test_steering_state=4;
				test_steering_time = systick_ms + 5000;			
			}
			break;
		
		case 4:
			if(systick_ms>=test_steering_time)
			{
				TIM_SetCompare2(STEERING_ENGINE_TIM,2300);  //180度,2300刚好180
				test_steering_state=5;
				test_steering_time = systick_ms + 5000;			
			}
			break;
		
		case 5:
			if(systick_ms>=test_steering_time)
			{
				TIM_SetCompare2(STEERING_ENGINE_TIM,1850); //135度
				test_steering_state=6;
				test_steering_time = systick_ms + 5000;			
			}
			break;
			
		case 6:
			if(systick_ms>=test_steering_time)
			{
				TIM_SetCompare2(STEERING_ENGINE_TIM,1400); //90度
				test_steering_state=7;
				test_steering_time = systick_ms + 5000;			
			}
			break;
		
		case 7:
			if(systick_ms>=test_steering_time)
			{
				TIM_SetCompare2(STEERING_ENGINE_TIM,950); //45度
				test_steering_state=0;
				test_steering_time = systick_ms + 5000;			
			}
			break;
		
		default:
			break;		
	}	
}

