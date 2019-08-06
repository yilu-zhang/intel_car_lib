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
 
 /*******************************system tim***********************************/
uint32_t sys_time;
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(SYSTEM_TIM,TIM_IT_Update)==SET) //����ж�
	{
		sys_time++;
	}
	TIM_ClearITPendingBit(SYSTEM_TIM,TIM_IT_Update);  //����жϱ�־λ
}

 /*******************************infrared_remote***********************************/
//��ʱ��1����ж�
void TIM1_UP_TIM10_IRQHandler(void)
{
 
  if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET) //����ж�
	{
		if(infrared_remote.status&0x80)//�ϴ������ݱ����յ���
		{	
			infrared_remote.status&=~0X10;						//ȡ���������Ѿ���������
			if((infrared_remote.status&0X0F)==0X00)
			{
				infrared_remote.status|=1<<6;//����Ѿ����һ�ΰ����ļ�ֵ��Ϣ�ɼ�
			
			}
			
			if((infrared_remote.status&0X0F)<14)
			{
				infrared_remote.status++;
			}
			else
			{
				infrared_remote.status&=~(1<<7);//���������ʶ
				infrared_remote.status&=0XF0;	//��ռ�����	
			}						 	   	
		}							    
	}
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);  //����жϱ�־λ 
} 
//��ʱ��1���벶���жϷ������	 
void TIM1_CC_IRQHandler(void)
{ 		    	 
	if(TIM_GetITStatus(TIM1,TIM_IT_CC1)==SET) //������(CC1IE)�ж�
	{	  
		if(RDATA)//�����ز���
		{
			TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			TIM_SetCounter(TIM1,0);	   	//��ն�ʱ��ֵ
			infrared_remote.status|=0X10;					//����������Ѿ�������
		}else //�½��ز���
		{
			infrared_remote.pulse_value=TIM_GetCapture1(TIM1);//��ȡCCR1Ҳ������CC1IF��־λ
			TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0	����Ϊ�����ز���
			if(infrared_remote.status&0X10)					//���һ�θߵ�ƽ���� 
			{
 				if(infrared_remote.status&0X80)//���յ���������
				{
					
					if(infrared_remote.pulse_value>300&&infrared_remote.pulse_value<800)	//560Ϊ��׼ֵ,560us
					{
						infrared_remote.recive_data<<=1;	//����һλ.
						infrared_remote.recive_data|=0;	//���յ�0	   
					}else if(infrared_remote.pulse_value>1400&&infrared_remote.pulse_value<1800)	//1680Ϊ��׼ֵ,1680us
					{
						infrared_remote.recive_data<<=1;	//����һλ.
						infrared_remote.recive_data|=1;	//���յ�1
					}else if(infrared_remote.pulse_value>2200&&infrared_remote.pulse_value<2600)	//�õ�������ֵ���ӵ���Ϣ 2500Ϊ��׼ֵ2.5ms
					{
						infrared_remote.key_count++; 		//������������1��
						infrared_remote.status&=0XF0;	//��ռ�ʱ��		
					}
 				}else if(infrared_remote.pulse_value>4200&&infrared_remote.pulse_value<4700)		//4500Ϊ��׼ֵ4.5ms
				{
					infrared_remote.status|=1<<7;	//��ǳɹ����յ���������
					infrared_remote.key_count=0;		//�����������������
				}						 
			}
			infrared_remote.status&=~(1<<4);
		}				 		     	    					   
	}
	TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);  //����жϱ�־λ 
}

