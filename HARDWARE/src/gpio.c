#include "gpio.h"

//LEDµ∆≥ı ºªØ
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
