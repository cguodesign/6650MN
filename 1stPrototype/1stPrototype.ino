//////////////////////////////////////////////////////////////////
//©2011 bildr
//Released under the MIT License - Please reuse change and share
//Using the easy stepper with your arduino
//use rotate and/or rotateDeg to controll stepper motor
//speed is any number from .01 -> 1 with 1 being fastest - 
//Slower Speed == Stronger movement
/////////////////////////////////////////////////////////////////

#include <NewPing.h>
#define DIR_PIN 2
#define STEP_PIN 3

#define  TRIGGER_PIN  11
#define  ECHO_PIN     10
#define MAX_DISTANCE 200 

#define REDLED     13
#define GREENLED   12

int potPin = A3;
int current = 0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int DistanceIn;
int DistanceCm;
int rotSpeed;

void setup() { 
  Serial.begin(9600);
  Serial.println("UltraSonic Distance Measurement");
  pinMode(DIR_PIN, OUTPUT); 
  pinMode(STEP_PIN, OUTPUT); 
  pinMode(REDLED, OUTPUT); 
  pinMode(GREENLED, OUTPUT); 
  
} 

void loop(){ 
  delay(100);
  current = analogRead(potPin);
  DistanceIn = sonar.ping_in();
  rotSpeed = map(current,0,1023,1,10);

  if(DistanceIn < 1){
    digitalWrite(REDLED,HIGH);
    digitalWrite(GREENLED,LOW);
  }else{
    digitalWrite(GREENLED,HIGH);
    digitalWrite(REDLED,LOW);
  }
  
  Serial.print("Ping: ");
  Serial.print(DistanceIn); 
  Serial.print(" in     ");
  Serial.print("Speed: ");
  Serial.print(current);
  Serial.print("=");
  Serial.print(rotSpeed);
  Serial.println("     ");
  //rotate a specific number of microsteps (8 microsteps per step)
  //a 200 step stepper would take 1600 micro steps for one full revolution
  rotate(1600, (rotSpeed/10)); 
  delay(1000); 
}



void rotate(int steps, float speed){ 
  //rotate a specific number of microsteps (8 microsteps per step) - (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (steps > 0)? HIGH:LOW;
  steps = abs(steps);

  digitalWrite(DIR_PIN,dir); 

  float usDelay = (1/speed) * 70;

  for(int i=0; i < steps; i++){ 
    digitalWrite(STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 

    digitalWrite(STEP_PIN, LOW); 
    delayMicroseconds(usDelay); 
  } 
} 

void rotateDeg(float deg, float speed){ 
  //rotate a specific number of degrees (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (deg > 0)? HIGH:LOW;
  digitalWrite(DIR_PIN,dir); 

  int steps = abs(deg)*(1/0.225);
  float usDelay = (1/speed) * 70;

  for(int i=0; i < steps; i++){ 
    digitalWrite(STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 

    digitalWrite(STEP_PIN, LOW); 
    delayMicroseconds(usDelay); 
  } 
}
