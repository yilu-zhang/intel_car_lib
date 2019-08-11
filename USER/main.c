#include "stm32f4xx.h"
#include  "delay.h"
#include "self_define.h"

//按正点原子开发指南85页修改时钟频率，这里已经修改过来
int main()
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	delay_init(168);
	delay_ms(2000);  //等待电压稳定 
	
	led_init();
	
	car_gpio_init();
	car_init();

	
	motor_left_pwm_init(1999,20);
	motor_right_pwm_init(1999,20); //84M/(20+1)=4Mhz的计数频率,重装载值(1999+1)=2000，所以PWM频率为 4M/2000=2khz.	
		
	sys_time_init(839, 0); //84M/(0+1)=84Mhz的计数频率,重装载值839+1=840，所以PWM频率为 84M/840=100Khz.
	
	infrared_remote_init();
	
	mpu6050_Init();
	
	load_flash_data();
	
	ultrasonic_timer_init();
	ultrasonic_gpio_init();
	
	steering_engine_pwm_init();
	TIM_SetCompare2(STEERING_ENGINE_TIM,1400);  //90度,初始化时对准正前方
	delay_ms(5000);
	
	mpu6050.quaternion.q0 =1;
	//flash_test();

	while(1)
	{
		steering_engine_test();
		//test();
		infrared_remote_test();
		//mpu6050_test();
		ultrasonic_test();
		//systick_test();
		//flow_switch();
		//motion_control();
		//LED0=!LED0;
		delay_ms(4);

	}

}

