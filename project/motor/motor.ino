#include <Servo.h> 

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

void setup() 
{ 
  Serial.begin(9600);
  
  // set motor
  motor1.attach(3,1000,2000);
  motor2.attach(9,1000,2000);
  motor3.attach(10,1000,2000);
  motor4.attach(11,1000,2000);  
   
  // set motor to max-point
  motor1.writeMicroseconds(2000);
  motor2.writeMicroseconds(2000);
  motor3.writeMicroseconds(2000);
  motor4.writeMicroseconds(2000);
  delay(2000);
  
  // set servo to min-point
  motor1.writeMicroseconds(1000);
  motor2.writeMicroseconds(1000);
  motor3.writeMicroseconds(1000);
  motor4.writeMicroseconds(1000);
  delay(1000);
  
  //
  motor1.writeMicroseconds(1100);
  motor2.writeMicroseconds(1100);
  motor3.writeMicroseconds(1100);
  motor4.writeMicroseconds(1100);
} 

void loop() 
{
} 
