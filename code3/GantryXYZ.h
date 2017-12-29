/*
   GantryClasses.h

   Author : Jamorn Saksommon
   Class  
  // please see http://www.github.com/MarginallyClever/GcodeCNCDemo for more information.

   Modifly date: 27.01.2017
*/

#ifndef Gantry_XYZ_h
#define Gantry_XYZ_h

#include "GantryClasses.h"
#include "GCODEClasses.h"


class GantryXYZClasses : public GantryClasses , public GCODEClasses
{
        
      public:
      	        
      GantryXYZClasses();

      void processCommand();

};

#endif
