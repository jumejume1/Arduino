
#include <arduino.h>
#include "GantryXYZ.h"

GantryXYZClasses::GantryXYZClasses()
{
      num_axis  = 1;

      motors = new Motor[num_axis];
      axis   = new Axis[num_axis];
      
      // X
      motors[0].step_pin=5;
      motors[0].dir_pin=2;
      motors[0].enable_pin=8;
      motors[0].limit_switch_pin=7;
      /*
      // Y
      motors[1].step_pin=46;
      motors[1].dir_pin=48;
      motors[1].enable_pin=62;
      motors[1].limit_switch_pin=14;
      // Z
      motors[2].step_pin=26;
      motors[2].dir_pin=28;
      motors[2].enable_pin=24;
      motors[2].limit_switch_pin=18;

    
     */
  
  for(int i=0;i<num_axis;++i) {  
    // set the motor pin & scale
    pinMode(motors[i].step_pin,OUTPUT);
    pinMode(motors[i].dir_pin,OUTPUT);
    pinMode(motors[i].enable_pin,OUTPUT);
  }
  
  disableMotor();
  setPosition(0,0,0);
 
}
void GantryXYZClasses::processCommand(){

      int cmd = 1;

      switch(cmd) {
  case  0:
  case  1: { //  move


    setFeedrate( parsenumber('f',feed_rate));

    prepareMove( parsenumber('x',(mode_abs?px:0)) + (mode_abs?0:px),
                 parsenumber('y',(mode_abs?py:0)) + (mode_abs?0:py),
                 parsenumber('z',(mode_abs?pz:0)) + (mode_abs?0:pz)
                 
                           
                           );
                                      
    break;
    }
  case  2:
  case  4:  ;  break;  // dwell
  case 90: mode_abs=1; break;  // absolute mode
  case 91: mode_abs=0; break;  // relative mode
  case 92:  // set logical position
   
    break;
  default:  break;
  }

  ready();

}
