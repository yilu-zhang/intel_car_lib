/***********************************************************************
 *
 *  Subsystem:   
 *  File:         
 *  Author:      ����¯
 *  Description: �ӳ���
 *  Others:         
 *
 *********************************************************************/
#include "tim.h"

/*******PWM��������*******/
//�Ҳ�ֱ�����pwm��TIM3
void motor_right_pwm_init(u32 arr3,u32 psc3)
{
	GPIO_InitTypeDef GPIO_Initstructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);  //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //ʹ��TIM3ʱ��
  //��ʼ��PB0
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Initstructure.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	//GPIO_PinAFConfig(GPIOA,GPIO_PinSource6|GPIO_PinSource7,GPIO_AF_TIM3);	
	//д��������ʽ���ԣ�ֻ���óɹ�PF7
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	//��ʼ��TIM3
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;    
	TIM_TimeBaseInitStructure.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Prescaler =psc3;
	TIM_TimeBaseInitStructure.TIM_Period=arr3;
	TIM_TimeBaseInit(MOTOR_TIM,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode =TIM_OCMode_PWM1;   //ѡ��ʱ��ģʽΪPWM���ϼ���
	TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;//�Ƚ�������Ը�
	TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;
	TIM_OC1Init(MOTOR_TIM,&TIM_OCInitStructure);
	TIM_OC2Init(MOTOR_TIM,&TIM_OCInitStructure);
	

	TIM_OC1PreloadConfig(MOTOR_TIM,TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(MOTOR_TIM,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(MOTOR_TIM,ENABLE);
	
	TIM_Cmd(MOTOR_TIM,ENABLE);
}

//���ֱ�����pwm��TIM3
void motor_left_pwm_init(u32 arr3,u32 psc3)
{ 
    GPIO_InitTypeDef GPIO_Initstructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);  //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //ʹ��TIM3ʱ��
  //��ʼ��PB0
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Initstructure.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
		
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);
	//��ʼ��TIM3
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;    
	TIM_TimeBaseInitStructure.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Prescaler =psc3;
	TIM_TimeBaseInitStructure.TIM_Period=arr3;
	TIM_TimeBaseInit(MOTOR_TIM,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode =TIM_OCMode_PWM1;   //ѡ��ʱ��ģʽΪPWM���ϼ���
	TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;//�Ƚ�������Ը�
	TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;
	TIM_OC3Init(MOTOR_TIM,&TIM_OCInitStructure);
	TIM_OC4Init(MOTOR_TIM,&TIM_OCInitStructure);

	TIM_OC3PreloadConfig(MOTOR_TIM,TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(MOTOR_TIM,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(MOTOR_TIM,ENABLE);
	
	TIM_Cmd(MOTOR_TIM,ENABLE);
}

//ϵͳʱ�ӣ�TIM4
void sys_time_init(u32 arr,u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///ʹ��TIM3ʱ��
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(SYSTEM_TIM,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(SYSTEM_TIM,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(SYSTEM_TIM,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //��ʱ��4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

//����ң�س�ʼ��
//����IO�Լ�TIM1_CH1�����벶��
void infrared_remote_init(void)    			  
{		
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM1_ICInitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//TIM1ʱ��ʹ�� 

	//GPIOA8  ���ù���,����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1); //GPIOA8����ΪTIM1

	TIM_TimeBaseStructure.TIM_Prescaler=167;  ////Ԥ��Ƶ��,1M�ļ���Ƶ��,1us��1.	
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=10000;   //�趨�������Զ���װֵ ���10ms���  
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure); 
	  
	//��ʼ��TIM2���벶�����
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM1_ICInitStructure.TIM_ICFilter = 0x03;//IC1F=0003 8����ʱ��ʱ�������˲�
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);//��ʼ����ʱ��2���벶��ͨ��
	 
	TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	TIM_Cmd(TIM1,ENABLE ); 	 	//ʹ�ܶ�ʱ��1

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//��ʼ��NVIC�Ĵ���

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//��ʼ��NVIC�Ĵ���
}

//����������ʱ�ӳ�ʼ��
//����IO�Լ�TIM5_CH1�����벶��
void ultrasonic_timer_init(void)    			  
{		
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM5_ICInitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//TIM1ʱ��ʹ�� 

	//GPIOA8  ���ù���,����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //GPIOA5����ΪTIM8

	TIM_TimeBaseStructure.TIM_Prescaler=83;  ////Ԥ��Ƶ��,1M�ļ���Ƶ��,1us��1.	
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=60000;   //�趨�������Զ���װֵ ���60ms���,�������ʱ��=4*2/340*1000=23.53(ms)
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure); 
	  
	//��ʼ��TIM8���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0003 8����ʱ��ʱ�������˲�
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);//��ʼ����ʱ��2���벶��ͨ��
	 
	//TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//����CC1IE�����ж�
	TIM_ITConfig(TIM5,TIM_IT_CC1,ENABLE);//����CC1IE�����ж�
	TIM_Cmd(TIM5,ENABLE ); 	 	//ʹ�ܶ�ʱ��1

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//��ʼ��NVIC�Ĵ���

//	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�2
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//��ʼ��NVIC�Ĵ���
}

