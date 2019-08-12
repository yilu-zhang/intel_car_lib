/***********************************************************************
 *
 *  Subsystem:   
 *  File:         
 *  Author:      ����¯
 *  Description: �жϴ�����
 *  Others:         
 *
 *********************************************************************/
 #include "isr.h"
 #include "car_system.h"
 
 /*******************************system tim***********************************/
uint32_t systick_10us;  //11.93h���
uint32_t systick_ms;    //1193h���
uint8_t system_flag_4ms_1=0;
uint8_t system_flag_4ms_2=0;
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(SYSTEM_TIM,TIM_IT_Update)==SET) //����ж�
	{
		systick_10us++;  
		if(systick_10us%100==0)
		{
			systick_ms++;
		}
		
		if(systick_10us%400==0)
		{
			system_flag_4ms_2 ^= 0x01;
		}

		generate_ultrasonic_trigger_pulse();
	}
	TIM_ClearITPendingBit(SYSTEM_TIM,TIM_IT_Update);  //����жϱ�־λ
}

 /*******************************infrared_remote***********************************/
//��ʱ��1����ж�
void TIM1_UP_TIM10_IRQHandler(void)
{
	struct Infrared_Remote *infra = &car.component.infrared_remote;
	
	if(TIM_GetITStatus(INFRARED_REMOTE_TIM,TIM_IT_Update)==SET) //����ж�
	{
		if(infra->status&0x80)//�ϴ������ݱ����յ���
		{	
			infra->status&=~0X10;						//ȡ���������Ѿ���������
			if((infra->status&0X0F)==0X00)
			{
				infra->status|=1<<6;//����Ѿ����һ�ΰ����ļ�ֵ��Ϣ�ɼ�
			
			}
			
			if((infra->status&0X0F)<14)
			{
				infra->status++;
			}
			else
			{
				infra->status&=~(1<<7);//���������ʶ
				infra->status&=0XF0;	//��ռ�����	
			}						 	   	
		}							    
	}
	TIM_ClearITPendingBit(INFRARED_REMOTE_TIM,TIM_IT_Update);  //����жϱ�־λ 
} 

//��ʱ��1���벶���жϷ������	 
void TIM1_CC_IRQHandler(void)
{ 	
	struct Infrared_Remote *infra = &car.component.infrared_remote;
	
	if(TIM_GetITStatus(INFRARED_REMOTE_TIM,TIM_IT_CC1)==SET) //������(CC1IE)�ж�
	{	  
		if(INFRARED_REMOTE_PIN_IN)//�����ز���
		{
			TIM_OC1PolarityConfig(INFRARED_REMOTE_TIM,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			TIM_SetCounter(INFRARED_REMOTE_TIM,0);	   	//��ն�ʱ��ֵ
			infra->status|=0X10;					//����������Ѿ�������
		}
		else //�½��ز���
		{
			infra->pulse_value=TIM_GetCapture1(TIM1);//��ȡCCR1Ҳ������CC1IF��־λ
			TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0	����Ϊ�����ز���
			if(infra->status&0X10)					//���һ�θߵ�ƽ���� 
			{
 				if(infra->status&0X80)//���յ���������
				{
					
					if(infra->pulse_value>300&&infra->pulse_value<800)	//560Ϊ��׼ֵ,560us
					{
						infra->recive_data<<=1;	//����һλ.
						infra->recive_data|=0;	//���յ�0	   
					}else if(infra->pulse_value>1400&&infra->pulse_value<1800)	//1680Ϊ��׼ֵ,1680us
					{
						infra->recive_data<<=1;	//����һλ.
						infra->recive_data|=1;	//���յ�1
					}else if(infra->pulse_value>2200&&infra->pulse_value<2600)	//�õ�������ֵ���ӵ���Ϣ 2500Ϊ��׼ֵ2.5ms
					{
						infra->key_count++; 		//������������1��
						infra->status&=0XF0;	//��ռ�ʱ��		
					}
 				}else if(infra->pulse_value>4200&&infra->pulse_value<4700)		//4500Ϊ��׼ֵ4.5ms
				{
					infra->status|=1<<7;	//��ǳɹ����յ���������
					infra->key_count=0;		//�����������������
				}						 
			}
			infra->status&=~(1<<4);
		}				 		     	    					   
	}
	TIM_ClearITPendingBit(INFRARED_REMOTE_TIM,TIM_IT_CC1);  //����жϱ�־λ 
}

/*******************************ultrasonic***********************************/
//��ʱ��5���벶���жϷ������	 
void TIM5_IRQHandler(void)
{ 	
	struct Ultrasonic *ultra = &car.component.ultrasonic;
	
	if(TIM_GetITStatus(ULTRASONIC_TIM,TIM_IT_CC1)==SET) //������(CC1IE)�ж�
	{	  
		if(ULTRASONIC_PIN_IN)//�����ز���
		{
			TIM_OC1PolarityConfig(ULTRASONIC_TIM,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			TIM_SetCounter(ULTRASONIC_TIM,0);	   	//��ն�ʱ��ֵ
			ultra->rising_edge_flag  = true;
			//infra->status|=0X10;					//����������Ѿ�������
		}
		else if(ultra->rising_edge_flag)					//���һ�θߵ�ƽ���� //�½��ز���
		{
			ultra->pulse_value =TIM_GetCapture1(TIM5);//��ȡCCR1Ҳ������CC1IF��־λ
			ultra->receive_data_flag = true;
			ultra->rising_edge_flag  = false;
		}				 		     	    					   
	}
	
	//TIM_ClearITPendingBit(ULTRASONIC_TIM,TIM_IT_CC1|TIM_IT_Update);  //����жϱ�־λ 
	TIM_ClearITPendingBit(ULTRASONIC_TIM,TIM_IT_CC1);  //����жϱ�־λ 
}


