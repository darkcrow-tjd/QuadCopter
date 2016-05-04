/*******************************************************************************
// file				:	tim_conf.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	：8.00M
// IDE				: Keil uVision4
// date				：2014.2.28
*******************************************************************************/

#include "tim_conf.h"


void TIMER4_Enable(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;                          //声明	
  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  							//设置中断优先级分组
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;        				//设置为定时器4中断，设置中断源
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;  		//设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            //设置响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                 //使能
    NVIC_Init(&NVIC_InitStructure);    														//初始化
	
}

void TIMER4_Configuration(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;            			//定时器声明
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 						//定时器4时钟使能
	
		TIM_DeInit(TIM4);
    TIM_TimeBaseStructure.TIM_Prescaler =(72-1); 									//psc 设置预分频数 72M/72=1M 
    TIM_TimeBaseStructure.TIM_ClockDivision= TIM_CKD_DIV1;        	//=0x0000  设置时间分割值  
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 			//向上模式
		TIM_TimeBaseStructure.TIM_Period = (5000-1); 									// 周期        5ms溢出时间 200Hz
  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);         				//初始化
	
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);  										//清标志位
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); 												//使能中断
		TIM_Cmd(TIM4,ENABLE); 																					//开启定时器
	
	
}


