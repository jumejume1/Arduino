int speakerOut = 9;
void setup() {
  // put your setup code here, to run once:
  pinMode(speakerOut,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    beep();
    delay(500);
}
void beep(){
  
   for( int i = 0; i<500;i++){
      digitalWrite(speakerOut , HIGH);
      delayMicroseconds(500);
      digitalWrite(speakerOut, LOW );
      delayMicroseconds(500);
   }
  
}

