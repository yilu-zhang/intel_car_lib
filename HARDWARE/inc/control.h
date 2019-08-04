#ifndef __CONTROL_H
#define __CONTROL_H

//#include "car_system.h"  //头文件相互包含会出错
#include "sys.h"
#include "bsp.h"
#include "isr.h"
#include "parameter.h"

enum DC_MOTOR_OP_STATE
{
	DC_MOTOR_OP_STATE_INIT,
	
	DC_MOTOR_OP_STATE_ADVANCE,
	DC_MOTOR_OP_STATE_ADVANCE_WAIT,
	
	DC_MOTOR_OP_STATE_BACK,
	DC_MOTOR_OP_STATE_BACK_WAIT,
	
	
	DC_MOTOR_OP_STATE_FINISH,
	DC_MOTOR_OP_STATE_FINISH_WAIT,
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
	
	bool time_mode_flag;  //当set_dc_motor_operation（）action_time时间为0时为非时间运动模式，小车一直运动；否则小车运动设定时间停止
	uint8_t state;
	
	uint32_t target_time;  
	uint32_t action_time; //通过动作时间控制前进距离和转动角度
	
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

struct Motion_Component
{
	struct DC_Motor dc_motor;
};

void motion_init(void);
void motion_control(void);
void set_dc_motor_operation(enum DC_MOTOR_OP_TYPE type, uint32_t action_time);

#endif
