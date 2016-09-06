#include "pwm.h"
#include "adc.h"
#include "delay.h"
#include "usart.h"
#include "ir.h"
//TIM14 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
u8 num=0;
void TIM4_PWM_Init(u32 arr,u32 psc)
{		 					 
		//�˲������ֶ��޸�IO������
		
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  		//TIM4ʱ��ʹ��    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTDʱ��	
		
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);  //GPIOD12����Ϊ��ʱ��4
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;          //GPIOD12
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
		GPIO_Init(GPIOD,&GPIO_InitStructure);               //��ʼ��PD12
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_Period=arr;     //�Զ���װ��ֵ
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		
		TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//��ʼ����ʱ��11
		
		//��ʼ��TIM14 Channel1 PWMģʽ
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
	 
		TIM_ARRPreloadConfig(TIM4,ENABLE);	//ARPEʹ�� 
		
		TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4		  
}  

//TIM14 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM13_PWM_Init(u32 arr,u32 psc)
{		 					 
		//�˲������ֶ��޸�IO������
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);  	//TIM13ʱ��ʹ��    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//ʹ��PORTFʱ��	
		
		GPIO_PinAFConfig(GPIOF,GPIO_PinSource8,GPIO_AF_TIM13);  //GPIOF8����Ϊ��ʱ��13
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOF8
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
		GPIO_Init(GPIOF,&GPIO_InitStructure);               //��ʼ��PF8
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_Period=arr;     //�Զ���װ��ֵ
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		
		TIM_TimeBaseInit(TIM13,&TIM_TimeBaseStructure);//��ʼ����ʱ��13
		
		//��ʼ��TIM14 Channel1 PWMģʽ	 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
		TIM_OC1Init(TIM13, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

		TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);  //ʹ��TIM13��CCR1�ϵ�Ԥװ�ؼĴ���
	 
		TIM_ARRPreloadConfig(TIM13,ENABLE);//ARPEʹ�� 
		
		TIM_Cmd(TIM13, ENABLE);  //ʹ��TIM13							  
}  	


//TIM14 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM14_PWM_Init(u32 arr,u32 psc)
{		 					 
		//�˲������ֶ��޸�IO������		
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM14ʱ��ʹ��    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//ʹ��PORTFʱ��	
		
		GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14);  //GPIOF9����Ϊ��ʱ��14
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOF9
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
		GPIO_Init(GPIOF,&GPIO_InitStructure);               //��ʼ��PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_Period=arr;     //�Զ���װ��ֵ
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		
		TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
		
		//��ʼ��TIM14 Channel1 PWMģʽ	 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
		TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

		TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
	 
		TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPEʹ�� 
		
		TIM_Cmd(TIM14, ENABLE);  //ʹ��TIM14							  
}  

void PWM_Init(u32 arr,u32 psc)
{
		TIM4_PWM_Init(arr,psc);
		TIM13_PWM_Init(arr,psc);
		TIM14_PWM_Init(arr,psc);
}


//��ʼ��Ϊ�����.��ʹ��ʱ��   
//���IO��ʼ��
void Motor_GPIO_Init(void)
{    	 
		GPIO_InitTypeDef  GPIO_InitStructure,GPIO_InitStructure1;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD, ENABLE);

		//GPIOF9,F10��ʼ������
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //��ͨ���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
		GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
		GPIO_SetBits( GPIOD,GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 );//���ø�
		//GPIOF9,F10��ʼ������
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //��ͨ���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��
		GPIO_SetBits( GPIOC,GPIO_Pin_0 | GPIO_Pin_1 );//���ø�
}


void PWM_Control1(u8 num,u16 value)
{
		if(num == 1)
		{
				IN1_1 = 1;									//����
				IN1_2 = 0;	
				TIM_SetCompare1(TIM4,value);	
		}
		else if(num == 2)								//����
		{
				IN1_1 = 0;
				IN1_2 = 1;	
				TIM_SetCompare1(TIM4,value);	
		}
		else if(num == 0)						
		{
				IN1_1 = 0;
				IN1_2 = 0;	
		}
}


void PWM_Control2(u8 num,u16 value)
{
		if(num == 1)								//���ϣ���ת
		{
				IN2_1 = 1;
				IN2_2 = 0;	
				TIM_SetCompare1(TIM13,value);	
		}
		else if(num == 2)						//���£���ת
		{
				IN2_1 = 0;
				IN2_2 = 1;
				TIM_SetCompare1(TIM13,value);	
		}
		else if(num == 0)					//ֹͣ
		{
				IN2_1 = 0;
				IN2_2 = 0;
		}
}

void PWM_Control3(u8 num,u16 value)
{
		if(num == 1)										//��ת��������
		{
				IN3_1 = 1;
				IN3_2 = 0;
				TIM_SetCompare1(TIM14,value);	
		}
		else if(num == 2)									//��ת����
		{
				IN3_1 = 0;
				IN3_2 = 1;
				TIM_SetCompare1(TIM14,value);	
		}
		else if(num == 0) 								//ֹͣ
		{
				IN3_1 = 0;
				IN3_2 = 0;	
		}
}


void Reset(void)
{
		u16 ADC_Value1 = 0;
		u16 ADC_Value2 = 0;
		float temp1;
		float temp2;
		u8 num1 = 2;    //����
		u8 num2 = 2;    //�½�
		u8 num3 = 2;    //����
	

		while(1)
		{
				ADC_Value2=Get_Adc_Average2(ADC_Channel_5,20);//��ȡͨ��5��ת��ֵ��20��ȡƽ��
				temp2=(float)ADC_Value2*(3.3/4096);           //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
				printf("ADC2: ");
				printf("%f\n",temp2);
				if(temp2 <= 0.4)
				{
						num2 = 0; 
				}
				if(temp2 >= 1.7)
				{
						num2 = 0;
						break;
				}	  
			//	PWM_Control2(num2,1);      
		}
}

void All_Motor_Stop(void)
{
	num=Remote_Scan();
	if(num == 0x38)								//8��
	{
			while(1)
			{
					PWM_Control1(0,1); 
					PWM_Control2(0,1); 
					PWM_Control3(0,1); 
					ir_control();
			}
	}
	
	
}






