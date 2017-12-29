/*
   GCODEClasses.h

   Author : Jamorn Saksommon
   Class  
  

   Modifly date: 03.02.2017
*/

#ifndef GCODE_Classes_h
#define GCODE_Classes_h

#define MAX_BUF              (20)  // What is the longest message Arduino can store?

class GCODEClasses 
{
        public:
          char buffer[MAX_BUF]; 
          int sofar;
          GCODEClasses(); 
          void storeBuffer( char);
          float parsenumber(char code,float val);
          void ready();
          virtual  void processCommand() =0;
};

#endif
