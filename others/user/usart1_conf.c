/*******************************************************************************
// file				:	usart1_conf.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	��8.00M
// IDE				: Keil uVision4
// date				��2014.2.28
*******************************************************************************/

#include "usart1_conf.h"
#include "time.h"

#define   uchar unsigned char
#define   uint unsigned int	
#define 	buffer_len 15


unsigned int usart1_tx = 0;


void USART1_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE  );

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //	ѡ�йܽ�9
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);				 // ѡ��A�˿�
    

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			  //ѡ�йܽ�10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);				  //ѡ��A�˿�
}

void USART1_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


void USART1_Configuration(void)
{

	USART_InitTypeDef USART_InitStructure;							//���ڲ�����ʼ���ṹ��
	USART_ClockInitTypeDef  USART_ClockInitStructure;		//����ʱ�Ӳ�����ʼ���ṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 |RCC_APB2Periph_USART1, ENABLE  );   //ʱ��ʹ��

	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;					// ʱ�ӵ͵�ƽ�
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;								// ʱ�ӵ͵�ƽ
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;							// ʱ�ӵڶ������ؽ������ݲ���
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;			// ���һλ���ݵ�ʱ�����岻��SCLK���

	USART_ClockInit(USART1, &USART_ClockInitStructure);									// ʱ�Ӳ�����ʼ������
																	 
	USART_InitStructure.USART_BaudRate = 9600;						  					// ������Ϊ��9600  // ԭΪ115200 ��Ϊ����HC06������Ϊ9600�� 2014.2.10
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8λ����
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				  	// ��֡��β����1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;				  		// ��żʧ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;			// Ӳ��������ʧ��

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  	// ����ʹ��+����ʹ��

	USART_Init(USART1, &USART_InitStructure);
    
  /* Enable USART1 */
	USART_ClearFlag(USART1, USART_IT_RXNE); 				//���жϣ�����һ�����жϺ����������ж�
	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);		//ʹ��USART1�ж�Դ
	USART_Cmd(USART1, ENABLE);											//USART1�ܿ��أ����� 
}


void  USART1_SendData(uchar SendData)
{
	USART_SendData(USART1, SendData);
	Delayms(1);
}

 //********���ڷ�������***************************************
void Send_data_1(uchar axis,uchar data[])
{	
	int i;

  USART1_SendData(axis);
  USART1_SendData(':'); 
  
	for(i=0;i<10;i++)
	USART1_SendData(data[i]);
  
  USART1_SendData(' ');
}



