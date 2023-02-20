//////////////////////////////////////
int counter =0;
int lastpotval;

void setup() { 
 Serial.begin(9600);
 lastpotval = analogRead(A3);
}

void loop() { 
int currentpotval = analogRead(A3);
if(currentpotval==1023 || currentpotval>1020){
  while(analogRead(A3)!=0){
    counter = counter;
    Serial.println(counter);
  }
}


if(lastpotval < currentpotval){
  counter+=(currentpotval-lastpotval);
}
else if(lastpotval==1023 &&  currentpotval >=0){
  counter++;
}
else if(lastpotval == 0 && currentpotval <= 1023){
  counter--;
}
else if(lastpotval>currentpotval){
  counter+=(currentpotval-lastpotval);
}

  Serial.println(counter);
  lastpotval = currentpotval;
}
