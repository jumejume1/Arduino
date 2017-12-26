#include "GantryXYZ.h"

GantryXYZClasses gantryXYZ;

void setup() {
  
  // put your setup code here, to run once:
    Serial.begin(9600);  // open coms
    gantryXYZ.setFeedrate(1000);  // set default speed
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
    while(Serial.available() > 0) {  // if something is available
    char c=Serial.read();  // get it
    Serial.print(c);  // repeat it back so I know you got the message

    gantryXYZ.storeBuffer( c );
  
    if(c=='\n') {
      // entire message received
      gantryXYZ.storeBuffer( c );
      Serial.print(F("\r\n"));  // echo a return character for humans
      gantryXYZ.processCommand();  // do something with the command
      
    }
  }

   gantryXYZ.move();
   
}
