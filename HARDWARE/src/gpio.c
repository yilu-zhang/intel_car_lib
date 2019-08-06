#include "gpio.h"

//LED�Ƴ�ʼ��
void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
}

void car_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_B_InitStructure;
	GPIO_InitTypeDef GPIO_E_InitStructure;
	GPIO_InitTypeDef GPIO_F_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	GPIO_B_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_B_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_B_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_B_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_B_InitStructure.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOB,&GPIO_B_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_14|GPIO_Pin_15);
		
	GPIO_E_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_E_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_E_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_E_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_E_InitStructure.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOE,&GPIO_E_InitStructure);
	GPIO_ResetBits(GPIOE,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);
		
	GPIO_F_InitStructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15;
	GPIO_F_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_F_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_F_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_F_InitStructure.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOF,&GPIO_F_InitStructure);
	GPIO_ResetBits(GPIOF,GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15);
}

//����ң�س�ʼ��
//����IO�Լ�TIM2_CH1�����벶��
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

