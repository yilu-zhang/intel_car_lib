#ifndef __CAR_SYSTEM_H
#define __CAR_SYSTEM_H
#include "sys.h"
#include "wheel.h"
#include "mpu6050.h"
#include "parameter.h"
#include "ultrasonic.h"
#include "infrared_remote.h"
#include "steering_engine.h"
#include "application.h"
#include "flow.h"

enum CAR_FLOW_TYPE
{
	CAR_NULL_FLOW=0,								//��
	CAR_FLOW_TYPE_INIT,
	CAR_FLOW_TYPE_MANUAL,
	CAR_FLOW_TYPE_AUTO,
	CAR_FLOW_TYPE_END,
};

struct Flow
{
	enum CAR_FLOW_TYPE type;	//��ǰ����ִ�е�����
	enum CAR_FLOW_TYPE switch_type;	 //��flow_switch()�������л���
    enum CAR_FLOW_TYPE cmd_switch_type; //�ֶ��л�
       
	enum CAR_FLOW_TYPE pre_type;
	enum CAR_FLOW_TYPE  next_type;
	
	bool  allow_swtich_flag;		//zhang
	uint8_t action_type;
	uint32_t flow_start_time;
	uint32_t action_start_time;
	
	uint32_t private_data;
	
	void (*fin_fun)(enum CAR_FLOW_TYPE next_flow_type);  //���Ӻ����л�ʱʹ��
	void (*init_fun)(enum CAR_FLOW_TYPE flow_type);
};

struct Motion_Component
{
	struct DC_Motor dc_motor;
	struct Mpu6050 mpu6050;
	struct Ultrasonic ultrasonic;
	struct Infrared_Remote infrared_remote;
	struct Steering_Engine steering_engine;
};

struct Obstacle
{
	float obstacle_diatance;  //ʵ�ʾ��룬��λ��cm
};

struct Attitude
{
	uint16_t error_counter;
	int16_t pitch;
	int16_t roll;
	int16_t yaw;
	float float_pitch;
	float float_roll;
	float float_yaw;
	
	float ax;
	float ay;
	float az;
	
	float vx;
	float vy;
	float vz;

	int16_t gyro_pitch;
	int16_t gyro_yaw;
	int16_t gyro_roll;
//	struct Window_Filter_signed filter_yaw;
//	struct Window_Filter_signed filter_pitch;
//	struct Window_Filter_signed filter_roll;
};

struct Car
{
	enum CAR_FLOW_TYPE flow_type;  //����״̬
	
	struct Flow *flow;  //��ǰ���̣���ʹ��ָ�벻���л����磺�ֶ����Զ�����
	struct Motion_Component component;  //�����˵�����豸
	
	struct Obstacle obstacle;
	struct Attitude attitude;
};

extern struct Car car;

void car_init(void);

#endif
