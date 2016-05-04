/*******************************************************************************
// file				:	mpu6050.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	：8.00M
// IDE				: Keil uVision4
// date				：2014.2.28
*******************************************************************************/


#include "mpu6050.h"
#include "i2c_conf.h"
#include "stdio.h"

#define	SMPLRT_DIV		0x19	//陀螺仪采样率地址，典型值：0x07(125Hz)
#define	CONFIG				0x1A	//低通滤波频率地址，典型值：0x06(5Hz)

#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)

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

#define	PWR_MGMT_1		0x6B		//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I			0x75		//IIC地址寄存器(默认数值0x68，只读)



#define	MPU6050_Addr   0xD0	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改


volatile float GYRO_X,	GYRO_Y,	GYRO_Z;
volatile float ACCE_X, ACCE_Y, ACCE_Z;
volatile short TEMPRETURE;


unsigned char BUF[14];       	
short data;						//接收数据缓存区 //Read_mpu6050()用到





//初始化MPU6050，根据需要请参考pdf进行修改************************
void Init_MPU6050(void)
{
/*
   Single_Write(MPU6050_Addr,PWR_M, 0x80);   //
   Single_Write(MPU6050_Addr,SMPL, 0x07);    //
   Single_Write(MPU6050_Addr,DLPF, 0x1E);    //±2000°
   Single_Write(MPU6050_Addr,INT_C, 0x00 );  //
   Single_Write(MPU6050_Addr,PWR_M, 0x00);   //
*/
  Single_Write(MPU6050_Addr,PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_Write(MPU6050_Addr,SMPLRT_DIV, 0x04);	//陀螺仪采样率，当前值：0x04,(200Hz),典型值：0x07(125Hz)
	Single_Write(MPU6050_Addr,CONFIG, 0x06);			//低通滤波频率，典型值：0x06(5Hz)
	Single_Write(MPU6050_Addr,GYRO_CONFIG, 0x18);	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000°/s)
	Single_Write(MPU6050_Addr,ACCEL_CONFIG, 0x01);//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
}
	
//******读取MPU6050数据****************************************
void READ_MPU6050(void)
{
	
	 BUF[0]=Single_Read(MPU6050_Addr,ACCEL_XOUT_L); 
   BUF[1]=Single_Read(MPU6050_Addr,ACCEL_XOUT_H);
   data =	(BUF[1]<<8)|BUF[0];
   ACCE_X = ((float)data)/16384; 						   //读取加速计X轴 


   BUF[2]=Single_Read(MPU6050_Addr,ACCEL_YOUT_L);
   BUF[3]=Single_Read(MPU6050_Addr,ACCEL_YOUT_H);
   data =	(BUF[3]<<8)|BUF[2];
   ACCE_Y = ((float)data)/16384; 						   //读取加速计Y轴 

	
   BUF[4]=Single_Read(MPU6050_Addr,ACCEL_ZOUT_L);
   BUF[5]=Single_Read(MPU6050_Addr,ACCEL_ZOUT_H);
   data  =	(BUF[5]<<8)|BUF[4];
   ACCE_Z = ((float)data)/16384; 					       //读取加速计Z轴 

/*
   BUF[6]=Single_Read(MPU6050_Addr,TEMP_OUT_L); 
   BUF[7]=Single_Read(MPU6050_Addr,TEMP_OUT_H); 
   data  =(BUF[7]<<8)|BUF[6];
   TEMPRETURE = 35+ ((double) ( data + 13200)) / 280; // 读取温度
*/
	
   BUF[8]=Single_Read(MPU6050_Addr,GYRO_XOUT_L); 
   BUF[9]=Single_Read(MPU6050_Addr,GYRO_XOUT_H);
   data  =	(BUF[9]<<8)|BUF[8]; 
	data = data/1.64;
   GYRO_X = ((double)data)/10 - 1.1f; 						   //读取陀螺仪X轴


   BUF[10]=Single_Read(MPU6050_Addr,GYRO_YOUT_L);
   BUF[11]=Single_Read(MPU6050_Addr,GYRO_YOUT_H);
   data  =	(BUF[11]<<8)|BUF[10];
	data = data/1.64;	
   GYRO_Y = ((double)data)/10 - 0.1f; 						   //读取陀螺仪Y轴 

	
   BUF[12]=Single_Read(MPU6050_Addr,GYRO_ZOUT_L);
   BUF[13]=Single_Read(MPU6050_Addr,GYRO_ZOUT_H);
   data =	(BUF[13]<<8)|BUF[12];
		data = data/1.64;
   GYRO_Z = ((double)data)/10 - 0.7f; 					       //读取陀螺仪z轴

}



