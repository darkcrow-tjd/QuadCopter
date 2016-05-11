/*******************************************************************************
// file				:	i2c_conf.h
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	£º8.00M
// IDE				: Keil uVision4
// date				£º2014.2.28
*******************************************************************************/
#include "stm32f10x.h"

#define   uchar unsigned char
#define   uint unsigned int

#define  	FALSE 0  
#define   TRUE  1

void I2C_GPIO_Config(void);
void I2C_delay(void);
void delay5ms(void);
int I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NoAck(void);
int I2C_WaitAck(void);
void I2C_SendByte(u8 SendByte);
unsigned char I2C_RadeByte(void);
int Single_Write(uchar SlaveAddress,uchar REG_Address,uchar REG_data);
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);



