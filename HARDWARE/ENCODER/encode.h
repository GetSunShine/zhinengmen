#ifndef __ENCODER_H
#define __ENDOCER_H	

#include "sys.h"
#define  uchar unsigned char
#define  uint unsigned int

void encode_io_config(void);

/*******************�ϱ�����***************/
#define CS1   PEout(0)   //Ƭѡ
#define CLK1   PEout(1)   //ʱ�����
#define DATA1  PEin(2)    //��������

extern int motor1_circle_num;
extern int ire1_angle_flag;				//�Ƕȵ�λ��־
void Motor1_GetSSI(int circles);
void Motor1_Up_Angle(float angle);
void Motor1_Down_Angle(float angle);


/*******************�б�����***************/
#define CS2   PEout(3)   //Ƭѡ
#define CLK2   PEout(4)   //ʱ�����
#define DATA2  PEin(5)    //��������

extern int motor2_circle_num;				//Ȧ����λ��־
extern int ire2_angle_flag;				//�Ƕȵ�λ��־
void Motor2_GetSSI(int circles);
void Motor2_Up_Angle(float angle);
void Motor2_Down_Angle(float angle);
/*******************�±�����***************/
#define CS3   PEout(6)   //Ƭѡ
#define CLK3   PFout(0)   //ʱ�����
#define DATA3  PFin(1)    //��������

extern int motor3_circle_num;
extern int ire3_angle_flag;				//�Ƕȵ�λ��־
void Motor3_GetSSI(int circles);
void Motor3_Up_Angle(float angle);
void Motor3_Down_Angle(float angle);
#endif