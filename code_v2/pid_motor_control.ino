
int target_rpm  = 6400;
float kp = 0.01;
float kd = 0;
float pre_error = 0;
int motor_pwm = 100;
float current_pwm = 0;
void PIDCALL()
{
  int current_rpm = rpm();
  current_rpm = -1 * current_rpm ;
  int current_error = current_rpm - target_rpm;
  pre_error = current_error;
  float kd_error = current_error - pre_error;

  float pd  = kp * current_error + kd * kd_error;

 if (pd  > 100)
 {
  pd = 100;
  
 }
 
 if (pd  < -100)
 {
  pd = -100;
  
 }

current_pwm = motor_pwm - pd;

if( (pd >-0.2) && (pd <0.2))
{
  motor_pwm = current_pwm;
  
}

//
//  if (pd >0 )
//  {
//    motor_pwm--;
//  }
//  else
//  {
//    motor_pwm++;
//  }

if (motor_pwm >255)
{
  motor_pwm = 200;
}
if (motor_pwm <0)
{
  motor_pwm = 0;
}
  analogWrite(PWM,current_pwm); 
  Serial.print(" current error = ");
  Serial.print(current_error);
  Serial.print(" pd = ");
  Serial.print(pd );
  
  Serial.print(" motor pwm  = ");
  Serial.print(current_pwm);
  Serial.print(" speed .  = ");
  Serial.println(current_rpm);
 
  delay(10);
  
}
