#ifndef __ENCODER_H
#define __ENDOCER_H	

#include "sys.h"
#define  uchar unsigned char
#define  uint unsigned int

void encode_io_config(void);

/*******************上编码器***************/
#define CS1   PEout(0)   //片选
#define CLK1   PEout(1)   //时钟输出
#define DATA1  PEin(2)    //数据输入

extern int motor1_circle_num;
extern int ire1_angle_flag;				//角度到位标志
void Motor1_GetSSI(int circles);
void Motor1_Up_Angle(float angle);
void Motor1_Down_Angle(float angle);


/*******************中编码器***************/
#define CS2   PEout(3)   //片选
#define CLK2   PEout(4)   //时钟输出
#define DATA2  PEin(5)    //数据输入

extern int motor2_circle_num;				//圈数到位标志
extern int ire2_angle_flag;				//角度到位标志
void Motor2_GetSSI(int circles);
void Motor2_Up_Angle(float angle);
void Motor2_Down_Angle(float angle);
/*******************下编码器***************/
#define CS3   PEout(6)   //片选
#define CLK3   PFout(0)   //时钟输出
#define DATA3  PFin(1)    //数据输入

extern int motor3_circle_num;
extern int ire3_angle_flag;				//角度到位标志
void Motor3_GetSSI(int circles);
void Motor3_Up_Angle(float angle);
void Motor3_Down_Angle(float angle);
#endif