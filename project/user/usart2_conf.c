

/*******************************************************************************
// file				:	usart2_conf.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	：8.00M
// IDE				: Keil uVision4
// date				：2014.2.28
*******************************************************************************/


#include "usart2_conf.h"
#include "time.h"

#define   uchar unsigned char
#define   uint unsigned int	


void USART2_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE  );

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //	选中管脚2  TX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);				 // 选择A端口
    

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			  //选中管脚3  RX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);				  //选择A端口
}


void USART2_Configuration(void)
{

	USART_InitTypeDef USART_InitStructure;							//串口参数初始化结构体
	USART_ClockInitTypeDef  USART_ClockInitStructure;		//串口时钟参数初始化结构体

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE  );   //时钟使能

	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;					// 时钟低电平活动
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;								// 时钟低电平
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;							// 时钟第二个边沿进行数据捕获
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;			// 最后一位数据的时钟脉冲不从SCLK输出

	USART_ClockInit(USART2, &USART_ClockInitStructure);									// 时钟参数初始化设置
																	 
	USART_InitStructure.USART_BaudRate = 9600;						  					// 波特率为：9600  
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8位数据
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				  	// 在帧结尾传输1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;				  		// 奇偶失能
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;			// 硬件流控制失能

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  	// 发送使能+接收使能

	USART_Init(USART2, &USART_InitStructure);
    
  /* Enable USART1 */
	USART_ClearFlag(USART2, USART_IT_RXNE); 				//清中断，以免一启用中断后立即产生中断
	USART_ITConfig(USART2,USART_IT_RXNE, ENABLE);		//使能USART2中断源
	USART_Cmd(USART2, ENABLE);											//USART2总开关：开启 
}

void  USART2_SendData(uchar SendData)
{
	USART_SendData(USART2, SendData);
	Delayms(1);
}

 //********串口发送数据***************************************
void Send_data(uchar axis,uchar data[])
{	
	int i;

  USART2_SendData(axis);
  USART2_SendData(':'); 
  
	for(i=0;i<4;i++)
	USART2_SendData(data[i]);
  
  USART2_SendData(' ');
}

