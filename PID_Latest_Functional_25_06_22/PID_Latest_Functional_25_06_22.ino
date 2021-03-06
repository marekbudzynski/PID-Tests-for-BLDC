#include <util/atomic.h>

// Pins
#define ENCA 2 // for Hall output or Board output
#define ENCB 3
#define PWM 5 // this goes to Board PMW input
#define IN1 6
#define IN2 7

// globals
unsigned long prevT = 0;
int posPrev = 0;
// Use the "volatile" directive for variables
// used in an interrupt
volatile int pos_i = 0;
volatile float velocity_i = 0;
volatile long prevT_i = 0;

float v1Filt = 0;
float v1Prev = 0;
float v2Filt = 0;
float v2Prev = 0;

float eintegral = 0;

void setup() {
  Serial.begin(115200);

  pinMode(ENCA,INPUT_PULLUP);
  pinMode(PWM,OUTPUT);
 

  attachInterrupt(digitalPinToInterrupt(ENCA),
                  readEncoder,RISING);
}

void loop() {

  // read the position in an atomic block
  // to avoid potential misreads
  int pos = 0;
  float velocity2 = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    pos = pos_i;
    velocity2 = velocity_i;
    int e = pos - target;
  }

  // Compute velocity with method 1
  unsigned long currT = micros();
  float deltaT = ((float) (currT-prevT))/1.0e6;
  float velocity1 = (pos - posPrev)/deltaT;
  posPrev = pos;
  prevT = currT;

  

  // Convert count/s to RPM
  float v1 = velocity1/12.0*60.0; // this is where you put how many pulses per revolution 12 in this case
  float v2 = velocity2/12.0*60.0;

  // Low-pass filter (25 Hz cutoff)
  v1Filt = 0.854*v1Filt + 0.0728*v1 + 0.0728*v1Prev;
  v1Prev = v1;
  v2Filt = 0.854*v2Filt + 0.0728*v2 + 0.0728*v2Prev;
  v2Prev = v2;

  // Set a target
  float vt = 50*(sin(currT/1e6)>0);

  // Compute the control signal u
  float kp = 0.55;
  float ki = 0.005;
  float e = vt-v1Filt;
  eintegral = eintegral + e*deltaT;
  
  float u = kp*e + ki*eintegral;
  

  // Set the motor speed and direction
  int dir = 1;
  if (u<0){
    dir = -1;
  }
  int pwr = (int) fabs(u);
  if(pwr > 64){
    pwr = 101;  //this is the rough speed from 0 to 255 or 39.6% Duty cycle
  }
  setMotor(dir,pwr,PWM,IN1,IN2);

  Serial.print(vt);
  Serial.print(" ");
  Serial.print(v1Filt);
  Serial.println();
  delay(1);
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal); // Motor speed
 
  
}

void readEncoder(){
  // Read encoder B when ENCA rises
  int b = digitalRead(ENCB);
  int increment = 0;
  if(b>0){
    // If B is high, increment forward
    increment = 1;
  }
  else{
    // Otherwise, increment backward
    increment = -1;
  }
  pos_i = pos_i + increment;

  // Compute velocity with method 2
  unsigned long currT = micros();
  float deltaT = ((float) (currT - prevT_i))/1.0e6;
  velocity_i = increment/deltaT;
  prevT_i = currT;
}
