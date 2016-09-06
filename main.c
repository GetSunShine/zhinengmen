#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "time.h"
#include "adc.h"
#include "ir.h"
#include "pwm.h"
#include "encode.h"
#include "ultrasonic.h"

u8 key;
u8 ir=0;
u8 FLAG = 0;
u8 encoder_flag1 = 0;
u8 encoder_flag2 = 0;
u8 encoder_flag3 = 0;
void ir_control(void)
{
		
		num=Remote_Scan();
		switch(num)
		{
/********************outside  motor**********************/			
				case 0x68:											//1键
				{
						while(1)
						{								
								ir=Remote_Scan();
								if(ir == 0x62)					//上键
								{
										Motor1_GetSSI(2);
										PWM_Control1(1,1);
										delay_ms(100);
										FLAG = 1;												
								}
								else if(ir == 0xA8)		  //下键
								{
										Motor1_GetSSI(2);
										PWM_Control1(2,1);
										delay_ms(500);
										FLAG = 1;											
								}
								else if(ir == 0x2)			//暂停键
								{												
										PWM_Control1(0,1);
										FLAG = 0;
								}
								else if(ir == 0x52)				//返回键
								{
										PWM_Control1(0,1);
										FLAG = 0;
										break;
								}
								if(FLAG == 1)
									Motor1_GetSSI(2);
								#if 1
								if(motor1_circle_num >= 2)
								{
									motor1_circle_num = 0;								
									FLAG = 0;
									PWM_Control1(0,1);									
									printf("enter motor1 stop\r\n");									
									break;
								}
								#endif
						}
						break;
				}
/*********************updown motor***********************/
				case 0x98:											//2键
				{
					
						while(1)
						{
							
								ir=Remote_Scan();
								if(ir == 0x62)						//上键
								{
										Motor2_Down_Angle(90);
										PWM_Control2(1,300);
										delay_ms(100);
										FLAG = 1;
								}
								else if(ir == 0xA8)				//下键
								{
										Motor2_Up_Angle(90);
										//Motor2_GetSSI(2);
										PWM_Control2(2,200);
										delay_ms(100);
										FLAG = 2;
								}
								else if(ir == 0x2)					//暂停键
								{												
										PWM_Control2(0,1);
										FLAG = 0;
								}
								else if(ir == 0x52)				//返回键
								{									
										PWM_Control2(0,1);
										FLAG = 0;
										break;
								}										
								if(FLAG == 1)
									Motor2_Down_Angle(90);
								if(FLAG == 2)
									Motor2_Up_Angle(90);
								
								if(ire2_angle_flag == 1)
								{
									ire2_angle_flag = 0;								
									FLAG = 0;
									PWM_Control2(0,1);									
									printf("enter motor2 stop\r\n");									
									break;
								}
								#if 0
								if(motor2_circle_num >= 2)
								{
									motor2_circle_num = 0;								
									FLAG = 0;
									PWM_Control2(0,1);									
									printf("enter motor2 stop\r\n");									
									break;
								}
								#endif
						}
						break;
				}
/************************forward and back motor*************************/
				case 0xB0:											//3键
				{
						while(1)
						{
								ir=Remote_Scan();
								if(ir == 0x62)					//上键
								{
										Motor3_Down_Angle(90);
										PWM_Control3(1,200);
										delay_ms(500);
										FLAG = 1;			
								}
								else if(ir == 0xA8)			//下键
								{
										Motor3_Up_Angle(90);
										PWM_Control3(2,200);
										delay_ms(500);
										FLAG = 2;
								}
								else if(ir == 0x2)			//暂停
								{	
										PWM_Control3(0,1);
										FLAG = 0;
								}
								else if(ir == 0x52)			//返回键
								{
										PWM_Control3(0,1);
										FLAG = 0;
										break;
								}
								if(FLAG == 1)
									Motor3_Down_Angle(90);
								if(FLAG == 2)
									Motor3_Up_Angle(90);
								if(ire3_angle_flag == 1)
								{
									ire3_angle_flag = 0;								
									FLAG = 0;
									PWM_Control3(0,1);									
									printf("enter motor3 stop\r\n");									
									break;
								}
								#if 0
								if(motor3_circle_num >= 2)
								{
									motor3_circle_num = 0;								
									FLAG = 0;
									PWM_Control3(0,1);									
									printf("enter motor3 stop\r\n");									
									break;
								}
								#endif
						}
						break;
				}
				default :
					break;
		}
}
int main(void)
{ 
	u8 key;
	u8 t=0;	
	u16 highbit,lowbit,i;
	float distance;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);		  
	LED_Init();		      
	uart_init(115200);
	Remote_Init();
	encode_io_config();
	PWM_Init(500-1,84-1);		//84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.
	Motor_GPIO_Init();
	Ultra_Init();	
	KEY_Init();
	#if 0
	while(1)
	{
		ir_control();
		for(i=0;i<7;i++)
		{
				//printf("1\r\n");
				TRIG = 1;
				delay_us(20);
				TRIG = 0;
				//printf("2\r\n");
				length += (Ultra_Dval/58.0);			
				delay_ms(100);			
		}
			distance = length/7;
			//printf("3\r\n");
			printf("distance = %fcm\r\n",distance);
			
			if(distance <= 35)
			{
				PWM_Control2(2,200);
			}
			if(distance >=35)
			{
				PWM_Control2(0,1);
			}
		
			distance = 0.0;
			length = 0.0;
	}
