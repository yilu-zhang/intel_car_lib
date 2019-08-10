/***********************************************************************
 *
 *  Subsystem:   
 *  File:         
 *  Author:      张溢炉
 *  Description: 从车后看
 *  Others:         
 *
 *********************************************************************/
#include "tim.h"

/*******PWM产生函数*******/
//右侧直流电机pwm波TIM3
void motor_right_pwm_init(u32 arr3,u32 psc3)
{
	GPIO_InitTypeDef GPIO_Initstructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);  //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //使能TIM3时钟
  //初始化PB0
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Initstructure.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	//GPIO_PinAFConfig(GPIOA,GPIO_PinSource6|GPIO_PinSource7,GPIO_AF_TIM3);	
	//写成这种形式不对，只配置成功PF7
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	//初始化TIM3
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;    
	TIM_TimeBaseInitStructure.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Prescaler =psc3;
	TIM_TimeBaseInitStructure.TIM_Period=arr3;
	TIM_TimeBaseInit(MOTOR_TIM,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode =TIM_OCMode_PWM1;   //选择定时器模式为PWM向上计数
	TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;//比较输出极性高
	TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;
	TIM_OC1Init(MOTOR_TIM,&TIM_OCInitStructure);
	TIM_OC2Init(MOTOR_TIM,&TIM_OCInitStructure);
	

	TIM_OC1PreloadConfig(MOTOR_TIM,TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(MOTOR_TIM,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(MOTOR_TIM,ENABLE);
	
	TIM_Cmd(MOTOR_TIM,ENABLE);
}

//左侧直流电机pwm波TIM3
void motor_left_pwm_init(u32 arr3,u32 psc3)
{ 
    GPIO_InitTypeDef GPIO_Initstructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);  //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //使能TIM3时钟
  //初始化PB0
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Initstructure.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
		
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);
	//初始化TIM3
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;    
	TIM_TimeBaseInitStructure.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Prescaler =psc3;
	TIM_TimeBaseInitStructure.TIM_Period=arr3;
	TIM_TimeBaseInit(MOTOR_TIM,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode =TIM_OCMode_PWM1;   //选择定时器模式为PWM向上计数
	TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;//比较输出极性高
	TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;
	TIM_OC3Init(MOTOR_TIM,&TIM_OCInitStructure);
	TIM_OC4Init(MOTOR_TIM,&TIM_OCInitStructure);

	TIM_OC3PreloadConfig(MOTOR_TIM,TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(MOTOR_TIM,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(MOTOR_TIM,ENABLE);
	
	TIM_Cmd(MOTOR_TIM,ENABLE);
}

//系统时钟，TIM4
void sys_time_init(u32 arr,u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///使能TIM3时钟
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(SYSTEM_TIM,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(SYSTEM_TIM,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(SYSTEM_TIM,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //定时器4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

//红外遥控初始化
//设置IO以及TIM1_CH1的输入捕获
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

//超声波捕获时钟初始化
//设置IO以及TIM5_CH1的输入捕获
void ultrasonic_timer_init(void)    			  
{		
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM5_ICInitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//TIM1时钟使能 

	//GPIOA8  复用功能,上拉
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //GPIOA5复用为TIM8

	TIM_TimeBaseStructure.TIM_Prescaler=83;  ////预分频器,1M的计数频率,1us加1.	
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=60000;   //设定计数器自动重装值 最大60ms溢出,最大脉冲时间=4*2/340*1000=23.53(ms)
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure); 
	  
	//初始化TIM8输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0003 8个定时器时钟周期滤波
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);//初始化定时器2输入捕获通道
	 
	//TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许CC1IE捕获中断
	TIM_ITConfig(TIM5,TIM_IT_CC1,ENABLE);//允许CC1IE捕获中断
	TIM_Cmd(TIM5,ENABLE ); 	 	//使能定时器1

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//初始化NVIC寄存器

//	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级2
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//初始化NVIC寄存器
}

