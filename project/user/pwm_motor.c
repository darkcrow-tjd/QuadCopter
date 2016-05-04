/*******************************************************************************
// file				:	pwm_motor.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	：8.00M
// IDE				: Keil uVision4
// date				：2014.2.28
*******************************************************************************/

#include "pwm_motor.h"

#define MOTOR_1 TIM3->CCR1
#define MOTOR_2 TIM3->CCR2
#define MOTOR_3 TIM3->CCR3
#define MOTOR_4 TIM3->CCR4


void PWM_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE  );
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	

	MOTOR_1 = 1000;
	MOTOR_2 = 1000;
	MOTOR_3 = 1000;
	MOTOR_4 = 1000;
	
	TIM_TimeBaseStructure.TIM_Period = (5000 - 1); //周期 20000, 5ms
	TIM_TimeBaseStructure.TIM_Prescaler = (72-1); //分频系数
	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); 
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //配置为PWM模式1

	
	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//当定时器计数值小于motor_1时为高电平
	//
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		
	TIM_OCInitStructure.TIM_Pulse = MOTOR_1; //设置电平跳变值
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//使能通道1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //
	
	//
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
	TIM_OCInitStructure.TIM_Pulse = MOTOR_2; //设置电平跳变值
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);//使能通道2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //
	
	//
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
	TIM_OCInitStructure.TIM_Pulse = MOTOR_3; //设置电平跳变值
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);//使能通道3
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //
	
	//
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
	TIM_OCInitStructure.TIM_Pulse = MOTOR_4; //设置电平跳变值
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);//使能通道4
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //
	
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
	
}
