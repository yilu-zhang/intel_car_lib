#include "stm32f4xx.h"
#include  "delay.h"
#include "self_define.h"

//������ԭ�ӿ���ָ��85ҳ�޸�ʱ��Ƶ�ʣ������Ѿ��޸Ĺ���
int main()
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	
	delay_init(168);
	delay_ms(2000);  //�ȴ���ѹ�ȶ� 
	
	led_init();
	
	car_gpio_init();
	
	motor_left_pwm_init(1999,20);
	motor_right_pwm_init(1999,20); //84M/(20+1)=4Mhz�ļ���Ƶ��,��װ��ֵ(1999+1)=2000������PWMƵ��Ϊ 4M/2000=2khz.	
		
	sys_time_init(839, 0); //84M/(0+1)=84Mhz�ļ���Ƶ��,��װ��ֵ839+1=840������PWMƵ��Ϊ 84M/840=100Khz.
	
	infrared_remote_init();
	
	mpu6050_Init();
	
	load_flash_data();
	
	ultrasonic_timer_init();
	ultrasonic_gpio_init();
	
	steering_engine_pwm_init();
	TIM_SetCompare2(STEERING_ENGINE_TIM,1400);  //90��,��ʼ��ʱ��׼��ǰ��
	delay_ms(2000);

	car_init();  //��ʼ��С����һЩ����
	
		
	//flash_test();

	while(1)
	{
		communication_task();
		update_sensor_data();
		flow_switch();
		flow_process();
		motion_control();
		
		//LED0=!LED0;
		//test();
		//delay_ms(4);
	}
}

