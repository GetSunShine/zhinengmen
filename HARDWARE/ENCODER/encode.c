#include "stdio.h"
#include "encode.h"
#include "string.h"
#include "usart.h"
#include "delay.h"
#include "math.h"

int TEST;
/***************1�ŵ��**************/
/**Ȧ������**/
int encoder1_circle_flag = 0;
int encoder1_circle_first_value;
int motor1_circle_num = 0;

/**�Ƕȱ���**/
int encoder1_angle_flag = 0;
int encoder1_angle_first_value;
int ire1;
float ire1_angle;
int ire1_angle_flag = 0;

/**************2�ŵ��***************/
/**Ȧ������**/
int encoder2_circle_flag = 0;
int encoder2_circle_first_value;
int motor2_circle_num = 0;

/**�Ƕȱ���**/
int encoder2_angle_flag = 0;
int encoder2_angle_first_value;
int ire2;
float ire2_angle;
int ire2_angle_flag = 0;

/**************3�ŵ��**************/
/**Ȧ������**/
int encoder3_circle_flag = 0;
int encoder3_circle_first_value;
int motor3_circle_num = 0;

/**�Ƕȱ���**/
int encoder3_angle_flag = 0;
int encoder3_angle_first_value;
int ire3;
float ire3_angle;
int ire3_angle_flag = 0;

/**������123��IO����**/
void encode_io_config(void)
{
/*******************������1	PIN��ʼ��*********************/
	  GPIO_InitTypeDef GPIO_InitStructure;
	  /** PE1:CLK�p PE0:CS1  **/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;         
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;     
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;           
    GPIO_Init(GPIOE, &GPIO_InitStructure);
	  GPIO_SetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_1);
	  
	  /** PE2:DATA **/
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                  
    GPIO_Init(GPIOE, &GPIO_InitStructure);               
	  GPIO_SetBits(GPIOE,GPIO_Pin_2);
	  printf("Encode1_io_config ok ......\r\n");
/*******************������2	PIN��ʼ��*********************/
	 
	  /** PE4:CLK�p PE3:CS2  **/ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3| GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;         
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          
    GPIO_Init(GPIOE, &GPIO_InitStructure);
	  GPIO_SetBits(GPIOE,GPIO_Pin_3 | GPIO_Pin_4);
	  
	  /** PE5:DATA **/
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                  
    GPIO_Init(GPIOE, &GPIO_InitStructure);               
	  GPIO_SetBits(GPIOE,GPIO_Pin_5);
	  printf("Encode2_io_config ok ......\r\n");
/*******************������3	PIN��ʼ��*********************/
	 
	  /**  PE6:CS3  **/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;         
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
    GPIO_Init(GPIOE, &GPIO_InitStructure);
	  GPIO_SetBits(GPIOE,GPIO_Pin_6);
		
	  /**  PF0:CLK�p**/		
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;           
    GPIO_Init(GPIOF, &GPIO_InitStructure);               
	  GPIO_SetBits(GPIOF,GPIO_Pin_0);		
		
		
	  /** PF1:DATA **/
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;            
    GPIO_Init(GPIOF, &GPIO_InitStructure);               
	  GPIO_SetBits(GPIOF,GPIO_Pin_1);
	  printf("Encode3_io_config ok ......\r\n");
	
}


