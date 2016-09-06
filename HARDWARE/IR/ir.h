#ifndef __IR_H
#define __IR_H	
#include "sys.h" 

#define RDATA PAin(8)	 //红外数据输入脚

//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0
#define REMOTE_ID 0      		   

extern u8 RmtCnt;	//按键按下的次数

void Remote_Init(void);  
void TIM1_UP_TIM10_IRQHandler(void);
u8 Remote_Scan(void);


#define ECHO 	PAin(11)	 	 		   


extern u16 Ultra_Dval;
extern float length;
#endif 