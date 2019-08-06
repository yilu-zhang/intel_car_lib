#include "infrared_remote.h"
#include "delay.h"


struct Ifrared_Remote infrared_remote; 

//����������
//����ֵ:
//	 0,û���κΰ�������
//����,���µİ�����ֵ.
uint8_t infrared_remote_scan(void)
{        
	uint8_t sta=0;       
    uint8_t t1,t2;  
	if(infrared_remote.status&(1<<6))//�õ�һ��������������Ϣ��
	{ 
	    t1=infrared_remote.recive_data>>24;			//�õ���ַ��
	    t2=(infrared_remote.recive_data>>16)&0xff;	//�õ���ַ���� 
 	    if((t1==(u8)~t2)&&t1==REMOTE_ID)//����ң��ʶ����(ID)����ַ 
	    { 
	        t1=infrared_remote.recive_data>>8;
	        t2=infrared_remote.recive_data; 	
	        if(t1==(u8)~t2)sta=t1;//��ֵ��ȷ	 
		}   
		if((sta==0)||((infrared_remote.status&0X80)==0))//�������ݴ���/ң���Ѿ�û�а�����
		{
		 	infrared_remote.status&=~(1<<6);//������յ���Ч������ʶ
			infrared_remote.key_count=0;		//�����������������
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


