#include "GantryXYZ.h"

#define home_sw 13
#define item1_sw 12
#define item2_sw 11

GantryXYZClasses gantryXYZ;

volatile boolean homePress  = false;
volatile boolean item1Press = false;
volatile boolean item2Press = false;

uint8_t homeBtnState = 0;
uint8_t lastHomeBtnState=0;

uint8_t item1BtnState = 0;
uint8_t lastItem1BtnState=0;

uint8_t item2BtnState = 0;
uint8_t lastItem2BtnState=0;

void setup() {
  
    pinMode(home_sw, INPUT_PULLUP);
    pinMode(item1_sw, INPUT_PULLUP);
    pinMode(item2_sw, INPUT_PULLUP);
 
    Serial.begin(9600);  // open coms
    gantryXYZ.setFeedrate(1000);  // set default speed
  
}

void loop() {

    /* 
     *  Home limit switch Hall Effect sensor normal = 1
     *                                       Hit    = 0
     *                                       
     */

     if( !gantryXYZ.is_move){
            
             checkIfHomeIsPressed();
             checkIfItem1IsPressed();
             checkIfItem2IsPressed();

             if( homePress){
                 homePress = false;
                 gantryXYZ.prepareMove(-1000,0,0);
             }
             else if(item1Press){
                 item1Press = false;
                 gantryXYZ.prepareMove( 200,0,0);
             }
             else if(item2Press){
              
                  item2Press = false;
                  gantryXYZ.prepareMove( 350,0,0);
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
  

   gantryXYZ.move();
   
   
}

void checkIfHomeIsPressed()
{
  homeBtnState     = digitalRead(home_sw);
  if (homeBtnState != lastHomeBtnState) 
  {
    if (homeBtnState == 0) {
         homePress=true;
    }
    delay(50);
  }
   lastHomeBtnState = homeBtnState;
}
void checkIfItem1IsPressed()
{
  item1BtnState     = digitalRead(item1_sw);
  if (item1BtnState != lastItem1BtnState) 
  {
    if (item1BtnState == 0) {
         item1Press=true;
    }
    delay(50);
  }
   lastItem1BtnState = item1BtnState;
}
void checkIfItem2IsPressed()
{
  item2BtnState     = digitalRead(item2_sw);
  
  if (item2BtnState != lastItem2BtnState) 
  {
    if (item2BtnState == 0) {
         item2Press=true;
    }
    delay(50);
  }
   lastItem2BtnState = item2BtnState;
}

