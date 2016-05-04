
#include "hmc5883l.h"
#include "time.h"

#define	HMC5883L_Addr   0x3C	  //定义器件在IIC总线中的从地址

#define SCL_H         GPIOB->BSRR = GPIO_Pin_6   	//BSRR寄存器；向GPIOx的低16位中某位写1，该位置1，其他不变；向GPIOx的高16位中某位写1，该位置0，其他不变。
#define SCL_L         GPIOB->BRR  = GPIO_Pin_6 		//BSR寄存器:	向GPIOx的低16位中某位写1，该位置0，其他不变；该寄存器无高16位。
   
#define SDA_H         GPIOB->BSRR = GPIO_Pin_7
#define SDA_L         GPIOB->BRR  = GPIO_Pin_7

#define SCL_read      GPIOB->IDR  & GPIO_Pin_6		//IDR:端口输入寄存器。
#define SDA_read      GPIOB->IDR  & GPIO_Pin_7

	 				

void I2C_Start()
{
    SDA_H;
    SCL_H;                   
    delay_us(2);                
    SDA_L;                   
    delay_us(2);                 
    SCL_L;                  
}
//**************************************
//I2Cstop
//**************************************
void I2C_Stop()
{
    SDA_L;                    
    SCL_H;                    
    delay_us(2);                 
    SDA_H;                    
    delay_us(2);                
}
//**************************************
//I2C transmit
//ack (0:ACK 1:NAK)
//**************************************
void I2C_SendACK(u8 ack)
{
	if(ack)
    SDA_H;
	else
		SDA_L;
  
	SCL_H;                    
  delay_us(2);                 
  SCL_L;                    
  delay_us(2);                
}
//**************************************
//I2C received signal
//**************************************

u8 I2C_RecvACK()
{
	  u8 CY;
	  SCL_H;
	  delay_us(2);
    I2C_SDAin;
    delay_us(2);
    CY = I2C_SDA_READ;
	  delay_us(2);
    I2C_SDAout;
    SCL_H;                
    delay_us(2);
    return CY;
}

//**************************************
//I2C transmit a byte data
//**************************************
u8 I2C_SendByte(u8 dat)
{
    u8 i;  
    for (i=0; i<8; i++)         
    {
			I2C_SDA =((dat<<i)&0x80)>>7; 
		  delay_us(2); 				 
		  I2C_SCL=1;                
		  delay_us(2);                          
		  I2C_SCL=0;             
    }
    return I2C_RecvACK();
}

//**************************************
// I2C received a byte data
//**************************************
u8 I2C_RecvByte()
{
    u8 i;
    u8 dat = 0;
    I2C_SDA=1; 
    delay_us(2);
	  I2C_SDAin;
    for (i=0; i<8; i++)         
    {
			  delay_us(2);
        dat <<= 1;
        I2C_SCL=1;                
        delay_us(2); 			
        dat |= I2C_SDA_READ;                          
        I2C_SCL=0;               
        delay_us(2);          
    }
		I2C_SDAout;
    return dat;
}
//**************************************
//I2C write a byte data
//**************************************
void Single_WriteI2C(u8 REG_Address,u8 REG_data)
{
    I2C_Start();                
    I2C_SendByte(SlaveAddress);   
    I2C_SendByte(REG_Address);   
    I2C_SendByte(REG_data);       
    I2C_Stop();                  
}
//**************************************
//I2C read a byte
//**************************************
u8 Single_ReadI2C(u8 REG_Address)
{
		u8 REG_data;
		I2C_Start();                   
		I2C_SendByte(SlaveAddress);    
		I2C_SendByte(REG_Address);     
		I2C_Start();                   
		I2C_SendByte(SlaveAddress+1); 
		REG_data=I2C_RecvByte();       
		I2C_SendACK(1);                
		I2C_Stop();                   
		return REG_data;
}


volatile u8 BUFFER[8];
volatile float M_X = 0.0f , M_Y = 0.0f , M_Z = 0.0f ;

//初始化HMC5883，根据需要请参考pdf进行修改****  

void Init_HMC5883L()
{
	 RCC->APB2ENR|=1<<6;    	//使能PORTE时钟	
	 GPIOE->CRL&=0xffffff00;
	 GPIOE->CRL|=0x00000077;
	 GPIOE->ODR|=3;
   Single_Write(HMC5883L_Addr,0x02,0x00);  
}


void Multiple_Read_HMC5883L(void)
{   
	  u8 i;
    I2C_Start();                          //起始信号
    I2C_SendByte(0x3C);           //发送设备地址+写信号
    I2C_SendByte(0x03);                   //发送存储单元地址，从0x3开始	
    I2C_Start();                          //起始信号
    I2C_SendByte(0x3D);         //发送设备地址+读信号
	  for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = I2C_RecvByte();          //BUF[0]存储数据
        if (i == 5)
        {
           I2C_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          I2C_SendACK(0);                 //回应ACK
        }
    }
    I2C_Stop();                           //停止信号


		M_X = BUFFER[0]<<8|BUFFER[1];
		M_Y = BUFFER[2]<<8|BUFFER[3];
		M_Z = BUFFER[4]<<8|BUFFER[5];
}

