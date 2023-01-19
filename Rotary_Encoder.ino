#define CLK 2
#define DT 3
#define ledpin 6u
int counter =0;
int currentstateclk;
int laststateclk;
//int maxcount =0;
void setup(){
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(ledpin,OUTPUT);
  Serial.begin(9600);
  

  laststateclk = digitalRead(CLK);
}
void loop(){
  currentstateclk = digitalRead(CLK);
  if(currentstateclk != laststateclk){
    if(digitalRead(DT)!= currentstateclk){
      counter ++;  
    
    }
    else{
      counter --;
     
    }
   Serial.println("Counter: ");
   Serial.println(counter);
  
  }
  laststateclk = currentstateclk;
 }
