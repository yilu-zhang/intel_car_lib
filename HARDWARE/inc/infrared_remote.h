#ifndef __INFRARED_REMOTE_H
#define __INFRARED_REMOTE_H

#include "sys.h"
#include "delay.h"
#include "parameter.h"

enum INFRARED_REMOTE_KEY
{
	INFRARED_REMOTE_KEY_NONE=0,
	INFRARED_REMOTE_KEY_ADVANCE,
	INFRARED_REMOTE_KEY_BACK,
	INFRARED_REMOTE_KEY_TURN_LEFT,
	INFRARED_REMOTE_KEY_TURN_RIGHT,
	INFRARED_REMOTE_KEY_STOP,
	
	INFRARED_REMOTE_KEY_STEERIN_ENGINE_TURN_LEFT,
	INFRARED_REMOTE_KEY_STEERIN_ENGINE_TURN_RIGHT,
	INFRARED_REMOTE_KEY_END,
};

struct Infrared_Remote
{
	//遥控器接收状态
	//[7]:收到了引导码标志
	//[6]:得到了一个按键的所有信息
	//[5]:保留	
	//[4]:标记上升沿是否已经被捕获								   
	//[3:0]:溢出计时器
	uint8_t status;	 
	
	uint8_t  key_count;	//按键按下的次数		
	
	uint16_t pulse_value;		//下降沿时计数器的值
	uint32_t recive_data;	//红外接收到的数据,8位地址码（遥控器编号，此遥控器为0），地址反码，控制码，控制反码	   		    
	
	enum INFRARED_REMOTE_KEY key; 
};

void infrared_remote_task(void);

#endif
