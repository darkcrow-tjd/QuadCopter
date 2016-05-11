/*******************************************************************************
// file				:	PID_control.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	：8.00M
// IDE				: Keil uVision4
// date				：2014.2.28
*******************************************************************************/

#include "PID_control.h"
#include "math.h"


#define ATTI_INT_LIMIT_US_F 0.f
#define HEAD_INT_LIMI_US_F 0.f

#define MAX_ATTI_TRIM_US_F 100.f
#define MAX_HEAD_TRIM_US_F 80.f

#define MAX_THRO_US 1900.f;

float attitude_p_gain = 0.25f , attitude_i_gain = 0.f , attitude_d_gain = 25.f;
float heading_p_gain = 2.f , heading_i_gain = 0.f , heading_d_gain = 235.f;

float last_attitude_roll = 0.f , last_attitude_pitch = 0.f , last_heading = 0.f;
float attitude_roll_iState = 0.f , attitude_pitch_iState = 0.f , heading_iState = 0.f;

float heading_trim, pitch_trim, roll_trim;

float error;

float motor_1 ,motor_2 ,motor_3, motor_4;



float relative_error(float desired, float current)
{
	float error = desired - current, abs_error = fabsf(error);
	if(abs_error > 180)
	{
		if(error > 0)
			error =  - (360 - abs_error);
		else
			error = 360 - abs_error;
	}
	return error;
}


void convert_motor(float de_thro, float de_yaw, float de_pitch, float de_roll ,float eu_yaw,float eu_pitch,float eu_roll)
{
	
	//pitch
		error = de_pitch - eu_pitch;
		attitude_pitch_iState += error * attitude_i_gain;

		if(attitude_pitch_iState > ATTI_INT_LIMIT_US_F)
				attitude_pitch_iState = ATTI_INT_LIMIT_US_F;
		else if(attitude_pitch_iState < - ATTI_INT_LIMIT_US_F)
				attitude_pitch_iState = - ATTI_INT_LIMIT_US_F;

		pitch_trim = (error * attitude_p_gain) + attitude_pitch_iState - ((eu_pitch - last_attitude_pitch) * attitude_d_gain);

		last_attitude_pitch = eu_pitch;
		
		//roll
		error = de_roll - eu_roll;
		attitude_roll_iState += error * attitude_i_gain;

		if(attitude_roll_iState > ATTI_INT_LIMIT_US_F)
				attitude_roll_iState = ATTI_INT_LIMIT_US_F;
		else if(attitude_roll_iState < - ATTI_INT_LIMIT_US_F)
				attitude_roll_iState = - ATTI_INT_LIMIT_US_F;

		pitch_trim = (error * attitude_p_gain) + attitude_roll_iState - ((eu_roll - last_attitude_roll) * attitude_d_gain);

		last_attitude_roll = eu_roll;
		
		//heading
		error = relative_error(de_yaw, eu_yaw);

			heading_iState += error *  heading_i_gain;

			if(heading_iState > HEAD_INT_LIMI_US_F)
				heading_iState = HEAD_INT_LIMI_US_F;
			else if(heading_iState < - HEAD_INT_LIMI_US_F)
				heading_iState = - HEAD_INT_LIMI_US_F;

			heading_trim = (error * heading_p_gain) + heading_iState - (relative_error(eu_yaw, last_heading) * heading_d_gain);
			
			last_heading = eu_yaw;
		
			//限制控制量
			if(pitch_trim > MAX_ATTI_TRIM_US_F)
					pitch_trim = MAX_ATTI_TRIM_US_F;
			if(pitch_trim < - MAX_ATTI_TRIM_US_F)
					pitch_trim = - MAX_ATTI_TRIM_US_F;
			
			if(roll_trim > MAX_ATTI_TRIM_US_F)
					roll_trim = MAX_ATTI_TRIM_US_F;
			if(roll_trim < - MAX_ATTI_TRIM_US_F)
					roll_trim = - MAX_ATTI_TRIM_US_F;
			
			if(heading_trim > MAX_HEAD_TRIM_US_F)
				heading_trim = MAX_HEAD_TRIM_US_F;
			if(heading_trim < - MAX_HEAD_TRIM_US_F)
				heading_trim = - MAX_HEAD_TRIM_US_F;
			
			//分配油门量
			motor_1 = de_thro + pitch_trim;// + heading_trim;
			motor_2 = de_thro - pitch_trim;// + heading_trim;
			motor_3 = de_thro + roll_trim;// - heading_trim;
			motor_4 = de_thro - roll_trim;// - heading_trim;
			
			//限制油门范围
		
				if(motor_1>1900)
					motor_1 = 1900;
				if(motor_1<1000)
					motor_1 = 1000;
				
				if(motor_2>1900)
					motor_2 = 1900;
				if(motor_2<1000)
					motor_2 = 1000;
				
				if(motor_3>1900)
					motor_3 = 1900;
				if(motor_3<1000)
					motor_3 = 1000;
				
				if(motor_3>1900)
					motor_3 = 1900;
				if(motor_3<1000)
					motor_3 = 1000;
	
				
				//更新油门
			TIM_SetCompare1(TIM3, motor_1);
			TIM_SetCompare2(TIM3, motor_2);
		//	TIM_SetCompare3(TIM3, motor_3); 
		//	TIM_SetCompare4(TIM3, motor_4);
			
						
	
}
