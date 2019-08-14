/***********************************************************************
 *
 *  Subsystem:   
 *  File:         
 *  Author:      ����¯
 *  Description: special function register
 *  Others: ���������ӿڣ�PA8-����ң����
 *
 *********************************************************************/

#ifndef __SFR_H
#define __SFR_H
#include "sys.h"

/*******************************system time***********************************/
#define SYSTEM_TIM TIM4

/*******************************led***********************************/
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	 
#define LED0_ON GPIO_ResetBits(GPIOF,GPIO_Pin_9)
#define LED0_OFF GPIO_SetBits(GPIOF,GPIO_Pin_9)
#define LED1_ON GPIO_ResetBits(GPIOF,GPIO_Pin_10)
#define LED1_OFF GPIO_SetBits(GPIOF,GPIO_Pin_10)

/*******************************timer***********************************/
#define MOTOR_TIM TIM3
#define STEERING_ENGINE_TIM TIM2
#define INFRARED_REMOTE_TIM TIM1
#define ULTRASONIC_TIM TIM5

/*******************************motor***********************************/
//�Ӻ�(����Ƕˣ���ǰ��,�������ң����ϵ��£�������
//ͨ������ռ�ձ��ƶ���ֹͣʱ��IN1,IN2����
#define MOTOR_LEFT_STBY_ON GPIO_SetBits(GPIOF,GPIO_Pin_11)
#define MOTOR_LEFT_STBY_OFF GPIO_ResetBits(GPIOF,GPIO_Pin_11)
#define MOTOR_LEFT_UP_ADVANCE do{GPIO_SetBits(GPIOB,GPIO_Pin_15);GPIO_ResetBits(GPIOB,GPIO_Pin_14);}while(0);
#define MOTOR_LEFT_UP_BACK do{GPIO_SetBits(GPIOB,GPIO_Pin_14);GPIO_ResetBits(GPIOB,GPIO_Pin_15);}while(0);
#define MOTOR_LEFT_UP_STOP do{GPIO_ResetBits(GPIOB,GPIO_Pin_14);GPIO_ResetBits(GPIOB,GPIO_Pin_15);}while(0);

#define MOTOR_LEFT_DOWN_ADVANCE do{GPIO_SetBits(GPIOF,GPIO_Pin_15);GPIO_ResetBits(GPIOF,GPIO_Pin_13);}while(0);
#define MOTOR_LEFT_DOWN_BACK do{GPIO_SetBits(GPIOF,GPIO_Pin_13);GPIO_ResetBits(GPIOF,GPIO_Pin_15);}while(0);
#define MOTOR_LEFT_DOWN_STOP do{GPIO_ResetBits(GPIOF,GPIO_Pin_13);GPIO_ResetBits(GPIOF,GPIO_Pin_15);}while(0);


#define MOTOR_RIGHT_STBY_ON GPIO_SetBits(GPIOE,GPIO_Pin_4)
#define MOTOR_RIGHT_STBY_OFF GPIO_ResetBits(GPIOE,GPIO_Pin_4)

#define MOTOR_RIGHT_UP_ADVANCE do{GPIO_SetBits(GPIOB,GPIO_Pin_5);GPIO_ResetBits(GPIOB,GPIO_Pin_7);}while(0);
#define MOTOR_RIGHT_UP_BACK do{GPIO_SetBits(GPIOB,GPIO_Pin_7);GPIO_ResetBits(GPIOB,GPIO_Pin_5);}while(0);
#define MOTOR_RIGHT_UP_STOP do{GPIO_ResetBits(GPIOB,GPIO_Pin_7);GPIO_ResetBits(GPIOB,GPIO_Pin_5);}while(0);

#define MOTOR_RIGHT_DOWN_ADVANCE do{GPIO_SetBits(GPIOE,GPIO_Pin_5);GPIO_ResetBits(GPIOE,GPIO_Pin_6);}while(0);
#define MOTOR_RIGHT_DOWN_BACK do{GPIO_SetBits(GPIOE,GPIO_Pin_6);GPIO_ResetBits(GPIOE,GPIO_Pin_5);}while(0);
#define MOTOR_RIGHT_DOWN_STOP do{GPIO_ResetBits(GPIOE,GPIO_Pin_5);GPIO_ResetBits(GPIOE,GPIO_Pin_6);}while(0);

/*******************************ultrasonic***********************************/
#define ULTRASONIC_PIN_IN PAin(0)	 //���������������
#define OPEN_RISING_EDGE GPIO_SetBits(GPIOF,GPIO_Pin_0)
#define OPEN_FALLING_EDGE GPIO_ResetBits(GPIOF,GPIO_Pin_0)

/*******************************infrared remote***********************************/
#define INFRARED_REMOTE_PIN_IN PAin(8)	 //�������������



#endif
