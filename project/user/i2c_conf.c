/*******************************************************************************
// file				:	i2c_conf.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	��8.00M
// IDE				: Keil uVision4
// date				��2014.2.28
*******************************************************************************/

#include "i2c_conf.h"

/*ģ��IIC�˿�������붨��*/   

#define SCL_H         GPIOB->BSRR = GPIO_Pin_6   	//BSRR�Ĵ�������GPIOx�ĵ�16λ��ĳλд1����λ��1���������䣻��GPIOx�ĸ�16λ��ĳλд1����λ��0���������䡣
#define SCL_L         GPIOB->BRR  = GPIO_Pin_6 		//BSR�Ĵ���:	��GPIOx�ĵ�16λ��ĳλд1����λ��0���������䣻�üĴ����޸�16λ��
   
#define SDA_H         GPIOB->BSRR = GPIO_Pin_7
#define SDA_L         GPIOB->BRR  = GPIO_Pin_7

#define SCL_read      GPIOB->IDR  & GPIO_Pin_6		//IDR:�˿�����Ĵ�����
#define SDA_read      GPIOB->IDR  & GPIO_Pin_7

	 				


void I2C_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   //��©���ģʽ
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void I2C_delay(void)
{
		
   int i=6; //��������Ż��ٶ�	����������͵�5����д��
   while(i) 
   { 
     i--; 
   }  
}

void delay5ms(void)
{
		
   int i=5000;  
   while(i) 
   { 
     i--; 
   }  
}


int I2C_Start(void)
{
	SDA_H;											//II2Э��涨������ʱ����Ϊ�͵�ƽ��ǰ���£��ſ����� �������źŸı�
	SCL_H;
	I2C_delay();
	
	if(!SDA_read)
		return FALSE;				//SDA��Ϊ�͵�ƽ������æ,�˳�
	SDA_L;								
	
	I2C_delay();
	
	if(SDA_read) 
		return FALSE;				//SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
	SDA_L;								
	
	I2C_delay();					
	
	return TRUE;
}



void I2C_Stop(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
} 


void I2C_Ack(void)
{	
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}   


void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
} 



int I2C_WaitAck(void) 	 //����Ϊ:=1��ACK,  =0��ACK
{
	SCL_L;
	I2C_delay();
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
      SCL_L;
	  I2C_delay();
      return FALSE;
	}
	SCL_L;
	I2C_delay();
	return TRUE;
}




void I2C_SendByte(u8 SendByte) //���ݴӸ�λ����λ//
{
    u8 i=8;
    while(i--)
    {
        SCL_L;
        I2C_delay();
			
      if(SendByte&0x80)		// 0x80 = 1000 0000;
        SDA_H;  
      else 
        SDA_L;   
			
        SendByte<<=1;   // SendByte����һλ��
        I2C_delay();
			
				SCL_H;
        I2C_delay();
    }
    SCL_L;
}  




unsigned char I2C_RadeByte(void)  //���ݴӸ�λ����λ//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      //����һλ��
			
      SCL_L;
      I2C_delay();
			
			SCL_H;
      I2C_delay();	
			
      if(SDA_read)
      {
        ReceiveByte|=0x01; //д��
      }
    }
    SCL_L;
    return ReceiveByte;
} 



int Single_Write(uchar SlaveAddress,uchar REG_Address,uchar REG_data)		     
{
  	if(!I2C_Start())
			return FALSE;
    I2C_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�	//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);	//���ø���ʼ��ַ+������ַ 
    
		if(!I2C_WaitAck())
		{
			I2C_Stop(); 
			return FALSE;
		}
    
		I2C_SendByte(REG_Address );   //���õ���ʼ��ַ      
    I2C_WaitAck();	
    
		I2C_SendByte(REG_data);
    I2C_WaitAck();   
    
		I2C_Stop(); 
    delay5ms();
    return TRUE;
}



unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   
	unsigned char REG_data; 

	
		if(!I2C_Start())
			return FALSE;
    I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!I2C_WaitAck())
		{
			I2C_Stop();

			return FALSE;
		}
    I2C_SendByte((u8) REG_Address);   //���õ���ʼ��ַ      
    I2C_WaitAck();
		I2C_Start();
    
		I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();

		REG_data= I2C_RadeByte();
    I2C_NoAck();
    I2C_Stop();

	return REG_data;

}						 
