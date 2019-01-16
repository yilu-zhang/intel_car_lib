/***********************************************************************
 *
 *  Subsystem:   
 *  File:         
 *  Author:      ’≈“Á¬Ø
 *  Description: special function register
 *  Others:         
 *
 *********************************************************************/

#ifndef __SFR_H
#define __SFR_H
#include "sys.h"

/*******************************led***********************************/
#define LED0_ON GPIO_ResetBits(GPIOF,GPIO_Pin_9)
#define LED0_OFF GPIO_SetBits(GPIOF,GPIO_Pin_9)
#define LED1_ON GPIO_ResetBits(GPIOF,GPIO_Pin_10)
#define LED1_OFF GPIO_SetBits(GPIOF,GPIO_Pin_10)

/*******************************motor***********************************/
#define MOTOR_LEFT_STBY_ON GPIO_SetBits(GPIOE,GPIO_Pin_4)
#define MOTOR_LEFT_STBY_OFF GPIO_ResetBits(GPIOE,GPIO_Pin_4)
#define MOTOR_LEFT_ADVANCE do{GPIO_SetBits(GPIOE,GPIO_Pin_6);GPIO_ResetBits(GPIOE,GPIO_Pin_5);\
							GPIO_SetBits(GPIOB,GPIO_Pin_5);GPIO_ResetBits(GPIOB,GPIO_Pin_7);}while(0);
#define MOTOR_LEFT_BACK do{GPIO_SetBits(GPIOE,GPIO_Pin_5);GPIO_ResetBits(GPIOE,GPIO_Pin_6);\
							GPIO_SetBits(GPIOB,GPIO_Pin_7);GPIO_ResetBits(GPIOB,GPIO_Pin_5);}while(0);

#define MOTOR_RIGHT_STBY_ON GPIO_SetBits(GPIOF,GPIO_Pin_11)
#define MOTOR_RIGHT_STBY_OFF GPIO_ResetBits(GPIOF,GPIO_Pin_11)
#define MOTOR_RIGHT_ADVANCE do{GPIO_SetBits(GPIOF,GPIO_Pin_15);GPIO_ResetBits(GPIOF,GPIO_Pin_13);\
							GPIO_SetBits(GPIOB,GPIO_Pin_15);GPIO_ResetBits(GPIOB,GPIO_Pin_14);}while(0);
#define MOTOR_RIGHT_BACK do{GPIO_SetBits(GPIOF,GPIO_Pin_13);GPIO_ResetBits(GPIOF,GPIO_Pin_15);\
							GPIO_SetBits(GPIOB,GPIO_Pin_14);GPIO_ResetBits(GPIOB,GPIO_Pin_15);}while(0);							
							

	
#endif
