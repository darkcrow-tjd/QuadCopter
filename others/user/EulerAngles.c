/*******************************************************************************
// file				: EulerAngles.c
// author			: Zhang Chengwu , Wei TaiHeng
// MCU				: STM32F103VET6
// oscillator	£º8.00M
// IDE				: Keil uVision4
// date				£º2014.2.28
*******************************************************************************/

#include "EulerAngles.h"
#include "math.h"


#define PI_FLOAT     3.14159265f
#define PIBY2_FLOAT  1.5707963f

volatile float eu_yaw = 0.0f , eu_pitch = 0.0f , eu_roll = 0.0f ;


float fastAtan2(float y, float x) 
{
        static float atan;
        static float z;
	
        if (x == 0.0f) 
	{
                if (y > 0.0f)
                        return PIBY2_FLOAT;
                if (y == 0.0f)
                        return 0.0f;
                return -PIBY2_FLOAT;
        }
				
        z = y / x;
				
        if (fabs(z) < 1.0f) 
	{
                atan = z / (1.0f + 0.28f * z * z);
                if (x < 0.0f) 
                {
                        if (y < 0.0f)
                                return atan - PI_FLOAT;
                        return atan + PI_FLOAT;
                }	
        } 
	else 
	{
                atan = PIBY2_FLOAT - z / (z * z + 0.28f);	
                if (y < 0.0f)
                        return atan - PI_FLOAT;
        }
        return atan;
}

void quaToEuler ( float q0 , float q1 , float q2 , float q3 )
{
	eu_roll = fastAtan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (q1 * q1 + q2 * q2)) * 57.3;
        eu_pitch = -(asin(2 * (q0 * q2 - q3 * q1))) * 57.3;
        eu_yaw = fastAtan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (q2 * q2 + q3 * q3)) * 57.3;
    
}
