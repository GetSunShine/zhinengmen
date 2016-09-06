#ifndef __PWM_H
#define __PWM_H	
#include "sys.h" 
extern u8 num;

#define IN1_1 PCout(0)	 //outside motor in2
#define IN1_2 PCout(1)	 //outside motor in1
//TIM4 PWM PD12
#define IN2_1 PDout(2)	 //updown  motor in1
#define IN2_2 PDout(3)	 //updown  motor in2
//TIM13 PWM	PF8
#define IN3_1 PDout(4)	 //forward and back motor in2
#define IN3_2 PDout(5)	 //forward and back motor in1
//TIM14 PWM PF9

void TIM4_PWM_Init(u32 arr,u32 psc);
void TIM13_PWM_Init(u32 arr,u32 psc);
void TIM14_PWM_Init(u32 arr,u32 psc);
void PWM_Init(u32 arr,u32 psc);
void Motor_GPIO_Init(void); 

void PWM_Control1(u8 num,u16 value);
void PWM_Control2(u8 num,u16 value);
void PWM_Control3(u8 num,u16 value);
void Reset(void);
void All_Motor_Stop(void);

#endif