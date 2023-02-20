//
//#include <Stepper.h>
//
//const int stepsPerRevolution = 200; 
//
//
//
//Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
//
//void setup() {
//  myStepper.setSpeed(60);
//  Serial.begin(9600);
//}
//
//void loop() {
//  Serial.println("clockwise");
//  myStepper.step(stepsPerRevolution);
//  delay(500);
//  
//  Serial.println("counterclockwise");
//  myStepper.step(-stepsPerRevolution);
//  delay(500);
//}


int dir = 5;
int pul = 9;

void setup(){
  Serial.begin(9600);
  pinMode(pul,OUTPUT);
  pinMode(dir,OUTPUT);
  digitalWrite(dir, LOW);
  
}
void loop(){
  digitalWrite(pul,HIGH);
  delayMicroseconds(50);
  digitalWrite(pul,LOW);
  delayMicroseconds(50);
  
}
