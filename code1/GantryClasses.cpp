/*
   GantryClasses.cpp
   Author : Jamorn Saksommon
   Class  
  // please see http://www.github.com/MarginallyClever/GcodeCNCDemo for more information.

   Modifly date: 27.01.2017
*/
#include <Arduino.h>
#include "GantryClasses.h"

GantryClasses::GantryClasses(){ 

       mode_abs  = 1; 
       feed_rate = 0;
       is_move   = false;
        
}

void GantryClasses::setFeedrate(float nfr){

 

  nfr = nfr*STEPS_PER_MM/60; 
  if( ( feed_rate==nfr ) || (nfr>MAX_FEEDRATE || nfr<MIN_FEEDRATE )  ) return;  // same as last time?  quit now.
  
  step_delay = MAX_FEEDRATE/nfr;
  feed_rate=nfr;

}

void GantryClasses::prepareMove( float newx,float newy,float newz  ){

       
       maxsteps=0;
       
       axis[AXIS_X].delta = (newx-px)*STEPS_PER_MM;
       axis[AXIS_Y].delta = (newy-py)*STEPS_PER_MM;
       axis[AXIS_Z].delta = (newz-pz)*STEPS_PER_MM;
   

       for(int i=0;i< num_axis ;++i) {
            axis[i].absdelta = abs( axis[i].delta );
            axis[i].over=0;
        if( maxsteps < axis[i].absdelta ) maxsteps = axis[i].absdelta;
      // set the direction once per movement
          digitalWrite( motors[i].dir_pin, axis[i].delta>0?HIGH:LOW);


        }

      delay_t = MAX_FEEDRATE/5000;
      accel = 1;
      steps_to_accel = delay_t - step_delay;

  if(steps_to_accel > maxsteps/2 ) 
    steps_to_accel = maxsteps/2;
    
   steps_to_decel = maxsteps - steps_to_accel;

   
  
  step_count = 0;
  prev_time  = 0;

  is_move    = maxsteps > 0;

  if( is_move){
      enableMotor();
  }
 /* 

  Serial.print("START ");
  Serial.println(delay_t);
  Serial.print("STOP ");
  Serial.println(step_delay);
  
  Serial.print("accel until ");
  Serial.println(steps_to_accel);  
  Serial.print("decel after ");
  Serial.println(steps_to_decel);  
  Serial.print("total ");
  Serial.println(maxsteps);  

  */
  
  //r.steps_to_accel = steps_to_accel;
  //r.steps_to_decel = steps_to_decel;
  

  setPosition(newx,newy,newz);
  
}
void GantryClasses::disableMotor(){

   int i;
  for(i=0;i<num_axis;++i) {  
    digitalWrite(motors[i].enable_pin,HIGH);
  }

}
void GantryClasses::enableMotor(){

  int i;
  for(i=0;i<num_axis;++i) {  
    digitalWrite(motors[i].enable_pin,LOW);
  }

}
void GantryClasses::setPosition(float npx,float npy,float npz){
         px = npx;
         py = npy;
         pz = npz;
         
}
void GantryClasses::move(){

  unsigned long curtime = micros();
  unsigned int _delay;

  if( is_move &&   ( (curtime - prev_time) >=  delay_t) ){

     prev_time = curtime;

     for(int j=0;j<num_axis;++j) {
           axis[j].over += axis[j].absdelta;

      if(  ( axis[j].over >= maxsteps ) ) {
            axis[j].over -= maxsteps;

        _delay = 100;    
        
        digitalWrite(motors[j].step_pin,HIGH);
        delayMicroseconds(_delay);
        digitalWrite(motors[j].step_pin,LOW);
        delayMicroseconds(_delay);
      }
    }

    if( step_count< steps_to_accel) {
      delay_t -= accel;
    }
    if( step_count>= steps_to_decel) {
          delay_t += accel;
    }

    step_count++;

    is_move = !(step_count >= maxsteps );

    if( !is_move ){
        disableMotor();
    }

  }

}