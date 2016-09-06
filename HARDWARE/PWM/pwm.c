#include "pwm.h"
#include "adc.h"
#include "delay.h"
#include "usart.h"
#include "ir.h"
//TIM14 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
u8 num=0;
void TIM4_PWM_Init(u32 arr,u32 psc)
{		 					 
		//此部分需手动修改IO口设置
		
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  		//TIM4时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//使能PORTD时钟	
		
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);  //GPIOD12复用为定时器4
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;          //GPIOD12
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
		GPIO_Init(GPIOD,&GPIO_InitStructure);               //初始化PD12
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
		TIM_TimeBaseStructure.TIM_Period=arr;     //自动重装载值
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		
		TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//初始化定时器11
		
		//初始化TIM14 Channel1 PWM模式
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
	 
		TIM_ARRPreloadConfig(TIM4,ENABLE);	//ARPE使能 
		
		TIM_Cmd(TIM4, ENABLE);  //使能TIM4		  
}  

//TIM14 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM13_PWM_Init(u32 arr,u32 psc)
{		 					 
		//此部分需手动修改IO口设置
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);  	//TIM13时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//使能PORTF时钟	
		
		GPIO_PinAFConfig(GPIOF,GPIO_PinSource8,GPIO_AF_TIM13);  //GPIOF8复用为定时器13
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOF8
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
		GPIO_Init(GPIOF,&GPIO_InitStructure);               //初始化PF8
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
		TIM_TimeBaseStructure.TIM_Period=arr;     //自动重装载值
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		
		TIM_TimeBaseInit(TIM13,&TIM_TimeBaseStructure);//初始化定时器13
		
		//初始化TIM14 Channel1 PWM模式	 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
		TIM_OC1Init(TIM13, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

		TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);  //使能TIM13在CCR1上的预装载寄存器
	 
		TIM_ARRPreloadConfig(TIM13,ENABLE);//ARPE使能 
		
		TIM_Cmd(TIM13, ENABLE);  //使能TIM13							  
}  	


//TIM14 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM14_PWM_Init(u32 arr,u32 psc)
{		 					 
		//此部分需手动修改IO口设置		
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM14时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//使能PORTF时钟	
		
		GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14);  //GPIOF9复用为定时器14
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOF9
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
		GPIO_Init(GPIOF,&GPIO_InitStructure);               //初始化PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
		TIM_TimeBaseStructure.TIM_Period=arr;     //自动重装载值
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		
		TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);//初始化定时器14
		
		//初始化TIM14 Channel1 PWM模式	 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
		TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

		TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
	 
		TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPE使能 
		
		TIM_Cmd(TIM14, ENABLE);  //使能TIM14							  
}  

void PWM_Init(u32 arr,u32 psc)
{
		TIM4_PWM_Init(arr,psc);
		TIM13_PWM_Init(arr,psc);
		TIM14_PWM_Init(arr,psc);
}


//初始化为输出口.并使能时钟   
//电机IO初始化
void Motor_GPIO_Init(void)
{    	 
		GPIO_InitTypeDef  GPIO_InitStructure,GPIO_InitStructure1;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD, ENABLE);

		//GPIOF9,F10初始化设置
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //普通输出模式
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
		GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
		GPIO_SetBits( GPIOD,GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 );//设置高
		//GPIOF9,F10初始化设置
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //普通输出模式
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
		GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化
		GPIO_SetBits( GPIOC,GPIO_Pin_0 | GPIO_Pin_1 );//设置高
}


void PWM_Control1(u8 num,u16 value)
{
		if(num == 1)
		{
				IN1_1 = 1;									//向上
				IN1_2 = 0;	
				TIM_SetCompare1(TIM4,value);	
		}
		else if(num == 2)								//向下
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
		if(num == 1)								//向上，正转
		{
				IN2_1 = 1;
				IN2_2 = 0;	
				TIM_SetCompare1(TIM13,value);	
		}
		else if(num == 2)						//向下，反转
		{
				IN2_1 = 0;
				IN2_2 = 1;
				TIM_SetCompare1(TIM13,value);	
		}
		else if(num == 0)					//停止
		{
				IN2_1 = 0;
				IN2_2 = 0;
		}
}

void PWM_Control3(u8 num,u16 value)
{
		if(num == 1)										//反转，向里走
		{
				IN3_1 = 1;
				IN3_2 = 0;
				TIM_SetCompare1(TIM14,value);	
		}
		else if(num == 2)									//正转向外
		{
				IN3_1 = 0;
				IN3_2 = 1;
				TIM_SetCompare1(TIM14,value);	
		}
		else if(num == 0) 								//停止
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
		u8 num1 = 2;    //放下
		u8 num2 = 2;    //下降
		u8 num3 = 2;    //后退
	

		while(1)
		{
				ADC_Value2=Get_Adc_Average2(ADC_Channel_5,20);//获取通道5的转换值，20次取平均
				temp2=(float)ADC_Value2*(3.3/4096);           //获取计算后的带小数的实际电压值，比如3.1111
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
	if(num == 0x38)								//8键
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






