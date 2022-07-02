//-------------------------------------start code----------------------------------------
 
// Pins - these values should match your board.
#define ENCA 2
#define ENCB 3
#define PWM 5
#define IN1 6
#define IN2 7
 
 
void setup() {
// Usable baud rates are 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200
 
  Serial.begin(115200);
 
// The pin mode should match the pin values above and designate whether input or output
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  pinMode(PWM,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
}
 
void loop() {
// For test change the speed value here to verify that the pins are connected and registered correctly.  
               int pwr = 7;
 
               int dir = 1;
              
               // The values passed here need to match the pin configuration. The setMotor function will likely have to be altered – specifically these arguments: PWM, IN1, IN2
               setMotor(dir, pwr, PWM, IN1, IN2);
}
 
void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
 
  analogWrite(pwm,pwmVal); // Motor speed
              
  if(dir == 1){
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }
}
 
 
//-------------------------end code----------------------
 
