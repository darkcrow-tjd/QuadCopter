/*******************************************************************************
// file				:	mpu6050.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	��8.00M
// IDE				: Keil uVision4
// date				��2014.2.28
*******************************************************************************/


#include "mpu6050.h"
#include "i2c_conf.h"
#include "stdio.h"

#define	SMPLRT_DIV		0x19	//�����ǲ����ʵ�ַ������ֵ��0x07(125Hz)
#define	CONFIG				0x1A	//��ͨ�˲�Ƶ�ʵ�ַ������ֵ��0x06(5Hz)

#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)

#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C

#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E

#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40

#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42

#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	

#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46

#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48

#define	PWR_MGMT_1		0x6B		//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I			0x75		//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)



#define	MPU6050_Addr   0xD0	  //����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�


volatile float GYRO_X,	GYRO_Y,	GYRO_Z;
volatile float ACCE_X, ACCE_Y, ACCE_Z;
volatile short TEMPRETURE;


unsigned char BUF[14];       	
short data;						//�������ݻ����� //Read_mpu6050()�õ�





//��ʼ��MPU6050��������Ҫ��ο�pdf�����޸�************************
void Init_MPU6050(void)
{
/*
   Single_Write(MPU6050_Addr,PWR_M, 0x80);   //
   Single_Write(MPU6050_Addr,SMPL, 0x07);    //
   Single_Write(MPU6050_Addr,DLPF, 0x1E);    //��2000��
   Single_Write(MPU6050_Addr,INT_C, 0x00 );  //
   Single_Write(MPU6050_Addr,PWR_M, 0x00);   //
*/
  Single_Write(MPU6050_Addr,PWR_MGMT_1, 0x00);	//�������״̬
	Single_Write(MPU6050_Addr,SMPLRT_DIV, 0x04);	//�����ǲ����ʣ���ǰֵ��0x04,(200Hz),����ֵ��0x07(125Hz)
	Single_Write(MPU6050_Addr,CONFIG, 0x06);			//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
	Single_Write(MPU6050_Addr,GYRO_CONFIG, 0x18);	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000��/s)
	Single_Write(MPU6050_Addr,ACCEL_CONFIG, 0x01);//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
}
	
//******��ȡMPU6050����****************************************
void READ_MPU6050(void)
{
	
	 BUF[0]=Single_Read(MPU6050_Addr,ACCEL_XOUT_L); 
   BUF[1]=Single_Read(MPU6050_Addr,ACCEL_XOUT_H);
   data =	(BUF[1]<<8)|BUF[0];
   ACCE_X = ((float)data)/16384; 						   //��ȡ���ټ�X�� 


   BUF[2]=Single_Read(MPU6050_Addr,ACCEL_YOUT_L);
   BUF[3]=Single_Read(MPU6050_Addr,ACCEL_YOUT_H);
   data =	(BUF[3]<<8)|BUF[2];
   ACCE_Y = ((float)data)/16384; 						   //��ȡ���ټ�Y�� 

	
   BUF[4]=Single_Read(MPU6050_Addr,ACCEL_ZOUT_L);
   BUF[5]=Single_Read(MPU6050_Addr,ACCEL_ZOUT_H);
   data  =	(BUF[5]<<8)|BUF[4];
   ACCE_Z = ((float)data)/16384; 					       //��ȡ���ټ�Z�� 

/*
   BUF[6]=Single_Read(MPU6050_Addr,TEMP_OUT_L); 
   BUF[7]=Single_Read(MPU6050_Addr,TEMP_OUT_H); 
   data  =(BUF[7]<<8)|BUF[6];
   TEMPRETURE = 35+ ((double) ( data + 13200)) / 280; // ��ȡ�¶�
*/
	
   BUF[8]=Single_Read(MPU6050_Addr,GYRO_XOUT_L); 
   BUF[9]=Single_Read(MPU6050_Addr,GYRO_XOUT_H);
   data  =	(BUF[9]<<8)|BUF[8]; 
	data = data/1.64;
   GYRO_X = ((double)data)/10 - 1.1f; 						   //��ȡ������X��


   BUF[10]=Single_Read(MPU6050_Addr,GYRO_YOUT_L);
   BUF[11]=Single_Read(MPU6050_Addr,GYRO_YOUT_H);
   data  =	(BUF[11]<<8)|BUF[10];
	data = data/1.64;	
   GYRO_Y = ((double)data)/10 - 0.1f; 						   //��ȡ������Y�� 

	
   BUF[12]=Single_Read(MPU6050_Addr,GYRO_ZOUT_L);
   BUF[13]=Single_Read(MPU6050_Addr,GYRO_ZOUT_H);
   data =	(BUF[13]<<8)|BUF[12];
		data = data/1.64;
   GYRO_Z = ((double)data)/10 - 0.7f; 					       //��ȡ������z��

}



