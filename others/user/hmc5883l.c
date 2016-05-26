
#include "hmc5883l.h"
#include "time.h"

#define	HMC5883L_Addr   0x3C	  //����������IIC�����еĴӵ�ַ

#define SCL_H         GPIOB->BSRR = GPIO_Pin_6   	//BSRR�Ĵ�������GPIOx�ĵ�16λ��ĳλд1����λ��1���������䣻��GPIOx�ĸ�16λ��ĳλд1����λ��0���������䡣
#define SCL_L         GPIOB->BRR  = GPIO_Pin_6 		//BSR�Ĵ���:	��GPIOx�ĵ�16λ��ĳλд1����λ��0���������䣻�üĴ����޸�16λ��
   
#define SDA_H         GPIOB->BSRR = GPIO_Pin_7
#define SDA_L         GPIOB->BRR  = GPIO_Pin_7

#define SCL_read      GPIOB->IDR  & GPIO_Pin_6		//IDR:�˿�����Ĵ�����
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

//��ʼ��HMC5883��������Ҫ��ο�pdf�����޸�****  

void Init_HMC5883L()
{
	 RCC->APB2ENR|=1<<6;    	//ʹ��PORTEʱ��	
	 GPIOE->CRL&=0xffffff00;
	 GPIOE->CRL|=0x00000077;
	 GPIOE->ODR|=3;
   Single_Write(HMC5883L_Addr,0x02,0x00);  
}


void Multiple_Read_HMC5883L(void)
{   
	  u8 i;
    I2C_Start();                          //��ʼ�ź�
    I2C_SendByte(0x3C);           //�����豸��ַ+д�ź�
    I2C_SendByte(0x03);                   //���ʹ洢��Ԫ��ַ����0x3��ʼ	
    I2C_Start();                          //��ʼ�ź�
    I2C_SendByte(0x3D);         //�����豸��ַ+���ź�
	  for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = I2C_RecvByte();          //BUF[0]�洢����
        if (i == 5)
        {
           I2C_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
          I2C_SendACK(0);                 //��ӦACK
        }
    }
    I2C_Stop();                           //ֹͣ�ź�


		M_X = BUFFER[0]<<8|BUFFER[1];
		M_Y = BUFFER[2]<<8|BUFFER[3];
		M_Z = BUFFER[4]<<8|BUFFER[5];
}

