#ifndef __IR_H
#define __IR_H	
#include "sys.h" 

#define RDATA PAin(8)	 //�������������

//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 0      		   

extern u8 RmtCnt;	//�������µĴ���

void Remote_Init(void);  
void TIM1_UP_TIM10_IRQHandler(void);
u8 Remote_Scan(void);


#define ECHO 	PAin(11)	 	 		   


extern u16 Ultra_Dval;
extern float length;
#endif 