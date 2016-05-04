/*******************************************************************************
// file				:	PID_control.h
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	£º8.00M
// IDE				: Keil uVision4
// date				£º2014.2.28
*******************************************************************************/
#include "stm32f10x.h"





void convert_motor(float de_thro ,float de_yaw, float de_pitch, float de_roll,float eu_yaw,float eu_pitch,float eu_roll);
float relative_error(float desired, float current);

