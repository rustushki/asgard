//============================================================================
// Name        : Asgard.cpp
// Author      : Ben Markwardt
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <boost/bind.hpp>

#include "MessageRouter.h"
//#include "Console.h"
#include "Database.h"
#include "GraphicsEngine.h"
#include "unistd.h"

int main() 
{
   
   MessageRouter* mr = MessageRouter::getInstance();
   //SystemComponent* console = new Console();
   SystemComponent* dbCont  = Database::getInstance();
   SystemComponent* graphicsEngine = GraphicsEngine::getInstance();

   dbCont->open();
   //console->open();
   graphicsEngine->open();
   
   // load drawables
   // fish out drawables and animations loaded into memory.
   // graphics engine will do something with those.

   while(1)
      sleep(10);
   
   return 0;
}
