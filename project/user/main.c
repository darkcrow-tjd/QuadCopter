/*******************************************************************************
// file				:	main.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	：8.00M
// IDE				: Keil uVision4 , ST lib 3.5.0
// date				：2014.2.28


// 与mpu6050连接， GPIOB6->SCL GPIOB7->SDA   
// 电调pwm通道连接， GPIOA6->01,GPIOA7->02,GPIOB0->03,GPIOB1->04
// 串口助手显示，波特率：9600(与蓝牙HC06默认波特率兼容）
//	串口2用来调试
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
  RCC_Configuration();		 	//配置RCC
	initDesireAngles();
	
	TIMER4_Enable();					//定时器4
	TIMER4_Configuration();		//配置中断
	
  USART1_GPIO_Config();		 	//配置GPIO
	USART1_NVIC_Config();			//配置中断
  USART1_Configuration();	 	//配置串口1
	
	USART2_GPIO_Config();
	USART2_Configuration();

	I2C_GPIO_Config();				//配置IIC使用端口
  Delayms(10);				 			//延时
	Init_MPU6050();		     //初始化MPU6050
	
	PWM_Configuration();
		
	while(1)
	{

	}
	 			//回车
	
}

/*	
  while(1)
	{
		
		
		READ_MPU6050();	         			//读取MPU6050数据
		
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
		
		
		
		sprintf(TX_DATA,"%f",ACCE_X);				//转换X轴加速计到数组	
		Send_data('X',TX_DATA);			 									//发送X轴数
		
		sprintf(TX_DATA,"%f",ACCE_Y);				//转换Y轴加速计到数组
		Send_data('Y',TX_DATA);			 									//发送Y轴数
		
		sprintf(TX_DATA,"%f",ACCE_Z);				//转换Z轴加速计到数组
		Send_data('Z',TX_DATA);			 									//发送Z轴数
		
		sprintf(TX_DATA,"%f",TEMPRETURE);		//转换温度数据到数组
		Send_data('T',TX_DATA);			 									//发送温度数据

    sprintf(TX_DATA,"%f",GYRO_X);				//转换X轴陀螺仪到数组
		Send_data('X',TX_DATA);			 									//发送X轴数
		
		sprintf(TX_DATA,"%f",GYRO_Y);				//转换Y轴陀螺仪到数组
		Send_data('Y',TX_DATA);			 									//发送Y轴数
		
		sprintf(TX_DATA,"%f",GYRO_Z);				//转换Z轴陀螺仪到数组
		Send_data('Z',TX_DATA);			 									//发送Z轴数
		
		
		USART1_SendData(0X0D);	 			//换行
		USART1_SendData(0X0A);	 			//回车
		Delayms(5);				 						//延时
  }
	*/
	
	

