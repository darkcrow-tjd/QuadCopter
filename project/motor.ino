#include <Servo.h> 

Servo myservo;

void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(9,1000,2000);  
  myservo.writeMicroseconds(2000);  // set servo to max-point
  Serial.print("max\n");
  delay(2000);
  myservo.writeMicroseconds(1000);  // set servo to min-point
  Serial.print("min\n");
  delay(1000);
  myservo.writeMicroseconds(1300);  // 
} 

void loop() 
{
} 
