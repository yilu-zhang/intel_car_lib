#include "infrared_remote.h"
#include "delay.h"


struct Ifrared_Remote infrared_remote; 

//处理红外键盘
//返回值:
//	 0,没有任何按键按下
//其他,按下的按键键值.
uint8_t infrared_remote_scan(void)
{        
	uint8_t sta=0;       
    uint8_t t1,t2;  
	if(infrared_remote.status&(1<<6))//得到一个按键的所有信息了
	{ 
	    t1=infrared_remote.recive_data>>24;			//得到地址码
	    t2=(infrared_remote.recive_data>>16)&0xff;	//得到地址反码 
 	    if((t1==(u8)~t2)&&t1==REMOTE_ID)//检验遥控识别码(ID)及地址 
	    { 
	        t1=infrared_remote.recive_data>>8;
	        t2=infrared_remote.recive_data; 	
	        if(t1==(u8)~t2)sta=t1;//键值正确	 
		}   
		if((sta==0)||((infrared_remote.status&0X80)==0))//按键数据错误/遥控已经没有按下了
		{
		 	infrared_remote.status&=~(1<<6);//清除接收到有效按键标识
			infrared_remote.key_count=0;		//清除按键次数计数器
		}
	}  
    return sta;
}

void infrared_remote_task(void)
{
	uint8_t key = infrared_remote_scan();
	switch(key)
	{
		case 98:
			infrared_remote.key = INFRARED_REMOTE_KEY_ADVANCE;
			break;
		
		case 168:
			infrared_remote.key = INFRARED_REMOTE_KEY_BACK;
			break;
		
		case 34:
			infrared_remote.key = INFRARED_REMOTE_KEY_TURN_LEFT;
			break;
		
		case 194:
			infrared_remote.key = INFRARED_REMOTE_KEY_TURN_RIGHT;
			break;
		
		case 2:
			infrared_remote.key = INFRARED_REMOTE_KEY_STOP;
			break;
		
		default:
			infrared_remote.key = INFRARED_REMOTE_KEY_NONE;
			break;				
	}
}


