#include "I2Cdev.h"
#include "HMC5883L.h"
#include "MPU6050.h"
#include "ComplementaryFilter.h"

short yaw;
short pitch;
short roll;

HMC5883L mag;
float mx, my, mz;
int16_t mix, miy, miz;

MPU6050 accelgyro;
float ax, ay, az;
float gx, gy, gz;
int16_t aix, aiy, aiz;
int16_t gix, giy, giz;

Madgwick filter;

unsigned long microsPrevious = 0; // 上次时刻
unsigned long microsNow = 0; // 当前时刻
unsigned long microsPerReading; // 积分周期

void setup()
{
    Wire.begin();
    Serial.begin(115200);
    mag.initialize();
    accelgyro.initialize();
    filter.begin(100);
    microsPerReading = 1000000.0 / 100.0; //频率100Hz
}

void loop()
{ 
  float roll, pitch, heading;

  microsNow = micros();
  if (microsNow - microsPrevious >= microsPerReading) 
  {
    mag.getHeading(&mix, &miy, &miz);
    accelgyro.getMotion6(&aix, &aiy, &aiz, &gix, &giy, &giz);

    ax = convertRawAcceleration(aix);
    ay = convertRawAcceleration(aiy);
    az = convertRawAcceleration(aiz);
    gx = convertRawGyro(gix);
    gy = convertRawGyro(giy);
    gz = convertRawGyro(giz);
    mx = mix;
    my = miy;
    mz = miz;
    
    filter.updateIMU(gx, gy, gz, ax, ay, az);

    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();

    Serial.print(heading);
    Serial.print(",");
    Serial.print(pitch);
    Serial.print(",");
    Serial.print(roll);
    Serial.println(" ");

    microsPrevious = microsPrevious + microsPerReading;
  }
}

float convertRawAcceleration(int aRaw) 
{  
  float a = (aRaw * 2.0) / 32768.0;
  return a;
}

float convertRawGyro(int gRaw) 
{  
  float g = (gRaw * 250.0) / 32768.0;
  return g;
}

