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
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode =TIM_OCMode_PWM1;   //ѡ��ʱ��ģʽΪPWM���ϼ���
	TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;//�Ƚ�������Ը�
	TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	

	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
}
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
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode =TIM_OCMode_PWM1;   //ѡ��ʱ��ģʽΪPWM���ϼ���
	TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;//�Ƚ�������Ը�
	TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);

	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);

}

