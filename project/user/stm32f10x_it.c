/*******************************************************************************
// file				:	stm32f10x_it.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	：8.00M
// IDE				: Keil uVision4
// date				：2014.2.28
*******************************************************************************/

#include "stm32f10x_it.h"

#include "mpu6050.h"
#include "MadgwickAHRS.h"
#include "EulerAngles.h"
#include "usart2_conf.h"
#include "usart1_conf.h"
#include "DesireAngles.h"
#include "PID_control.h"
#include "crc_check.h"
#include "pwm_motor.h"

#include "stdio.h"


//////////


///////////


unsigned int num = 0;;
unsigned print_count = 0;
unsigned char TX_DATA[10];


unsigned char data_buffer;
unsigned int head_status = 0;
unsigned int recstatus = 0;
unsigned int count = 0;
volatile unsigned char usart1_buffer[15];
volatile short X1 , Y1 , X2 , Y2 , crc ;
volatile unsigned char button1, button2, len , version , protocol ;






void Get_Usart1_Data(void)   //解数据包
{

	//USART_ITConfig(USART1,USART_IT_RXNE, DISABLE);

		len = usart1_buffer[0];

		version = usart1_buffer[1];
	
		protocol = usart1_buffer[2];
		
		button1 = usart1_buffer[4];
		button2 = usart1_buffer[3];
	
		X1 = (usart1_buffer[6]<<8)|usart1_buffer[5];

		Y1 = (usart1_buffer[8]<<8|usart1_buffer[7]) * (-1);
	
		X2 = (usart1_buffer[10]<<8)|usart1_buffer[9];
	
		Y2 = (usart1_buffer[12]<<8)|usart1_buffer[11];
		
		crc = (usart1_buffer[14]<<8)|usart1_buffer[13];
		
	//	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);
	
}


void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		data_buffer = USART_ReceiveData(USART1);
		
		if(data_buffer == 0x55 )
		{
			head_status = 1;
			return;
		}
		if(data_buffer == 0xaa)
		{
			if(head_status == 1)
			{
				recstatus = 1;
				head_status = 0;
				return;
			}
		}
		if(count == 15)
		{
			recstatus = 0;
			count = count%15;
		}
		
		if(recstatus == 1)
		{
			usart1_buffer[count++] = data_buffer ;
			return ;
		}
	}
	
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(USART1,USART_FLAG_ORE);
		USART_ReceiveData(USART1);
	}
}


void TIM4_IRQHandler(void)
{	
	
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
	{
		TIM_ClearFlag(TIM4,TIM_IT_Update);  
		
		Get_Usart1_Data();
		if(button2 == 0x01)
		{
			//获取实时姿态角
			READ_MPU6050();	
			MadgwickAHRSupdateIMU(GYRO_X,GYRO_Y,GYRO_Z,ACCE_X,ACCE_Y,ACCE_Z);
			quaToEuler(q0,q1,q2,q3);
		
			//获取期望姿态角

			GetDesireAngles(X1,Y1,X2,Y2);

			//计算油门量
			convert_motor(de_thro,de_yaw,de_pitch,de_roll,eu_yaw,eu_pitch,eu_roll);
			
			
		}
		
		else
		{
			TIM_SetCompare1(TIM3,1000);
			TIM_SetCompare2(TIM3,1000);
			TIM_SetCompare3(TIM3,1000);
			TIM_SetCompare4(TIM3,1000);
		}
		
		
	}
		 
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
