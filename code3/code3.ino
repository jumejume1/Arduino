#include "GantryXYZ.h"

#define right_sw  13
#define left_sw   11

#define potmeterPin A0

GantryXYZClasses gantryXYZ;

volatile boolean rightPress = false;
volatile boolean leftPress  = false;

uint8_t rightBtnState = 0;
uint8_t lastRightBtnState=0;


uint8_t leftBtnState = 0;
uint8_t lastLeftBtnState=0;

unsigned int delay_time=500;

void setup() {
  
    pinMode(right_sw, INPUT_PULLUP);
    pinMode(left_sw, INPUT_PULLUP);
 
    Serial.begin(9600);  // open coms
    gantryXYZ.setFeedrate(1000);  // set default speed
  
}

void loop() {

    /* 
     *  Home limit switch Hall Effect sensor normal = 1
     *                                       Hit    = 0
     *                                       
     */

      int p = analogRead(potmeterPin);
      delay_time = map(p,0,1023,1500,50) ;

     if( !gantryXYZ.is_move){

             

           //   Serial.println( delay_time );
            
             checkIfRightIsPressed();
             
             checkIfLeftIsPressed();

             if( rightPress){
                 rightPress = false;
                 gantryXYZ.prepareMove(-1000,0,0);
             }
            
             else if(leftPress){
              
                  leftPress = false;
                  gantryXYZ.prepareMove( 450,0,0);
             }
     }
     
     
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
  

   gantryXYZ.move(delay_time);
   
   
}

void checkIfRightIsPressed()
{
  rightBtnState     = digitalRead(right_sw);
  if (rightBtnState != lastRightBtnState) 
  {
    if (rightBtnState == 0) {
         rightPress=true;
    }
    delay(50);
  }
   lastRightBtnState = rightBtnState;
}

void checkIfLeftIsPressed()
{
  leftBtnState     = digitalRead(left_sw);
  
  if (leftBtnState != lastLeftBtnState) 
  {
    if (leftBtnState == 0) {
         leftPress=true;
    }
    delay(50);
  }
   lastLeftBtnState = leftBtnState;
}

