#ifndef __CONTROL_H
#define __CONTROL_H

//#include "car_system.h"  //ͷ�ļ��໥���������
#include <stdbool.h>  //bool����
#include "sys.h"
#include "bsp.h"
#include "isr.h"
#include "parameter.h"

enum DC_MOTOR_OP_STATE
{
	DC_MOTOR_OP_STATE_INIT,
	
	DC_MOTOR_OP_STATE_ADVANCE,	
	DC_MOTOR_OP_STATE_BACK,
	DC_MOTOR_OP_STATE_TURN_LEFT,	
	DC_MOTOR_OP_STATE_TURN_RIGHT,
	DC_MOTOR_OP_STATE_STOP,
		
	DC_MOTOR_OP_STATE_FINISH,
	DC_MOTOR_OP_STATE_END,
};

enum DC_MOTOR_OP_TYPE
{
	DC_MOTOR_OP_ADVANCE,
	DC_MOTOR_OP_BACK,
	DC_MOTOR_OP_TURN_LEFT,	
	DC_MOTOR_OP_TURN_RIGHT,
	DC_MOTOR_OP_STOP,
	DC_MOTOR_OP_END,	
};

enum DC_MOTOR_ACTION_TYPE
{
	DC_MOTOR_ACTION_ADVANCE,
	DC_MOTOR_ACTION_BACK,
	DC_MOTOR_ACTION_TURN_LEFT,	
	DC_MOTOR_ACTION_TURN_RIGHT,
	DC_MOTOR_ACTION_STOP,
	DC_MOTOR_ACTION_BRAKE,
	DC_MOTOR_ACTION_END,
	
};

struct DC_Motor_Operation_Function
{
	void (*f[DC_MOTOR_OP_END])();
};

struct DC_Motor_Action_Function
{
	void (*f[DC_MOTOR_ACTION_END])();
};

struct DC_Motor_Operation
{
	enum DC_MOTOR_OP_TYPE type;
	
	bool time_mode_flag;  //��set_dc_motor_operation����action_timeʱ��Ϊ0ʱΪ��ʱ���˶�ģʽ��С��һֱ�˶�������С���˶��趨ʱ��ֹͣ
	uint8_t state;
	
	uint32_t target_time;  
	uint32_t action_time; //ͨ������ʱ�����ǰ�������ת���Ƕ�
	
    struct DC_Motor_Operation_Function fun;
	
    //struct vMoto motor_pwm;
};

struct DC_Motor_Action
{
	enum DC_MOTOR_ACTION_TYPE type;
    struct DC_Motor_Action_Function fun;

    //struct vMoto motor_pwm;
};	

struct DC_Motor
{
	struct DC_Motor_Operation op;
	struct DC_Motor_Action action;
};

void init_dc_motor(void);
//void set_dc_motor_operation(enum DC_MOTOR_OP_TYPE type, uint32_t action_time);
void set_dc_motor_operation(enum DC_MOTOR_OP_TYPE type);

void dc_motor_action_advance(void); //for common.c test()
void dc_motor_action_back(void);
void dc_motor_action_turn_left(void);
void dc_motor_action_turn_right(void);
void dc_motor_action_stop(void);
void dc_motor_action_brake(void);

#endif
