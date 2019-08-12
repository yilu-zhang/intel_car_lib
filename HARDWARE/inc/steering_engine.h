#ifndef __STEERING_ENGINE_H
#define __STEERING_ENGINE_H

#include "sys.h"

enum STEERING_ENGINE_OP_STATE
{	
	STEERING_ENGINE_OP_STATE_ACTION=0,	
	STEERING_ENGINE_OP_STATE_WAIT,
		
	STEERING_ENGINE_OP_STATE_FINISH,
	STEERING_ENGINE_OP_STATE_END,
};

enum STEERING_ENGINE_OP_TYPE
{
	STEERING_ENGINE_OP_TURN_FIX_ANGLE,
	STEERING_ENGINE_OP__END,	
};

enum STEERING_ENGINE_ACTION_TYPE
{
	STEERING_ENGINE_ACTION_TURN_FIX_ANGLE,
	STEERING_ENGINE_ACTION_END,
	
};

struct Steering_Engine_Operation_Function
{
	void (*f[STEERING_ENGINE_OP__END])();
};

struct Steering_Engine_Action_Function
{
	void (*f[STEERING_ENGINE_ACTION_END])();
};

struct Steering_Engine_Operation
{
	enum STEERING_ENGINE_OP_STATE state;
	enum STEERING_ENGINE_OP_TYPE type;	

	uint32_t target_time;
    struct Steering_Engine_Operation_Function fun;
};

struct Steering_Engine_Action
{
	enum STEERING_ENGINE_ACTION_TYPE type;
    struct Steering_Engine_Action_Function fun;
};	

struct Steering_Engine
{
	//当op.state == STEERING_ENGINE_OP_STATE_END时，角度可以当成当前舵机角度
	float setting_angle;  //单位：度，脉宽0.5ms对应0度(向右)，脉宽2.3ms对应180度(向左）
	uint16_t setting_pulse; //setting_angle/180*1800+500

	struct Steering_Engine_Operation op;
	struct Steering_Engine_Action action;
	
};

float get_steering_engine_angle(void);
void set_steering_engine_angle(float angle);
void init_steering_engine(void);


#endif

