#define LM1 10    // left motor
#define LM2 11    // left motor
#define RM1 9     // right motor
#define RM2 8     // right motor
#define trigpin 3  // Trigger pin of HC-SR04
#define echopin 4  // Echo pin of HC-SR04

long duration;     // declaring variable to store time duration
int distance;      // declaring variable to store distance as int(integer)
void setup()
{
  pinMode(LM1, OUTPUT);           //Initialising motor pin of Left motor as Output
  pinMode(LM2, OUTPUT);           //Initialising motor pin of Left motor as Output
  pinMode(RM1, OUTPUT);           //Initialising motor pin of Right motor as Output
  pinMode(RM2, OUTPUT);           //Initialising motor pin of Right motor as Output
  
  pinMode(trigpin, OUTPUT);       //Initialising trig pin as Output
  pinMode(echopin, INPUT);        //Initialising echo pin as Input to capture reflected waves
  
  Serial.begin(9600);             //Serial.begin to display the distance on Serial Monitor with baudrate of 9600
}

void loop(){
  digitalWrite(trigpin, LOW);     //Sending low wave for 5 ms to avoid collision in serial monitor
  delay(5);
  digitalWrite(trigpin, HIGH);    //turn on the Trigger to generate pulse
  delay(10);                      // keep the trigger "ON" for 10 ms to generate pulse for 10 ms
  digitalWrite(trigpin, LOW);     // Turn off the pulse trigger to stop pulse generation


    // If pulse reached the receiver echoPin
    // become high Then pulseIn() returns the
    // time taken by the pulse to reach the
    // receiver
  duration = pulseIn(echopin, HIGH); 
  
  distance = (duration*0.034)/2;        // Expression to Calculate distance using Time
  Serial.println("Distance: ");         // Printing the value of distance calculated by the sensor on serial monitor
  Serial.println(distance);
  delay(100);
 
  if(distance>=9){                       // condition if distance is greater than 9cm then move forward
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  }
  else if(distance<=8){                  //else if distance <=8cm then,
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);                // Stop for 0.5s
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  delay(500);
  
  digitalWrite(LM1, HIGH);               
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);               // Backward for 2s
  digitalWrite(RM2, LOW);
  delay(2000);
  
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);                // Stop for 1s
  digitalWrite(RM2, LOW);
  delay(1000);
  
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);                // Turn Left for 1.4s
  digitalWrite(RM2, HIGH);
  delay(1400);
  }

}
 
