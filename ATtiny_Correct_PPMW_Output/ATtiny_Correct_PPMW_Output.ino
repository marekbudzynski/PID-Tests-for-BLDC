int PWM_Pin = 0; /* give PWM_Pin name to D5 pin */
// Perform initialization inside setup()
void setup()
{
pinMode(PWM_Pin,OUTPUT);  /*declare D5 pin as an output pin */ 
TCCR0B = TCCR0B & 0b11111000 | 0b001;  /*set 30.64Hz Frequency */
}
void loop()
{
analogWrite(PWM_Pin,64);
TCCR0B = TCCR0B & 0b11111000 | 0b001;
}
