/*******************************************************************************
// file				:	rcc_conf.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	：8.00M
// IDE				: Keil uVision4
// date				：2014.2.28
*******************************************************************************/
#include "rcc_conf.h"


ErrorStatus HSEStartUpStatus;		


void RCC_Configuration(void)
{   
  
  RCC_DeInit();										// RCC system reset(for debug purpose) 
	RCC_HSEConfig(RCC_HSE_ON);			// Enable HSE 
	HSEStartUpStatus = RCC_WaitForHSEStartUp();		// Wait till HSE is ready 

  if(HSEStartUpStatus == SUCCESS)
  {
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //开启FLASH预读缓冲功能，加速FLASH的读取。所有程序中必须的用法.位置：RCC初始化子函数里面，时钟起振之后
    FLASH_SetLatency(FLASH_Latency_2);                    //flash操作的延时
    
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 			//HCLK = SYSCLK 
		RCC_PCLK2Config(RCC_HCLK_Div1);  			// PCLK2 = HCLK 
		RCC_PCLK1Config(RCC_HCLK_Div2);				// PCLK1 = HCLK/2 
		FLASH_SetLatency(FLASH_Latency_2); 		// Flash 2 wait state 
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); 		// Enable Prefetch Buffer 
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);			// PLLCLK = 8MHz * 9 = 72 MHz 
		RCC_PLLCmd(ENABLE);			// Enable PLL 

		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) 				// Wait till PLL is ready 
    {
    }
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);								// Select PLL as system clock source 
		while(RCC_GetSYSCLKSource() != 0x08)											// Wait till PLL is used as system clock source 
    {
    }
  } 
	
	
}
