/*******************************************************************************
// file				:	usart2_conf.h
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	£º8.00M
// IDE				: Keil uVision4
// date				£º2014.2.28
*******************************************************************************/
#include "stm32f10x.h"


#define   uchar unsigned char
#define   uint unsigned int	

void USART2_Configuration(void);
void USART2_GPIO_Config(void);
void USART2_SendData(uchar SendData);
void Send_data_2(uchar axis,uchar data[]);

