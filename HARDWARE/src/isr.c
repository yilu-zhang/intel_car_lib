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
