//��Ϊmain����������ģ����м�㣬��main����ֱ�ӵ��ã����к�����������ģ��
#include "application.h"
#include "car_system.h"

/*******************************communication**************************************/
void communication_task(void)
{
	infrared_remote_task();
}

/*******************************sensor**************************************/
void update_sensor_data(void)
{
	ultrasonic_task();
	mpu6050_task();
}

/*******************************control**************************************/
//��ʼ�����������operation��action�ص�����
//�������̣��ı䶯������operation->type,Ȼ��motion_control()-operation-action
void motion_init(void)
{
    init_dc_motor(); 
	init_steering_engine();
}

void dc_motor_control(void)
{
	struct DC_Motor_Operation *op = &car.component.dc_motor.op;
	struct DC_Motor_Action *action = &car.component.dc_motor.action;
	
	op->fun.f[op->type]();  //�ǵü�����
	action->fun.f[action->type]();
}

void steering_engine_control(void)
{
	struct Steering_Engine_Operation *op = &car.component.steering_engine.op;
	struct Steering_Engine_Action *action = &car.component.steering_engine.action;
	
	op->fun.f[op->type]();  //�ǵü�����
	action->fun.f[action->type]();
}

void motion_control(void)
{	
	dc_motor_control();
	steering_engine_control();	
}
