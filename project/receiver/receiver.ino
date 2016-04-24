int throttle_pin = 2;
int yaw_pin = 6;
int roll_pin = 5;
int pitch_pin = 4;
unsigned long throttle;
unsigned long yaw;
unsigned long roll;
unsigned long pitch;

int count = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(throttle_pin, INPUT);
  pinMode(yaw_pin, INPUT);
  pinMode(roll_pin, INPUT);
  pinMode(pitch_pin, INPUT);
}

void loop()
{
  throttle = pulseIn(throttle_pin, HIGH);
  yaw = pulseIn(yaw_pin, HIGH);
  roll = pulseIn(roll_pin, HIGH);
  pitch = pulseIn(pitch_pin, HIGH);

  Serial.print("THR = "); Serial.print(throttle);
  Serial.print(" | YAW = "); Serial.print(yaw);
  Serial.print(" | ROLL = "); Serial.print(roll);
  Serial.print(" | PITCH = "); Serial.print(pitch);
  Serial.print("\n");

}
