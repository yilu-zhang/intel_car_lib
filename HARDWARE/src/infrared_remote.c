#include "infrared_remote.h"
#include "car_system.h"

//处理红外键盘
//返回值:
//0,没有任何按键按下
//其他,按下的按键键值.
uint8_t infrared_remote_scan(void)
{        
	uint8_t sta=0;       
    uint8_t t1,t2;
	struct Infrared_Remote *infra = &car.component.infrared_remote;
	
	if(infra->status&(1<<6))//得到一个按键的所有信息了
	{ 
	    t1=infra->recive_data>>24;			//得到地址码
	    t2=(infra->recive_data>>16)&0xff;	//得到地址反码 
 	    if((t1==(u8)~t2)&&t1==REMOTE_ID)//检验遥控识别码(ID)及地址 
	    { 
	        t1=infra->recive_data>>8;
	        t2=infra->recive_data; 	
	        if(t1==(u8)~t2)sta=t1;//键值正确	 
		}   
		if((sta==0)||((infra->status&0X80)==0))//按键数据错误/遥控已经没有按下了
		{
		 	infra->status&=~(1<<6);//清除接收到有效按键标识
			infra->key_count=0;		//清除按键次数计数器
		}
	}  
    return sta;
}

//case 0:str="ERROR";break			   
//case 162:str="POWER";break	    
//case 98:"UP"    
//case 2:"PLAY"		 
//case 226:"ALIENTEK"	  
//case 194:"RIGHT" 
//case 34:"LEFT"		  
//case 224:"VOL-"		  
//case 168:"DOWN"	   
//case 144:"VOL+"	    
//case 104:"1"	  
//case 152:"2"   
//case 176:"3"    
//case 48:"4";		    
//case 24:"5";		    
//case 122:"6"	  
//case 16:"7"			   					
//case 56:"8"	 
//case 90:"9"
//case 66:"0"
//case 82:"DELETE"	
void infrared_remote_task(void)
{
	uint8_t key = infrared_remote_scan();
	struct Infrared_Remote *infra = &car.component.infrared_remote;

	switch(key)
	{
		case 104://1
			car.flow->switch_type = CAR_FLOW_TYPE_INIT;
			LED0=!LED0;
			break;
		
		case 152://2
			car.flow->switch_type = CAR_FLOW_TYPE_MANUAL;
			LED0=!LED0;
			break;
		
		case 176://3
			car.flow->switch_type = CAR_FLOW_TYPE_AUTO;
			LED0=!LED0;
			break;
		
		case 98://up
			infra->key = INFRARED_REMOTE_KEY_ADVANCE;
			LED0=!LED0;
			break;
		
		case 168://down
			infra->key = INFRARED_REMOTE_KEY_BACK;
			LED0=!LED0;
			break;
		
		case 34://left
			infra->key = INFRARED_REMOTE_KEY_TURN_LEFT;
			LED0=!LED0;
			break;
		
		case 194://right
			infra->key = INFRARED_REMOTE_KEY_TURN_RIGHT;
			LED0=!LED0;
			break;
		
		case 2://play
			infra->key = INFRARED_REMOTE_KEY_STOP;
			LED0=!LED0;
			break;
		
		case 224://vol-
			infra->key = INFRARED_REMOTE_KEY_STEERIN_ENGINE_TURN_LEFT;
			LED0=!LED0;
			break;
		
		case 144://vol+
			infra->key = INFRARED_REMOTE_KEY_STEERIN_ENGINE_TURN_RIGHT;
			LED0=!LED0;
			break;
		
		default:
			infra->key = INFRARED_REMOTE_KEY_NONE;
			break;				
	}
}


