/*******************************************************************************
// file				:	main.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	��8.00M
// IDE				: Keil uVision4 , ST lib 3.5.0
// date				��2014.2.28


// ��mpu6050���ӣ� GPIOB6->SCL GPIOB7->SDA   
// ���pwmͨ�����ӣ� GPIOA6->01,GPIOA7->02,GPIOB0->03,GPIOB1->04
// ����������ʾ�������ʣ�9600(������HC06Ĭ�ϲ����ʼ��ݣ�
//	����2��������
*******************************************************************************/

#include "stm32f10x.h"
#include "rcc_conf.h"
#include "usart1_conf.h"
#include "usart2_conf.h"
#include "i2c_conf.h"
#include "mpu6050.h"
#include "time.h"
#include "MadgwickAHRS.h"
#include "EulerAngles.h"
#include "tim_conf.h"
#include "DesireAngles.h"
#include "pwm_motor.h"

#include "stdio.h"


#define   uchar unsigned char
#define   uint unsigned int	





int main(void)
{ 
  RCC_Configuration();		 	//����RCC
	initDesireAngles();
	
	TIMER4_Enable();					//��ʱ��4
	TIMER4_Configuration();		//�����ж�
	
  USART1_GPIO_Config();		 	//����GPIO
	USART1_NVIC_Config();			//�����ж�
  USART1_Configuration();	 	//���ô���1
	
	USART2_GPIO_Config();
	USART2_Configuration();

	I2C_GPIO_Config();				//����IICʹ�ö˿�
  Delayms(10);				 			//��ʱ
	Init_MPU6050();		     //��ʼ��MPU6050
	
	PWM_Configuration();
		
	while(1)
	{

	}
	 			//�س�
	
}

/*	
  while(1)
	{
		
		
		READ_MPU6050();	         			//��ȡMPU6050����
		
		MadgwickAHRSupdateIMU(GYRO_X,GYRO_Y,GYRO_Z,ACCE_X,ACCE_Y,ACCE_Z);
		
		quaToEuler(q0,q1,q2,q3);
		
		sprintf(TX_DATA,"%f",eu_yaw);
		Send_data('Y',TX_DATA);
		
		sprintf(TX_DATA,"%f",eu_pitch);
		Send_data('P',TX_DATA);
		
		sprintf(TX_DATA,"%f",eu_roll);
		Send_data('R',TX_DATA);
		
		
		
		sprintf(TX_DATA,"%f",q0);
		Send_data('W',TX_DATA);
		
		sprintf(TX_DATA,"%f",q1);
		Send_data('X',TX_DATA);
		
		sprintf(TX_DATA,"%f",q2);
		Send_data('Y',TX_DATA);
		
		sprintf(TX_DATA,"%f",q3);
		Send_data('Z',TX_DATA);
		
		
		
		sprintf(TX_DATA,"%f",ACCE_X);				//ת��X����ټƵ�����	
		Send_data('X',TX_DATA);			 									//����X����
		
		sprintf(TX_DATA,"%f",ACCE_Y);				//ת��Y����ټƵ�����
		Send_data('Y',TX_DATA);			 									//����Y����
		
		sprintf(TX_DATA,"%f",ACCE_Z);				//ת��Z����ټƵ�����
		Send_data('Z',TX_DATA);			 									//����Z����
		
		sprintf(TX_DATA,"%f",TEMPRETURE);		//ת���¶����ݵ�����
		Send_data('T',TX_DATA);			 									//�����¶�����

    sprintf(TX_DATA,"%f",GYRO_X);				//ת��X�������ǵ�����
		Send_data('X',TX_DATA);			 									//����X����
		
		sprintf(TX_DATA,"%f",GYRO_Y);				//ת��Y�������ǵ�����
		Send_data('Y',TX_DATA);			 									//����Y����
		
		sprintf(TX_DATA,"%f",GYRO_Z);				//ת��Z�������ǵ�����
		Send_data('Z',TX_DATA);			 									//����Z����
		
		
		USART1_SendData(0X0D);	 			//����
		USART1_SendData(0X0A);	 			//�س�
		Delayms(5);				 						//��ʱ
  }
	*/
	
	

