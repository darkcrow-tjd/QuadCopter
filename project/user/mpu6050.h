/*******************************************************************************
// file				:	mpu6050.h
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	£º8.00M
// IDE				: Keil uVision4
// date				£º2014.2.28
*******************************************************************************/
#include "stm32f10x.h"



extern volatile float GYRO_X,	GYRO_Y,	GYRO_Z;
extern volatile float ACCE_X, ACCE_Y, ACCE_Z;
extern volatile short TEMPRETURE;

void Init_MPU6050(void);
void READ_MPU6050(void);

