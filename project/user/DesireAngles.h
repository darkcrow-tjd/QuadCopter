/*******************************************************************************
// file				:	DesireAngles.h
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	£º8.00M
// IDE				: Keil uVision4
// date				£º2014.2.28
*******************************************************************************/
#include "stm32f10x.h"


extern volatile float de_yaw , de_pitch , de_roll ,de_thro;
	
void initDesireAngles(void);
void GetDesireAngles(short X1 ,short Y1 ,short X2, short Y2 );

