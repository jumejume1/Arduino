#include "GantryXYZ.h"

GantryXYZClasses gantryXYZ;

int state = 0;

void setup() {
  
    Serial.begin(9600);  //  Default connection rate for my BT module
    gantryXYZ.setFeedrate(1000);  // set default speed

    // When Start move to Home
    gantryXYZ.prepareMove(-1000,0,0);
   
}

void loop() {

    /* 
     *  Home limit switch Hall Effect sensor normal = 1
     *                                       Hit    = 0
     *                                       
     */

     if( !gantryXYZ.is_move){

             state = 0 ;
             if(Serial.available() > 0)
                  state = Serial.read();
            
             if( state == 50){                                        
                 
                 gantryXYZ.prepareMove(-1000,0,0);
             }
             else if(state == 49){
                               
                  gantryXYZ.prepareMove( 400,0,0);
             }
     }
     
     
     gantryXYZ.move();
   
   
}