void Motor1_GetSSI(int circles)
{
	uchar i = 0;	    
	
	uchar uState = 0;           //У��λ���� 		 
 	uchar bCrc = 0;             //��ż
	uint iSSI_1 = 0;              //��ǰ����
	 CS1= 0;                    //Ƭѡ*****************		 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 CLK1 = 0;                    
   __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
   CLK1 = 1; 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 for(i = 0; i < 10;i++)
	 {
				CLK1 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		 		TEST=DATA1;                    //��ʱ
				iSSI_1 <<= 1;
				if(DATA1)
				{ 
						bCrc = !bCrc;             //��żУ��λȡ��   
						iSSI_1 |= 1;
				}
				CLK2 = 1;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();__nop();__nop();__nop();__nop();__nop();
	 
   
	 for(i = 0; i < 5;i++)
	 {
				CLK1 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		    TEST=DATA1;
				uState <<= 1;
				if(DATA1)                      //����Ϊ��1����ȡ����żλ
				{
						bCrc = !bCrc;             //��żУ��λȡ��
						uState |= 1;
				}
				CLK1 = 1;
        __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();	__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 
	 if(DATA1 == bCrc)	                  // ��ż
	 {	
			CS1= 1;   
		  if((uState == 16)||(uState == 19))         // 16: 10000   19:10011
			{  
					printf("issi1 = %d\r\n",iSSI_1);
					
				if(encoder1_circle_flag == 0)
					{
							encoder1_circle_flag++;
							encoder1_circle_first_value = iSSI_1;
						
					}
					
					if(abs(encoder1_circle_first_value-iSSI_1)<2)
					{
							motor1_circle_num++;
							if(motor1_circle_num == 1 && encoder1_circle_flag == 1)
							{
								encoder1_circle_flag++;
								motor1_circle_num = 0;
							}
							if(motor1_circle_num == circles)
							{
								encoder1_circle_flag = 0;
								printf("motor1_circle_num = %d\r\n",motor1_circle_num);
								return ;						//���һ�β���ʱ������ֹͣ
							}
							printf("motor1_circle_num = %d\r\n",motor1_circle_num);
							delay_ms(400);
					}
							
				}	
			}
	 CS1 = 1; 
}

void Motor1_Up_Angle(float angle)
{
	uchar i = 0;	    
	
	uchar uState = 0;           //У��λ���� 		 
 	uchar bCrc = 0;             //��ż
	uint iSSI_1 = 0;              //��ǰ����
	 CS1= 0;                    //Ƭѡ*****************		 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 CLK1 = 0;                    
   __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
   CLK1 = 1; 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 for(i = 0; i < 10;i++)
	 {
				CLK1 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		 		TEST=DATA1;                    //��ʱ
				iSSI_1 <<= 1;
				if(DATA1)
				{ 
						bCrc = !bCrc;             //��żУ��λȡ��   
						iSSI_1 |= 1;
				}
				CLK1 = 1;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();__nop();__nop();__nop();__nop();__nop();
	 
   
	 for(i = 0; i < 5;i++)
	 {
				CLK1 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		    TEST=DATA1;
				uState <<= 1;
				if(DATA1)                      //����Ϊ��1����ȡ����żλ
				{
						bCrc = !bCrc;             //��żУ��λȡ��
						uState |= 1;
				}
				CLK1 = 1;
        __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();	__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 
	 if(DATA1 == bCrc)	                  // ��ż
	 {	
			CS1= 1;   
		  if((uState == 16)||(uState == 19))         // 16: 10000   19:10011
			{  
					
				
					printf("issi1 = %d\r\n",iSSI_1);
					
					ire1_angle = ((angle/360) * 1024);
				
					if(encoder1_angle_flag == 0)
						{
								encoder1_angle_flag++;
								encoder1_angle_first_value = iSSI_1;
								printf("encoder1_angle_first_value = %d\r\n",encoder1_angle_first_value);
							
						}
					if(iSSI_1 > encoder2_angle_first_value)
					{
						ire1 = iSSI_1 - encoder1_angle_first_value;
					}
					if(iSSI_1 < encoder1_angle_first_value)
					{
						ire1 = 1024 - encoder2_angle_first_value + iSSI_1;
					}
					if(ire1 >= ire1_angle)
					{
						ire1_angle_flag = 1;
						encoder1_angle_flag = 0;
						ire1 = 0;
						printf("issi1_end = %d\r\n",iSSI_1);
						printf("ire1 = %d\r\n",ire1);
					}
			
				}	
			}
	 CS1 = 1; 
	 
}

void Motor1_Down_Angle(float angle)
{
	uchar i = 0;	    
	
	uchar uState = 0;           //У��λ���� 		 
 	uchar bCrc = 0;             //��ż
	uint iSSI_1 = 0;              //��ǰ����
	 CS1= 0;                    //Ƭѡ*****************		 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 CLK1 = 0;                    
   __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
   CLK1 = 1; 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 for(i = 0; i < 10;i++)
	 {
				CLK1 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		 		TEST=DATA1;                    //��ʱ
				iSSI_1 <<= 1;
				if(DATA1)
				{ 
						bCrc = !bCrc;             //��żУ��λȡ��   
						iSSI_1 |= 1;
				}
				CLK1 = 1;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();__nop();__nop();__nop();__nop();__nop();
	 
   
	 for(i = 0; i < 5;i++)
	 {
				CLK1 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		    TEST=DATA1;
				uState <<= 1;
				if(DATA1)                      //����Ϊ��1����ȡ����żλ
				{
						bCrc = !bCrc;             //��żУ��λȡ��
						uState |= 1;
				}
				CLK1 = 1;
        __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();	__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 
	 if(DATA1 == bCrc)	                  // ��ż
	 {	
			CS2= 1;   
		  if((uState == 16)||(uState == 19))         // 16: 10000   19:10011
			{  
					
				
					printf("issi1 = %d\r\n",iSSI_1);
					
					ire1_angle = ((angle/360) * 1024);
					if(encoder1_angle_flag == 0)
						{
								encoder1_angle_flag++;
								encoder1_angle_first_value = iSSI_1;
								printf("encoder1_angle_first_value = %d\r\n",encoder1_angle_first_value);
							
						}
					if(iSSI_1 < encoder1_angle_first_value)
					{
						ire1 = encoder1_angle_first_value - iSSI_1;
					}
					if(iSSI_1 > encoder1_angle_first_value)
					{
						ire1 = 1024 - iSSI_1 + encoder1_angle_first_value;
					}
					if(ire1 >= ire1_angle)
					{
						ire1_angle_flag = 1;
						encoder1_angle_flag = 0;
						ire1 = 0;
						printf("issi1_end = %d\r\n",iSSI_1);
						printf("ire1 = %d\r\n",ire1);
					}
			
				}	
			}
	 CS1 = 1; 
	 
}



void Motor2_GetSSI(int circles)
{
	uchar i = 0;	    
	
	uchar uState = 0;           //У��λ���� 		 
 	uchar bCrc = 0;             //��ż
	uint iSSI_2 = 0;              //��ǰ����
	 CS2= 0;                    //Ƭѡ*****************		 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 CLK2 = 0;                    
   __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
   CLK2 = 1; 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 for(i = 0; i < 10;i++)
	 {
				CLK2 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		 		TEST=DATA2;                    //��ʱ
				iSSI_2 <<= 1;
				if(DATA2)
				{ 
						bCrc = !bCrc;             //��żУ��λȡ��   
						iSSI_2 |= 1;
				}
				CLK2 = 1;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();__nop();__nop();__nop();__nop();__nop();
	 
   
	 for(i = 0; i < 5;i++)
	 {
				CLK2 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		    TEST=DATA2;
				uState <<= 1;
				if(DATA2)                      //����Ϊ��1����ȡ����żλ
				{
						bCrc = !bCrc;             //��żУ��λȡ��
						uState |= 1;
				}
				CLK2 = 1;
        __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();	__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 
	 if(DATA2 == bCrc)	                  // ��ż
	 {	
			CS2= 1;   
		  if((uState == 16)||(uState == 19))         // 16: 10000   19:10011
			{  
					printf("issi2 = %d\r\n",iSSI_2);
					
				if(encoder2_circle_flag == 0)
					{
							encoder2_circle_flag++;
							encoder2_circle_first_value = iSSI_2;
						
					}
					
					if(abs(encoder2_circle_first_value-iSSI_2)<2)
					{
							motor2_circle_num++;
							if(motor2_circle_num == 1 && encoder2_circle_flag == 1)
							{
								encoder2_circle_flag++;
								motor2_circle_num = 0;
							}
							if(motor2_circle_num == circles)
							{
								encoder2_circle_flag = 0;
								printf("motor2_circle_num = %d\r\n",motor2_circle_num);
								return ;						//���һ�β���ʱ������ֹͣ
							}
							printf("motor2_circle_num = %d\r\n",motor2_circle_num);
							delay_ms(400);
					}
							
				}	
			}
	 CS2 = 1; 
}

/****����������������ת��ֵ����*******/
void Motor2_Up_Angle(float angle)
{
	uchar i = 0;	    
	
	uchar uState = 0;           //У��λ���� 		 
 	uchar bCrc = 0;             //��ż
	uint iSSI_2 = 0;              //��ǰ����
	 CS2= 0;                    //Ƭѡ*****************		 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 CLK2 = 0;                    
   __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
   CLK2 = 1; 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 for(i = 0; i < 10;i++)
	 {
				CLK2 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		 		TEST=DATA2;                    //��ʱ
				iSSI_2 <<= 1;
				if(DATA2)
				{ 
						bCrc = !bCrc;             //��żУ��λȡ��   
						iSSI_2 |= 1;
				}
				CLK2 = 1;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();__nop();__nop();__nop();__nop();__nop();
	 
   
	 for(i = 0; i < 5;i++)
	 {
				CLK2 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		    TEST=DATA2;
				uState <<= 1;
				if(DATA2)                      //����Ϊ��1����ȡ����żλ
				{
						bCrc = !bCrc;             //��żУ��λȡ��
						uState |= 1;
				}
				CLK2 = 1;
        __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();	__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 
	 if(DATA2 == bCrc)	                  // ��ż
	 {	
			CS2= 1;   
		  if((uState == 16)||(uState == 19))         // 16: 10000   19:10011
			{  
					
				
					printf("issi2 = %d\r\n",iSSI_2);
					
					ire2_angle = ((angle/360) * 1024);
				
					if(encoder2_angle_flag == 0)
						{
								encoder2_angle_flag++;
								encoder2_angle_first_value = iSSI_2;
								printf("encoder2_angle_first_value = %d\r\n",encoder2_angle_first_value);
							
						}
					if(iSSI_2 > encoder2_angle_first_value)
					{
						ire2 = iSSI_2 - encoder2_angle_first_value;
					}
					if(iSSI_2 < encoder2_angle_first_value)
					{
						ire2 = 1024 - encoder2_angle_first_value + iSSI_2;
					}
					if(ire2 >= ire2_angle)
					{
						ire2_angle_flag = 1;
						encoder2_angle_flag = 0;
						printf("ire2 = %d\r\n",ire2);
						ire2 = 0;
						printf("issi2_end = %d\r\n",iSSI_2);
						
					}
			
				}	
			}
	 CS2 = 1; 
	 
}
/*****���½�����������ת��ֵ��С*******/
void Motor2_Down_Angle(float angle)
{
	uchar i = 0;	    
	
	uchar uState = 0;           //У��λ���� 		 
 	uchar bCrc = 0;             //��ż
	uint iSSI_2 = 0;              //��ǰ����
	 CS2= 0;                    //Ƭѡ*****************		 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 CLK2 = 0;                    
   __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
   CLK2 = 1; 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 for(i = 0; i < 10;i++)
	 {
				CLK2 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		 		TEST=DATA2;                    //��ʱ
				iSSI_2 <<= 1;
				if(DATA2)
				{ 
						bCrc = !bCrc;             //��żУ��λȡ��   
						iSSI_2 |= 1;
				}
				CLK2 = 1;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();__nop();__nop();__nop();__nop();__nop();
	 
   
	 for(i = 0; i < 5;i++)
	 {
				CLK2 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		    TEST=DATA2;
				uState <<= 1;
				if(DATA2)                      //����Ϊ��1����ȡ����żλ
				{
						bCrc = !bCrc;             //��żУ��λȡ��
						uState |= 1;
				}
				CLK2 = 1;
        __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();	__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 
	 if(DATA2 == bCrc)	                  // ��ż
	 {	
			CS2= 1;   
		  if((uState == 16)||(uState == 19))         // 16: 10000   19:10011
			{  
					
				
					printf("issi2 = %d\r\n",iSSI_2);
					
					ire2_angle = ((angle/360) * 1024);
					if(encoder2_angle_flag == 0)
						{
								encoder2_angle_flag++;
								encoder2_angle_first_value = iSSI_2;
								printf("encoder2_angle_first_value = %d\r\n",encoder2_angle_first_value);
							
						}
					if(iSSI_2 < encoder2_angle_first_value)
					{
						ire2 = encoder2_angle_first_value - iSSI_2;
					}
					if(iSSI_2 > encoder2_angle_first_value)
					{
						ire2 = 1024 - iSSI_2 + encoder2_angle_first_value;
					}
					if(ire2 >= ire2_angle)
					{
						ire2_angle_flag = 1;
						encoder2_angle_flag = 0;
						ire2 = 0;
						printf("issi2_end = %d\r\n",iSSI_2);
						printf("ire2 = %d\r\n",ire2);
					}
			
				}	
			}
	 CS2 = 1; 
	 
}

void Motor3_GetSSI(int circles)
{
	uchar i = 0;	    
	
	uchar uState = 0;           //У��λ���� 		 
 	uchar bCrc = 0;             //��ż
	uint iSSI_3 = 0;              //��ǰ����
	 CS3= 0;                    //Ƭѡ*****************		 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 CLK3 = 0;                    
   __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
   CLK3 = 1; 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 for(i = 0; i < 10;i++)
	 {
				CLK3 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		 		TEST=DATA3;                    //��ʱ
				iSSI_3 <<= 1;
				if(DATA3)
				{ 
						bCrc = !bCrc;             //��żУ��λȡ��   
						iSSI_3 |= 1;
				}
				CLK3 = 1;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();__nop();__nop();__nop();__nop();__nop();
	 
   
	 for(i = 0; i < 5;i++)
	 {
				CLK3 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		    TEST=DATA3;
				uState <<= 1;
				if(DATA3)                      //����Ϊ��1����ȡ����żλ
				{
						bCrc = !bCrc;             //��żУ��λȡ��
						uState |= 1;
				}
				CLK3 = 1;
        __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();	__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 
	 if(DATA3 == bCrc)	                  // ��ż
	 {	
			CS3 = 1;   
		  if((uState == 16)||(uState == 19))         // 16: 10000   19:10011
			{  
					printf("issi3 = %d\r\n",iSSI_3);
					
				if(encoder3_circle_flag == 0)
					{
							encoder3_circle_flag++;
							encoder3_circle_first_value = iSSI_3;
						
					}
					
					if(abs(encoder3_circle_first_value-iSSI_3)<2)
					{
							motor3_circle_num++;
							if(motor3_circle_num == 1 && encoder3_circle_flag == 1)
							{
								encoder3_circle_flag++;
								motor3_circle_num = 0;
							}
							if(motor3_circle_num == circles)
							{
								encoder3_circle_flag = 0;
								printf("motor3_circle_num = %d\r\n",motor3_circle_num);
								return ;						//���һ�β���ʱ������ֹͣ
							}
							printf("motor3_circle_num = %d\r\n",motor3_circle_num);
							delay_ms(400);
					}
							
				}	
			}
	 CS3 = 1; 
}


/****�����ڣ���������ת��ֵ����*******/
void Motor3_Up_Angle(float angle)
{
	uchar i = 0;	    
	
	uchar uState = 0;           //У��λ���� 		 
 	uchar bCrc = 0;             //��ż
	uint iSSI_3 = 0;              //��ǰ����
	 CS3= 0;                    //Ƭѡ*****************		 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 CLK3 = 0;                    
   __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
   CLK3 = 1; 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 for(i = 0; i < 10;i++)
	 {
				CLK3 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		 		TEST=DATA3;                    //��ʱ
				iSSI_3 <<= 1;
				if(DATA3)
				{ 
						bCrc = !bCrc;             //��żУ��λȡ��   
						iSSI_3 |= 1;
				}
				CLK3 = 1;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();__nop();__nop();__nop();__nop();__nop();
	 
   
	 for(i = 0; i < 5;i++)
	 {
				CLK3 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		    TEST=DATA3;
				uState <<= 1;
				if(DATA3)                      //����Ϊ��1����ȡ����żλ
				{
						bCrc = !bCrc;             //��żУ��λȡ��
						uState |= 1;
				}
				CLK3 = 1;
        __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();	__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 
	 if(DATA3 == bCrc)	                  // ��ż
	 {	
			CS3= 1;   
		  if((uState == 16)||(uState == 19))         // 16: 10000   19:10011
			{  
					
				
					printf("issi3 = %d\r\n",iSSI_3);
					
					ire3_angle = ((angle/360) * 1024);
				
					if(encoder3_angle_flag == 0)
						{
								encoder3_angle_flag++;
								encoder3_angle_first_value = iSSI_3;
								printf("encoder3_angle_first_value = %d\r\n",encoder3_angle_first_value);
							
						}
					if(iSSI_3 > encoder3_angle_first_value)
					{
						ire3 = iSSI_3 - encoder3_angle_first_value;
					}
					if(iSSI_3 < encoder3_angle_first_value)
					{
						ire3 = 1024 - encoder3_angle_first_value + iSSI_3;
					}
					if(ire3 >= ire3_angle)
					{
						ire3_angle_flag = 1;
						encoder3_angle_flag = 0;
						ire3 = 0;
						printf("issi3_end = %d\r\n",iSSI_3);
						printf("ire3 = %d\r\n",ire3);
					}			
				}	
			}
	 CS3 = 1; 
	 
}
/****�����⣬��������ת��ֵ��С*******/
void Motor3_Down_Angle(float angle)
{
	uchar i = 0;	    
	
	uchar uState = 0;           //У��λ���� 		 
 	uchar bCrc = 0;             //��ż
	uint iSSI_3 = 0;              //��ǰ����
	 CS3= 0;                    //Ƭѡ*****************		 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 CLK3 = 0;                    
   __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
   CLK3 = 1; 
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 for(i = 0; i < 10;i++)
	 {
				CLK3 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		 		TEST=DATA3;                    //��ʱ
				iSSI_3 <<= 1;
				if(DATA3)
				{ 
						bCrc = !bCrc;             //��żУ��λȡ��   
						iSSI_3 |= 1;
				}
				CLK3 = 1;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();__nop();__nop();__nop();__nop();__nop();
	 
   
	 for(i = 0; i < 5;i++)
	 {
				CLK3 = 0;
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
		    TEST=DATA3;
				uState <<= 1;
				if(DATA3)                      //����Ϊ��1����ȡ����żλ
				{
						bCrc = !bCrc;             //��żУ��λȡ��
						uState |= 1;
				}
				CLK3 = 1;
        __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();        
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
	 }
	 __nop();	__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	 
	 if(DATA3 == bCrc)	                  // ��ż
	 {	
			CS3= 1;   
		  if((uState == 16)||(uState == 19))         // 16: 10000   19:10011
			{  
					
				
					printf("issi3 = %d\r\n",iSSI_3);
					
					ire3_angle = ((angle/360) * 1024);
					if(encoder3_angle_flag == 0)
						{
								encoder3_angle_flag++;
								encoder3_angle_first_value = iSSI_3;
								printf("encoder3_angle_first_value = %d\r\n",encoder3_angle_first_value);							
						}
					if(iSSI_3 < encoder3_angle_first_value)
					{
						ire3 = encoder3_angle_first_value - iSSI_3;
					}
					if(iSSI_3 > encoder3_angle_first_value)
					{
						ire3 = 1024 - iSSI_3 + encoder3_angle_first_value;
					}
					if(ire3 >= ire3_angle)
					{
						ire3_angle_flag = 1;
						encoder3_angle_flag = 0;
						printf("ire3 = %d\r\n",ire3);
						ire3 = 0;
						printf("issi3_end = %d\r\n",iSSI_3);
						
					}
			
				}	
			}
	 CS3 = 1; 
	 
}
