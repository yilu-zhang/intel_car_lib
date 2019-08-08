#ifndef __INFRARED_REMOTE_H
#define __INFRARED_REMOTE_H

#include "sys.h"

#define RDATA PAin(8)	 //�������������

//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 0  

enum INFRARED_REMOTE_KEY
{
	INFRARED_REMOTE_KEY_NONE=0,
	INFRARED_REMOTE_KEY_ADVANCE,
	INFRARED_REMOTE_KEY_BACK,
	INFRARED_REMOTE_KEY_TURN_LEFT,
	INFRARED_REMOTE_KEY_TURN_RIGHT,
	INFRARED_REMOTE_KEY_STOP,
	INFRARED_REMOTE_KEY_END,
};

struct Ifrared_Remote
{
	//ң��������״̬
	//[7]:�յ����������־
	//[6]:�õ���һ��������������Ϣ
	//[5]:����	
	//[4]:����������Ƿ��Ѿ�������								   
	//[3:0]:�����ʱ��
	uint8_t status;	 
	
	uint8_t  key_count;	//�������µĴ���		
	
	uint16_t pulse_value;		//�½���ʱ��������ֵ
	uint32_t recive_data;	//������յ�������,8λ��ַ�루ң������ţ���ң����Ϊ0������ַ���룬�����룬���Ʒ���	   		    
	
	enum INFRARED_REMOTE_KEY key; 
};

extern struct Ifrared_Remote infrared_remote; 

void infrared_remote_task(void);

#endif