#include <util/atomic.h>

// Pins
#define ENCA 2
#define ENCB 3
#define PWM 5
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


void setup() {
  Serial.begin(115200);

  pinMode(ENCA,INPUT_PULLUP);
  pinMode(PWM,OUTPUT);
 

  attachInterrupt(digitalPinToInterrupt(ENCA),
                  readEncoder,RISING);
}

void loop() {
  PIDCALL();

//  analogWrite(PWM, 200); 
//  int a = rpm();
//  a = -1 * a;
//Serial.println();
//delay(10);

}

int rpm()
{
  
  // read the position in an atomic block
  // to avoid potential misreads
  int pos = 0;

    pos = pos_i;
 

  // Compute velocity with method 1
  unsigned long currT = micros();
  float deltaT = ((float) (currT-prevT))/1.0e6;
  float velocity1 = (pos - posPrev)/deltaT;
  posPrev = pos;
  prevT = currT;

  

  // Convert count/s to RPM
  float v1 = velocity1/4.0*60.0;

  // Low-pass filter (25 Hz cutoff)
  v1Filt = 0.854*v1Filt + 0.0728*v1 + 0.0728*v1Prev;
  v1Prev = v1;

 // v1Filt = -1 * v1Filt;
return  v1Filt;
  
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
 
}
