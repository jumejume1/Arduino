/*
   GCODEClasses.cpp

   Author : Jamorn Saksommon
   Class  

   Modifly date: 03.02.2017
*/

#include <Arduino.h>
#include "GCODEClasses.h"


GCODEClasses::GCODEClasses(){
     sofar = 0;
}

void GCODEClasses::storeBuffer( char c){ 

    if( c == '\n'){
        buffer[sofar]=0;
        return;
    }

    if(sofar<MAX_BUF-1) buffer[sofar++] = c;
       

}
float GCODEClasses::parsenumber(char code,float val){

       char *ptr=buffer;
  while(ptr && *ptr && ptr<buffer+sofar) {
    if(*ptr==code) {
    
      return atof(ptr+1);
    }
    ptr=strchr(ptr,' ')+1;
  }
  return val;

}

void GCODEClasses::ready(){
      sofar=0;
}
void GCODEClasses::processCommand(){}