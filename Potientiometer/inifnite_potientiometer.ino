//////////////////////////////////////
int counter =0;                   //Initializing Variables
int lastpotval;


void setup() { 
 Serial.begin(9600);
 lastpotval = analogRead(A3);      // Initially reading the value of the Potientiometer and storing it
}


void loop() { 
int currentpotval = analogRead(A3);                 //Taking the current potientiometer reading and storing it
if(currentpotval==1023 || currentpotval>1020){      //Setting the end condition as the analog pin has a max value range of 1023
  while(analogRead(A3)!=0){
    counter = counter;
    Serial.println(counter);
  }
}

if(lastpotval < currentpotval){                          // condition for turning the knob of potientiometer in +ve direction(clockwise)
  counter+=(currentpotval-lastpotval);             
}
else if(lastpotval==1023 &&  currentpotval >=0){         // end condition during clockwise direction 
  counter++;
}
else if(lastpotval == 0 && currentpotval <= 1023){       // end condition for anti-clockwise direction
  counter--;
}
else if(lastpotval>currentpotval){                       // condition for turning the knob of potientiometer in -ve direction(anti-clockwise)
  counter+=(currentpotval-lastpotval);
}

  Serial.println(counter);
  lastpotval = currentpotval;                            // updating the last potientiometer value as current everytime just before one loop ends 
}
