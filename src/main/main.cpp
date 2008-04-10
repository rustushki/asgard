//============================================================================
// Name        : Asgard.cpp
// Author      : Ben Markwardt
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "AsgardThread.h"
#include "Console.h"

int main() 
{
   
   Console blah;
   
   blah.open();
   
   while(blah.isOpen())
   {
      // Do nothing
   }
   
   //AsgardThread asgardThread;
   
   //asgardThread.open(Console::);
   
   
   return 0;
}
