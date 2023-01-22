#include <MPU6050_light.h>     // Gyroscope Sensor MPU-6050 library 
#include "Wire.h"              // Library for I2C protocol

#include <RoboClaw.h>
#include<SoftwareSerial.h>

// Address of two RoboClaws
#define add1 128
#define add2 129

// Tune in the values of kp, ki, kd according to your satisfaction
#define kp 2          // Proportionality Constant 
#define ki 0          // Integration Constant 
#define kd 4          // Derivative Constant 


// Creating objects for RoboClaw 
RoboClaw roboclaw1(&Serial1,10000);    
RoboClaw roboclaw2(&Serial1,10000);     

MPU6050 mpu(Wire);
unsigned long timer = 0;
int bot_angle = 0;
int wheel_speed = 0;
int wheel_direction = 0;

int error = 0;
int prev_error = 0;


void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  roboclaw1.ForwardM1(add1, 0);
  roboclaw1.ForwardM2(add1, 0);
  roboclaw2.ForwardM2(add2, 0);
  Wire.begin();
 
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
 
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true;                           // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

void gyroPID(){                                               // Function to integrate P.I.D. to Gyrocope Sensor
  error = bot_angle;
  int p_error = error;
  int i_error = 0;
  i_error = error + i_error;
  int d_error = error - prev_error;
  float P = kp * p_error;
  float I = ki * i_error;
  float D = kd * d_error;
  float correction = P + I + D;                   

  wheel_speed = fabs(correction);
  if(wheel_speed>80){
    wheel_speed = 80;
  }

  if(error>0){
    wheel_direction = 1;
  }else if(error<0){
    wheel_direction = -1;
  }else if(error<20){
    wheel_direction = 0;
  }
  // Serial.println(wheel_speed);      // just to check the speed and direction in case you want to tune it
  // Serial.println(wheel_direction);
  prev_error = error;
}

void gyro(){                           // Function to calculate the angle along the Z-axis after every 10ms
  mpu.update();
  if((millis()-timer)>10){             // print data every 10ms
  bot_angle = mpu.getAngleZ();
  Serial.println(bot_angle);
  timer = millis();  
  }
}

void motorControl(){                  // Function for controlling the motors using RoboClaw 
  if(wheel_direction == 1){
    roboclaw1.ForwardM1(add1, wheel_speed);
    roboclaw1.ForwardM2(add1, wheel_speed);
    roboclaw2.ForwardM2(add2, wheel_speed);

  }else if(wheel_direction == -1){
    roboclaw1.BackwardM1(add1, wheel_speed);
    roboclaw1.BackwardM2(add1, wheel_speed);
    roboclaw2.BackwardM2(add2, wheel_speed);  

  }else if(wheel_direction == 0){
    roboclaw1.ForwardM1(add1, 0);
    roboclaw1.ForwardM2(add1, 0);
    roboclaw2.ForwardM2(add2, 0);

  }
}


void loop() {
  gyro();
  gyroPID();
  motorControl();
}
