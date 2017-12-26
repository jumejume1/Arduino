/*
   GantryClasses.h
   Class  
  // please see http://www.github.com/MarginallyClever/GcodeCNCDemo for more information.

   Modifly date: 27.01.2017
*/

#ifndef Gantry_Classes_h
#define Gantry_Classes_h


#define STEPS_PER_MM         (40)  
#define MAX_FEEDRATE         (1000000)
#define MIN_FEEDRATE         (1)

#define  AXIS_X  0
#define  AXIS_Y  1
#define  AXIS_Z  2   
  

typedef struct {
  int step_pin;
  int dir_pin;
  int enable_pin;
  int limit_switch_pin;
} Motor;

// for line()
typedef struct {
  long delta;  // number of steps to move
  long absdelta;
  long over;  // for dx/dy bresenham calculations
} Axis;



class GantryClasses 
{
        public:
          bool      is_move; 
          uint8_t   num_axis; 
          float feed_rate;  // human version
          long  step_delay; 
          unsigned long  delay_t;
          long  maxsteps;
          long  step_count;
          long  accel;
          float px,py,pz,pg;

          long steps_to_accel;
          long steps_to_decel;

          unsigned long prev_time;

          char  mode_abs; //absolute mode;

          Axis *axis;  // for move()
          Motor *motors;

         GantryClasses(); 

         void setFeedrate( float nfr);
         void setPosition(float npx,float npy,float npz);
         void prepareMove( float newx,float newy,float newz   );
         void move();

         void disableMotor();
         void enableMotor();

};

#endif
