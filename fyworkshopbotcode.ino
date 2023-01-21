#define LM1 10    // left motor
#define LM2 11    // left motor
#define RM1 8   // right motor
#define RM2 9     // right motor

#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial (2, 3);

Servo myservo;

int pos = 0;

int ENA = 7; //right motor
int ENB = 12; //left motor

int counter[6];

int SPEED = 250;
void MoveForward()
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  analogWrite(ENA, SPEED);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  analogWrite(ENB, SPEED);
}

void TurnRight()
{
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  analogWrite(ENB, SPEED);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  analogWrite(ENA, SPEED);
}

void TurnLeft()
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  analogWrite(ENB, SPEED);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  analogWrite(ENA, SPEED);
}

void Stop()
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  analogWrite(ENA, SPEED);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  analogWrite(ENB, SPEED);
  delay(20);
}

void Flick()
{
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
}
void setup()
{
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  int i;
  for (i = 0; i < 6; i++)
  {
    counter[i] = 0;
  }
  myservo.attach(12);
  Serial.begin(9600);

  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  mySerial.begin(9600);
}

void loop()
{

  if (Serial.available())
  {
    char aadesh = Serial.read();
    if (aadesh == '0')
    {
      counter[0] = 1;
      Serial.println("front");
      do
      {
        MoveForward();
        if (Serial.available())
        {
          counter[0] = 0;
          break;
        }
      } while (counter[0] == 1);
    }
    /////////////////////////////////////////////////////
    else if (aadesh == '1')
    {
      counter[1] = 1;
      Serial.println("Right");
      do
      {
        TurnRight();
        if (Serial.available())
        {
          counter[1] = 0;
          break;
        }
      } while (counter[1] == 1);
    }
    ///////////////////////////////////////////////////
    else if (aadesh == '2')
    {
      counter[2] = 1;
      Serial.println("Left");
      do
      {
        TurnLeft();
        if (Serial.available())
        {
          counter[2] = 0;
          break;
        }
      } while (counter[2] == 1);
    }
    ////////////////////////////////////////////////////////
    else if (aadesh == '3')
    {
      counter[3] = 1;
      Serial.println("Stop");
      do
      {
        Stop();
        if (Serial.available())
        {
          counter[3] = 0;
          break;
        }
      } while (counter[3] == 1);
    }
    ////////////////////////////////////////////////////////
    else if (aadesh == '4')
    {
      counter[4] = 1;
      Serial.println("Flick");
      do
      {
        Stop();
        if (Serial.available())
        {
          counter[4] = 0;
          break;
        }
      } while (counter[4] == 1);
    }
    ////////////////////////////////////////////////////////
  }

}
