/*******************************************************************************
// file				:	DesireAngles.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	：8.00M
// IDE				: Keil uVision4
// date				：2014.2.28
*******************************************************************************/

#include "DesireAngles.h"


#define uint unsigned int
#define uchar unsigned char 

#define LIMIT_ANGLE 30.0f		//最大姿态角
#define LIMIT_RANGE 110.0f //遥控器通道范围

//基准水平值，由水平校正机体得到
#define STANDARD_PITCH 0.296f
#define STANDARD_ROLL 2.185f 


#define FLASH_RATE 50.0f //帧率

#define YAW_SPEED 90.0f //yaw通道最大速度，度每秒

volatile float de_yaw , de_pitch , de_roll , de_thro;


void initDesireAngles(void)
{
	de_yaw = 0.0f;
	de_roll = STANDARD_ROLL;
	de_pitch = STANDARD_PITCH;
	de_thro = 1000.f;
}

void GetDesireAngles(short X1 ,short Y1 ,short X2, short Y2 )
{
	if(X1<LIMIT_RANGE && X1>-LIMIT_RANGE )
		de_yaw += (X1/LIMIT_RANGE)*(YAW_SPEED/FLASH_RATE);
	
	//越界处理
	if(de_yaw>180)
		de_yaw = de_yaw - 360;

	if(de_yaw<-180)
		de_yaw = de_yaw + 360;
	
	if(Y1<LIMIT_RANGE && Y1>-LIMIT_RANGE )
		de_thro += (Y1/LIMIT_RANGE)*(200/FLASH_RATE);
	
	if(de_thro>1900)
		de_thro = 1900;
	
	if(de_thro<1000)
		de_thro = 1000;
	
	
	if(Y2<LIMIT_RANGE && Y2>-LIMIT_RANGE)
		de_pitch = STANDARD_PITCH + (Y2/LIMIT_RANGE) * LIMIT_ANGLE ;
	if(X2<LIMIT_RANGE && X2>-LIMIT_RANGE)
		de_roll = STANDARD_ROLL + (X2/LIMIT_RANGE) * LIMIT_ANGLE ;
	

}
