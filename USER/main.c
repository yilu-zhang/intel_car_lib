#include "stm32f4xx.h"
#include  "delay.h"
#include "self_define.h"

//按正点原子开发指南85页修改时钟频率，这里已经修改过来

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);
	led_init();
	car_gpio_init();
	motor_left_pwm_init(1999,21);
	motor_right_pwm_init(1999,21); //84M/21=4Mhz的计数频率,重装载值2000，所以PWM频率为 4M/2000=2khz.	
	
	sys_time_init(1999, 42); //84M/42=2Mhz的计数频率,重装载值2000，所以PWM频率为 2M/2000=1khz.
	car_init();
	infrared_remote_init();
	MPU_Init();
	load_flash_data();
	//flash_test();
	mpu6050.quaternion.q0 =1;

	while(1)
	{
		//test();
		//infrared_remote_test();
		mpu6050_test();
		delay_ms(4);
		//flow_switch();
		//motion_control();
	}

}

//MOTOR_LEFT_STBY_ON;
//	MOTOR_LEFT_UP_ADVANCE;
//	set_dc_motor_left_up_pwm(1000);
//	delay_ms(3000);
//	set_dc_motor_left_up_pwm(0);
//	delay_ms(3000);
//	MOTOR_LEFT_UP_BACK;
//	set_dc_motor_left_up_pwm(1000);
//	delay_ms(3000);
//	set_dc_motor_left_up_pwm(0);
//	MOTOR_LEFT_DOWN_ADVANCE;
//	set_dc_motor_left_down_pwm(1000);
//	delay_ms(3000);
//	set_dc_motor_left_down_pwm(0);
//	delay_ms(3000);
//	MOTOR_LEFT_DOWN_BACK;
//	set_dc_motor_left_down_pwm(1000);
//	delay_ms(3000);
//	set_dc_motor_left_down_pwm(0);
//	delay_ms(3000);
//	MOTOR_LEFT_STBY_OFF;
//	
//	MOTOR_RIGHT_STBY_ON;
//	MOTOR_RIGHT_UP_ADVANCE;
//	set_dc_motor_right_up_pwm(1000);
//	delay_ms(3000);
//	set_dc_motor_right_up_pwm(0);
//	delay_ms(3000);
//	MOTOR_RIGHT_UP_BACK;
//	set_dc_motor_right_up_pwm(1000);
//	delay_ms(3000);
//	set_dc_motor_right_up_pwm(0);
//	MOTOR_RIGHT_DOWN_ADVANCE;
//	set_dc_motor_right_down_pwm(1000);
//	delay_ms(3000);
//	set_dc_motor_right_down_pwm(0);
//	delay_ms(3000);
//	MOTOR_RIGHT_DOWN_BACK;
//	set_dc_motor_right_down_pwm(1000);
//	delay_ms(3000);
//	set_dc_motor_right_down_pwm(0);
//	delay_ms(3000);
//	MOTOR_RIGHT_STBY_OFF;
