/*******************************************************************************
// file				:	pwm_motor.h
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	��8.00M
// IDE				: Keil uVision4
// date				��2014.2.28
*******************************************************************************/
#include "stm32f10x.h"

#define MOTOR_1 TIM3->CCR1
#define MOTOR_2 TIM3->CCR2
#define MOTOR_3 TIM3->CCR3
#define MOTOR_4 TIM3->CCR4

void PWM_Configuration(void);