#endif
	
	
#if 0
	while(1)
	{
		ir_control();
		//printf("123\r\n");
		//Motor1_GetSSI(2);
	}
#endif
/*********1.外板下降放平*************/
#if 1
	 
#if 1
	while(1)
	{
		ir_control();
		if(encoder_flag1 == 0)
		{
			Motor1_GetSSI(12);
			PWM_Control1(1,1);
			delay_ms(500);
			encoder_flag1 = 1;			
		}
		if(encoder_flag1 == 1)
				Motor1_GetSSI(12);

		if(motor1_circle_num >= 12)
		{
			motor1_circle_num = 0;								
			encoder_flag1 = 0;
			PWM_Control1(0,1);									
			printf("enter motor1 stop\r\n");	
			break;
		}
	}
	//while(1);
#endif
	
/*********2.外板水平推进，过枢纽停，放快递3s*************/
#if 1
	while(1)
	{
		if(encoder_flag3 == 0)
		{
			Motor3_GetSSI(2);
			PWM_Control3(2,200);
			PWM_Control1(2,230);			//钢丝拉紧
			delay_ms(500);
			encoder_flag3 = 1;			
		}
		if(encoder_flag3 == 1)
				Motor3_GetSSI(2);

		if(motor3_circle_num >= 2)
		{
			motor3_circle_num = 0;								
			encoder_flag3 = 0;
			PWM_Control3(0,1);	
			PWM_Control1(0,1);			
			printf("enter motor3 stop\r\n");
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(1000);
			break;
		}
	}	
	//while(1);
#endif
	
/*********3.检测高度，内板上升************/
#if 1
	while(1)
	{
		ir_control();
		for(i=0;i<7;i++)
		{
				//printf("1\r\n");
				TRIG = 1;
				delay_us(20);
				TRIG = 0;
				//printf("2\r\n");
				length += (Ultra_Dval/58.0);			
				delay_ms(100);			
		}
			distance = length/7;
			//printf("3\r\n");
			printf("distance = %fcm\r\n",distance);
			
			if(distance <= 35)
			{
				PWM_Control2(2,200);
			}
			if(distance >=35)
			{
				delay_ms(200);
				PWM_Control2(0,1);
				break;
			}
		
			distance = 0.0;
			length = 0.0;
	}
#endif	
	
/*********4.外板水平推进到最里面*************/
#if 1
	while(1)
	{
		if(encoder_flag3 == 0)
		{
			Motor3_GetSSI(4);
			PWM_Control3(2,200);
			PWM_Control1(2,270);				//钢丝拉紧
			delay_ms(500);
			encoder_flag3 = 1;			
		}
		if(encoder_flag3 == 1)
				Motor3_GetSSI(4);

		if(motor3_circle_num >= 4)
		{
			motor3_circle_num = 0;								
			encoder_flag3 = 0;
			PWM_Control3(0,1);	
			PWM_Control1(0,1);
			printf("enter motor3 stop\r\n");
			break;
		}
	}
	//while(1);	
#endif
	
/*********5.内板下降************/
#if 1
	while(1)
	{
		if(KEY0 == 0)
		{
			PWM_Control2(0,1);
			break;
		}
		else if(KEY0 == 1)
		{
			PWM_Control2(1,300);
		}
	}
	
#endif		

/*********6.外板水平推出到最外*************/
#if 1
	while(1)
	{
		if(encoder_flag3 == 0)
		{
			Motor3_GetSSI(6);
			PWM_Control3(1,200);
			PWM_Control1(1,350);		//钢丝放松
			delay_ms(500);
			encoder_flag3 = 1;			
		}
		if(encoder_flag3 == 1)
				Motor3_GetSSI(6);

		if(motor3_circle_num >= 6)
		{
			motor3_circle_num = 0;								
			encoder_flag3 = 0;
			PWM_Control3(0,1);	
			PWM_Control1(0,1);
			printf("enter motor3 stop\r\n");
			break;
		}
	}	
#endif
	
/*********7.外板上升复位*************/
#if 1
		while(1)
	{
			
		if(KEY1 == 0)
		{
			PWM_Control1(0,1);
			break;
		}
		else if(KEY1 == 1)
		{
			PWM_Control1(2,1);
		}
	}
	while(1);
#endif
#endif
}