


void call()
{
  current_rpm = rpm();
  current_rpm = -1 * current_rpm ;
  target_pwm = (current_pwm * target_rpm ) / current_rpm;
  int current_error = current_rpm - target_rpm;
  float pwm = target_pwm;

  
if (pwm >255)
{
  pwm = 255;
}
if (pwm <10)
{
 pwm = 10;
}

pwm = (pwm + ( pwm_factor *current_pwm) ) / (pwm_factor + 1);

  analogWrite(PWM,pwm); 
  Serial.print(" current error= ");
  Serial.print(current_error);
  Serial.print(" current pwm = ");
  Serial.print(current_pwm);
  
  
  Serial.print("target pwm  = ");
  Serial.print(target_pwm);
  Serial.print(" current  rpm  = ");
  Serial.println(current_rpm);
 
  delay(delay_factor);
  current_pwm = pwm;
  
  
}
