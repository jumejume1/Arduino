// defines pins numbers
const int stepPin = 5; 
const int dirPin = 2; 
const int enPin = 8;
const int limitPin = 7;
void setup() {

  pinMode(limitPin,INPUT);
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  
}
void loop() {
  
 if( digitalRead(limitPin) == HIGH){
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
 }
  
}
