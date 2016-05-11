/*******************************************************************************
// file				:	i2c_conf.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	：8.00M
// IDE				: Keil uVision4
// date				：2014.2.28
*******************************************************************************/

#include "i2c_conf.h"

/*模拟IIC端口输出输入定义*/   

#define SCL_H         GPIOB->BSRR = GPIO_Pin_6   	//BSRR寄存器；向GPIOx的低16位中某位写1，该位置1，其他不变；向GPIOx的高16位中某位写1，该位置0，其他不变。
#define SCL_L         GPIOB->BRR  = GPIO_Pin_6 		//BSR寄存器:	向GPIOx的低16位中某位写1，该位置0，其他不变；该寄存器无高16位。
   
#define SDA_H         GPIOB->BSRR = GPIO_Pin_7
#define SDA_L         GPIOB->BRR  = GPIO_Pin_7

#define SCL_read      GPIOB->IDR  & GPIO_Pin_6		//IDR:端口输入寄存器。
#define SDA_read      GPIOB->IDR  & GPIO_Pin_7

	 				


void I2C_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   //开漏输出模式
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void I2C_delay(void)
{
		
   int i=6; //这里可以优化速度	，经测试最低到5还能写入
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
	SDA_H;											//II2协议规定必须在时钟线为低电平的前提下，才可以让 数据线信号改变
	SCL_H;
	I2C_delay();
	
	if(!SDA_read)
		return FALSE;				//SDA线为低电平则总线忙,退出
	SDA_L;								
	
	I2C_delay();
	
	if(SDA_read) 
		return FALSE;				//SDA线为高电平则总线出错,退出
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



int I2C_WaitAck(void) 	 //返回为:=1有ACK,  =0无ACK
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




void I2C_SendByte(u8 SendByte) //数据从高位到低位//
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
			
        SendByte<<=1;   // SendByte左移一位。
        I2C_delay();
			
				SCL_H;
        I2C_delay();
    }
    SCL_L;
}  




unsigned char I2C_RadeByte(void)  //数据从高位到低位//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      //左移一位，
			
      SCL_L;
      I2C_delay();
			
			SCL_H;
      I2C_delay();	
			
      if(SDA_read)
      {
        ReceiveByte|=0x01; //写入
      }
    }
    SCL_L;
    return ReceiveByte;
} 



int Single_Write(uchar SlaveAddress,uchar REG_Address,uchar REG_data)		     
{
  	if(!I2C_Start())
			return FALSE;
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号	//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);	//设置高起始地址+器件地址 
    
		if(!I2C_WaitAck())
		{
			I2C_Stop(); 
			return FALSE;
		}
    
		I2C_SendByte(REG_Address );   //设置低起始地址      
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
    I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck())
		{
			I2C_Stop();

			return FALSE;
		}
    I2C_SendByte((u8) REG_Address);   //设置低起始地址      
    I2C_WaitAck();
		I2C_Start();
    
		I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();

		REG_data= I2C_RadeByte();
    I2C_NoAck();
    I2C_Stop();

	return REG_data;

}						 
