#include "stdio.h"
#include "encode.h"
#include "string.h"
#include "usart.h"
#include "delay.h"
#include "math.h"

int TEST;
/***************1号电机**************/
/**圈数变量**/
int encoder1_circle_flag = 0;
int encoder1_circle_first_value;
int motor1_circle_num = 0;

/**角度变量**/
int encoder1_angle_flag = 0;
int encoder1_angle_first_value;
int ire1;
float ire1_angle;
int ire1_angle_flag = 0;

/**************2号电机***************/
/**圈数变量**/
int encoder2_circle_flag = 0;
int encoder2_circle_first_value;
int motor2_circle_num = 0;

/**角度变量**/
int encoder2_angle_flag = 0;
int encoder2_angle_first_value;
int ire2;
float ire2_angle;
int ire2_angle_flag = 0;

/**************3号电机**************/
/**圈数变量**/
int encoder3_circle_flag = 0;
int encoder3_circle_first_value;
int motor3_circle_num = 0;

/**角度变量**/
int encoder3_angle_flag = 0;
int encoder3_angle_first_value;
int ire3;
float ire3_angle;
int ire3_angle_flag = 0;

/**编码器123的IO配置**/
void encode_io_config(void)
{
/*******************编码器1	PIN初始化*********************/
	  GPIO_InitTypeDef GPIO_InitStructure;
	  /** PE1:CLK PE0:CS1  **/
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
/*******************编码器2	PIN初始化*********************/
	 
	  /** PE4:CLK PE3:CS2  **/ 
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
/*******************编码器3	PIN初始化*********************/
	 
	  /**  PE6:CS3  **/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;         
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
    GPIO_Init(GPIOE, &GPIO_InitStructure);
	  GPIO_SetBits(GPIOE,GPIO_Pin_6);
		
	  /**  PF0:CLK**/		
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
	
	uchar uState = 0;           //校验位数据 		 
 	uchar bCrc = 0;             //奇偶
	uint iSSI_1 = 0;              //当前数据
	 CS1= 0;                    //片选*****************		 
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
	
		 		TEST=DATA1;                    //延时
				iSSI_1 <<= 1;
				if(DATA1)
				{ 
						bCrc = !bCrc;             //奇偶校验位取反   
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
				if(DATA1)                      //数据为“1”就取反奇偶位
				{
						bCrc = !bCrc;             //奇偶校验位取反
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
	 
	 if(DATA1 == bCrc)	                  // 奇偶
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
								return ;						//最后一次不延时，立即停止
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
	
	uchar uState = 0;           //校验位数据 		 
 	uchar bCrc = 0;             //奇偶
	uint iSSI_1 = 0;              //当前数据
	 CS1= 0;                    //片选*****************		 
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
	
		 		TEST=DATA1;                    //延时
				iSSI_1 <<= 1;
				if(DATA1)
				{ 
						bCrc = !bCrc;             //奇偶校验位取反   
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
				if(DATA1)                      //数据为“1”就取反奇偶位
				{
						bCrc = !bCrc;             //奇偶校验位取反
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
	 
	 if(DATA1 == bCrc)	                  // 奇偶
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
	
	uchar uState = 0;           //校验位数据 		 
 	uchar bCrc = 0;             //奇偶
	uint iSSI_1 = 0;              //当前数据
	 CS1= 0;                    //片选*****************		 
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
	
		 		TEST=DATA1;                    //延时
				iSSI_1 <<= 1;
				if(DATA1)
				{ 
						bCrc = !bCrc;             //奇偶校验位取反   
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
				if(DATA1)                      //数据为“1”就取反奇偶位
				{
						bCrc = !bCrc;             //奇偶校验位取反
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
	 
	 if(DATA1 == bCrc)	                  // 奇偶
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
	
	uchar uState = 0;           //校验位数据 		 
 	uchar bCrc = 0;             //奇偶
	uint iSSI_2 = 0;              //当前数据
	 CS2= 0;                    //片选*****************		 
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
	
		 		TEST=DATA2;                    //延时
				iSSI_2 <<= 1;
				if(DATA2)
				{ 
						bCrc = !bCrc;             //奇偶校验位取反   
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
				if(DATA2)                      //数据为“1”就取反奇偶位
				{
						bCrc = !bCrc;             //奇偶校验位取反
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
	 
	 if(DATA2 == bCrc)	                  // 奇偶
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
								return ;						//最后一次不延时，立即停止
							}
							printf("motor2_circle_num = %d\r\n",motor2_circle_num);
							delay_ms(400);
					}
							
				}	
			}
	 CS2 = 1; 
}

/****板上升，编码器正转，值增大*******/
void Motor2_Up_Angle(float angle)
{
	uchar i = 0;	    
	
	uchar uState = 0;           //校验位数据 		 
 	uchar bCrc = 0;             //奇偶
	uint iSSI_2 = 0;              //当前数据
	 CS2= 0;                    //片选*****************		 
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
	
		 		TEST=DATA2;                    //延时
				iSSI_2 <<= 1;
				if(DATA2)
				{ 
						bCrc = !bCrc;             //奇偶校验位取反   
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
				if(DATA2)                      //数据为“1”就取反奇偶位
				{
						bCrc = !bCrc;             //奇偶校验位取反
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
	 
	 if(DATA2 == bCrc)	                  // 奇偶
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
/*****板下降，编码器反转，值减小*******/
void Motor2_Down_Angle(float angle)
{
	uchar i = 0;	    
	
	uchar uState = 0;           //校验位数据 		 
 	uchar bCrc = 0;             //奇偶
	uint iSSI_2 = 0;              //当前数据
	 CS2= 0;                    //片选*****************		 
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
	
		 		TEST=DATA2;                    //延时
				iSSI_2 <<= 1;
				if(DATA2)
				{ 
						bCrc = !bCrc;             //奇偶校验位取反   
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
				if(DATA2)                      //数据为“1”就取反奇偶位
				{
						bCrc = !bCrc;             //奇偶校验位取反
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
	 
	 if(DATA2 == bCrc)	                  // 奇偶
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
	
	uchar uState = 0;           //校验位数据 		 
 	uchar bCrc = 0;             //奇偶
	uint iSSI_3 = 0;              //当前数据
	 CS3= 0;                    //片选*****************		 
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
	
		 		TEST=DATA3;                    //延时
				iSSI_3 <<= 1;
				if(DATA3)
				{ 
						bCrc = !bCrc;             //奇偶校验位取反   
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
				if(DATA3)                      //数据为“1”就取反奇偶位
				{
						bCrc = !bCrc;             //奇偶校验位取反
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
	 
	 if(DATA3 == bCrc)	                  // 奇偶
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
								return ;						//最后一次不延时，立即停止
							}
							printf("motor3_circle_num = %d\r\n",motor3_circle_num);
							delay_ms(400);
					}
							
				}	
			}
	 CS3 = 1; 
}


/****板向内，编码器正转，值增大*******/
void Motor3_Up_Angle(float angle)
{
	uchar i = 0;	    
	
	uchar uState = 0;           //校验位数据 		 
 	uchar bCrc = 0;             //奇偶
	uint iSSI_3 = 0;              //当前数据
	 CS3= 0;                    //片选*****************		 
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
	
		 		TEST=DATA3;                    //延时
				iSSI_3 <<= 1;
				if(DATA3)
				{ 
						bCrc = !bCrc;             //奇偶校验位取反   
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
				if(DATA3)                      //数据为“1”就取反奇偶位
				{
						bCrc = !bCrc;             //奇偶校验位取反
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
	 
	 if(DATA3 == bCrc)	                  // 奇偶
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
/****板向外，编码器反转，值减小*******/
void Motor3_Down_Angle(float angle)
{
	uchar i = 0;	    
	
	uchar uState = 0;           //校验位数据 		 
 	uchar bCrc = 0;             //奇偶
	uint iSSI_3 = 0;              //当前数据
	 CS3= 0;                    //片选*****************		 
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
	
		 		TEST=DATA3;                    //延时
				iSSI_3 <<= 1;
				if(DATA3)
				{ 
						bCrc = !bCrc;             //奇偶校验位取反   
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
				if(DATA3)                      //数据为“1”就取反奇偶位
				{
						bCrc = !bCrc;             //奇偶校验位取反
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
	 
	 if(DATA3 == bCrc)	                  // 奇偶
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
