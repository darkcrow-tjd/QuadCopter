/*******************************************************************************
// file				:	tim_conf.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	��8.00M
// IDE				: Keil uVision4
// date				��2014.2.28
*******************************************************************************/

#include "tim_conf.h"


void TIMER4_Enable(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;                          //����	
  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  							//�����ж����ȼ�����
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;        				//����Ϊ��ʱ��4�жϣ������ж�Դ
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;  		//������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            //������Ӧ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                 //ʹ��
    NVIC_Init(&NVIC_InitStructure);    														//��ʼ��
	
}

void TIMER4_Configuration(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;            			//��ʱ������
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 						//��ʱ��4ʱ��ʹ��
	
		TIM_DeInit(TIM4);
    TIM_TimeBaseStructure.TIM_Prescaler =(72-1); 									//psc ����Ԥ��Ƶ�� 72M/72=1M 
    TIM_TimeBaseStructure.TIM_ClockDivision= TIM_CKD_DIV1;        	//=0x0000  ����ʱ��ָ�ֵ  
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 			//����ģʽ
		TIM_TimeBaseStructure.TIM_Period = (5000-1); 									// ����        5ms���ʱ�� 200Hz
  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);         				//��ʼ��
	
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);  										//���־λ
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); 												//ʹ���ж�
		TIM_Cmd(TIM4,ENABLE); 																					//������ʱ��
	
	
}


