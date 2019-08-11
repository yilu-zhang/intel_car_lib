/***********************************************************************
 *
 *  Subsystem:   
 *  File:         
 *  Author:      张溢炉
 *  Description: 中断处理函数
 *  Others:         
 *
 *********************************************************************/
 #include "isr.h"
 #include "ultrasonic.h"
 
 /*******************************system tim***********************************/
uint32_t systick_10us;  //11.93h溢出
uint32_t systick_ms;    //1193h溢出
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(SYSTEM_TIM,TIM_IT_Update)==SET) //溢出中断
	{
		systick_10us++;  
		if(systick_10us%100==0)
		{
			systick_ms++;
		}

		generate_ultrasonic_trigger_pulse();
	}
	TIM_ClearITPendingBit(SYSTEM_TIM,TIM_IT_Update);  //清除中断标志位
}

 /*******************************infrared_remote***********************************/
//定时器1溢出中断
void TIM1_UP_TIM10_IRQHandler(void)
{
 
  if(TIM_GetITStatus(INFRARED_REMOTE_TIM,TIM_IT_Update)==SET) //溢出中断
	{
		if(infrared_remote.status&0x80)//上次有数据被接收到了
		{	
			infrared_remote.status&=~0X10;						//取消上升沿已经被捕获标记
			if((infrared_remote.status&0X0F)==0X00)
			{
				infrared_remote.status|=1<<6;//标记已经完成一次按键的键值信息采集
			
			}
			
			if((infrared_remote.status&0X0F)<14)
			{
				infrared_remote.status++;
			}
			else
			{
				infrared_remote.status&=~(1<<7);//清空引导标识
				infrared_remote.status&=0XF0;	//清空计数器	
			}						 	   	
		}							    
	}
	TIM_ClearITPendingBit(INFRARED_REMOTE_TIM,TIM_IT_Update);  //清除中断标志位 
} 

//定时器1输入捕获中断服务程序	 
void TIM1_CC_IRQHandler(void)
{ 		    	 
	if(TIM_GetITStatus(INFRARED_REMOTE_TIM,TIM_IT_CC1)==SET) //处理捕获(CC1IE)中断
	{	  
		if(INFRARED_REMOTE_PIN_IN)//上升沿捕获
		{
			TIM_OC1PolarityConfig(INFRARED_REMOTE_TIM,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			TIM_SetCounter(INFRARED_REMOTE_TIM,0);	   	//清空定时器值
			infrared_remote.status|=0X10;					//标记上升沿已经被捕获
		}
		else //下降沿捕获
		{
			infrared_remote.pulse_value=TIM_GetCapture1(TIM1);//读取CCR1也可以清CC1IF标志位
			TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0	设置为上升沿捕获
			if(infrared_remote.status&0X10)					//完成一次高电平捕获 
			{
 				if(infrared_remote.status&0X80)//接收到了引导码
				{
					
					if(infrared_remote.pulse_value>300&&infrared_remote.pulse_value<800)	//560为标准值,560us
					{
						infrared_remote.recive_data<<=1;	//左移一位.
						infrared_remote.recive_data|=0;	//接收到0	   
					}else if(infrared_remote.pulse_value>1400&&infrared_remote.pulse_value<1800)	//1680为标准值,1680us
					{
						infrared_remote.recive_data<<=1;	//左移一位.
						infrared_remote.recive_data|=1;	//接收到1
					}else if(infrared_remote.pulse_value>2200&&infrared_remote.pulse_value<2600)	//得到按键键值增加的信息 2500为标准值2.5ms
					{
						infrared_remote.key_count++; 		//按键次数增加1次
						infrared_remote.status&=0XF0;	//清空计时器		
					}
 				}else if(infrared_remote.pulse_value>4200&&infrared_remote.pulse_value<4700)		//4500为标准值4.5ms
				{
					infrared_remote.status|=1<<7;	//标记成功接收到了引导码
					infrared_remote.key_count=0;		//清除按键次数计数器
				}						 
			}
			infrared_remote.status&=~(1<<4);
		}				 		     	    					   
	}
	TIM_ClearITPendingBit(INFRARED_REMOTE_TIM,TIM_IT_CC1);  //清除中断标志位 
}

/*******************************ultrasonic***********************************/
//定时器5输入捕获中断服务程序	 
void TIM5_IRQHandler(void)
{ 		    	 
	if(TIM_GetITStatus(ULTRASONIC_TIM,TIM_IT_CC1)==SET) //处理捕获(CC1IE)中断
	{	  
		if(ULTRASONIC_PIN_IN)//上升沿捕获
		{
			TIM_OC1PolarityConfig(ULTRASONIC_TIM,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			TIM_SetCounter(ULTRASONIC_TIM,0);	   	//清空定时器值
			ultrasonic.rising_edge_flag  = true;
			//infrared_remote.status|=0X10;					//标记上升沿已经被捕获
		}
		else if(ultrasonic.rising_edge_flag)					//完成一次高电平捕获 //下降沿捕获
		{
			ultrasonic.pulse_value =TIM_GetCapture1(TIM5);//读取CCR1也可以清CC1IF标志位
			ultrasonic.receive_data_flag = true;
			ultrasonic.rising_edge_flag  = false;
		}				 		     	    					   
	}
	
	TIM_ClearITPendingBit(ULTRASONIC_TIM,TIM_IT_CC1|TIM_IT_Update);  //清除中断标志位 
}


