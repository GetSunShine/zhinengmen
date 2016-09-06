#include "ultrasonic.h"
#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "led.h"


void Ultra_Init(void)    			  
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM1_ICInitStructure;  
 
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ�� 	 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��PORTBʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//TIM1ʱ��ʹ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;			//PB1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);				
	
	//GPIOA8  ���ù���,����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1); //GPIOA8����ΪTIM1
	
	
 	TIM_TimeBaseStructure.TIM_Prescaler=167;  ////Ԥ��Ƶ��,1M�ļ���Ƶ��,1us��1.	
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=10000;   //�趨�������Զ���װֵ ���10ms���  
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure); 
  	  
 	//��ʼ��TIM2���벶�����
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM1_ICInitStructure.TIM_ICFilter = 0x03;//IC1F=0003 8����ʱ��ʱ�������˲�
  TIM_ICInit(TIM1, &TIM1_ICInitStructure);//��ʼ����ʱ��2���벶��ͨ��
	 
 
	
	TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC4,ENABLE);//��������ж� ,����CC1IE�����ж�	
  TIM_Cmd(TIM1,ENABLE ); 	 	//ʹ�ܶ�ʱ��1
 
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//��ʼ��NVIC�Ĵ���
	
//	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�2
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//��ʼ��NVIC�Ĵ���
}

//void TIM1_UP_TIM10_IRQHandler(void)
//{
//		if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET) 		//����ж�
//		{
//		}
//		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);  //����жϱ�־λ 
//} 


//u16 Ultra_Dval;
//float length = 0.0;
//void TIM1_CC_IRQHandler(void)
//{ 		
//	if(TIM_GetITStatus(TIM1,TIM_IT_CC4)==SET)
//	{	  
//			//printf("zd\r\n");
//			if(ECHO)//�����ز���
//			{
//				//printf("ss\r\n");
//				TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
//				TIM_SetCounter(TIM1,0);				//��ն�ʱ��ֵ
//			}
//			else //�½��ز���
//			{
//				//printf("xj\r\n");
//				Ultra_Dval=TIM_GetCapture4(TIM1);//��ȡCCR1Ҳ������CC1IF��־λ
//				TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Rising); 							
//			}				 		     	    					   
//	}
//		TIM_ClearITPendingBit(TIM1,TIM_IT_CC4);	    
//}


































