

/*******************************************************************************
// file				:	usart2_conf.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	��8.00M
// IDE				: Keil uVision4
// date				��2014.2.28
*******************************************************************************/


#include "usart2_conf.h"
#include "time.h"

#define   uchar unsigned char
#define   uint unsigned int	


void USART2_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE  );

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //	ѡ�йܽ�2  TX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);				 // ѡ��A�˿�
    

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			  //ѡ�йܽ�3  RX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);				  //ѡ��A�˿�
}


void USART2_Configuration(void)
{

	USART_InitTypeDef USART_InitStructure;							//���ڲ�����ʼ���ṹ��
	USART_ClockInitTypeDef  USART_ClockInitStructure;		//����ʱ�Ӳ�����ʼ���ṹ��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE  );   //ʱ��ʹ��

	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;					// ʱ�ӵ͵�ƽ�
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;								// ʱ�ӵ͵�ƽ
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;							// ʱ�ӵڶ������ؽ������ݲ���
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;			// ���һλ���ݵ�ʱ�����岻��SCLK���

	USART_ClockInit(USART2, &USART_ClockInitStructure);									// ʱ�Ӳ�����ʼ������
																	 
	USART_InitStructure.USART_BaudRate = 9600;						  					// ������Ϊ��9600  
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8λ����
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				  	// ��֡��β����1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;				  		// ��żʧ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;			// Ӳ��������ʧ��

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  	// ����ʹ��+����ʹ��

	USART_Init(USART2, &USART_InitStructure);
    
  /* Enable USART1 */
	USART_ClearFlag(USART2, USART_IT_RXNE); 				//���жϣ�����һ�����жϺ����������ж�
	USART_ITConfig(USART2,USART_IT_RXNE, ENABLE);		//ʹ��USART2�ж�Դ
	USART_Cmd(USART2, ENABLE);											//USART2�ܿ��أ����� 
}

void  USART2_SendData(uchar SendData)
{
	USART_SendData(USART2, SendData);
	Delayms(1);
}

 //********���ڷ�������***************************************
void Send_data(uchar axis,uchar data[])
{	
	int i;

  USART2_SendData(axis);
  USART2_SendData(':'); 
  
	for(i=0;i<4;i++)
	USART2_SendData(data[i]);
  
  USART2_SendData(' ');
}

