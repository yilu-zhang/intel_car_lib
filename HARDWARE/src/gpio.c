#include "gpio.h"

//LED灯初始化
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

//红外遥控初始化
//设置IO以及TIM2_CH1的输入捕获
void infrared_remote_init(void)    			  
{		
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM1_ICInitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//TIM1时钟使能 

	//GPIOA8  复用功能,上拉
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1); //GPIOA8复用为TIM1

	TIM_TimeBaseStructure.TIM_Prescaler=167;  ////预分频器,1M的计数频率,1us加1.	
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=10000;   //设定计数器自动重装值 最大10ms溢出  
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure); 
	  
	//初始化TIM2输入捕获参数
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
	TIM1_ICInitStructure.TIM_ICFilter = 0x03;//IC1F=0003 8个定时器时钟周期滤波
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);//初始化定时器2输入捕获通道
	 


	TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	TIM_Cmd(TIM1,ENABLE ); 	 	//使能定时器1

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//初始化NVIC寄存器

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//初始化NVIC寄存器
}

