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
 
 /*******************************system tim***********************************/
uint32_t sys_time;
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(SYSTEM_TIM,TIM_IT_Update)==SET) //溢出中断
	{
		sys_time++;
	}
	TIM_ClearITPendingBit(SYSTEM_TIM,TIM_IT_Update);  //清除中断标志位
}
