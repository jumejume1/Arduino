#include "GantryXYZ.h"

#define right_sw  13
#define left_sw   11

GantryXYZClasses gantryXYZ;

volatile boolean rightPress = false;
volatile boolean leftPress  = false;



unsigned int delay_time=300;

int move_position=0;

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

     

     if( !gantryXYZ.is_move){

           //   Serial.println( delay_time );

            leftPress = false;
            rightPress = false; 
             checkIfRightIsPressed();
             
             checkIfLeftIsPressed();
             

             if( rightPress){
                
                 move_position -= 10;
                 gantryXYZ.prepareMove(move_position,0,0);
             }
            
             else if(leftPress){
              
                  
                  move_position+=10;
                  gantryXYZ.prepareMove( move_position,0,0);
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
  if ( digitalRead(right_sw) == LOW  ) 
  {
     rightPress=true;
       
  }
}

void checkIfLeftIsPressed()
{
  
  if ( digitalRead(left_sw) == LOW  ) 
  {
     leftPress=true;
       
  }
   
}

