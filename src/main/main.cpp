//============================================================================
// Name        : Asgard.cpp
// Author      : Ben Markwardt
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <boost/bind.hpp>

#include "MessageRouter.h"
#include "Console.h"
#include "MessageFactory.h"
#include "Database.h"
#include "GraphicsEngine.h"
#include "unistd.h"

int main(int argc, char**argv)
{
   
   // Open MessageRouter first always.
   MessageRouter* mr = MessageRouter::getInstance();
   
   SystemComponent* dbCont  = Database::getInstance();
   SystemComponent* graphicsEngine = GraphicsEngine::getInstance();

   dbCont->open();
   graphicsEngine->open();

   // TODO: make ready() instructions for SystemComponent's so that there is
   // not a race condition here.  Explanation: Screen in GraphicsEngine *MUST*
   // be initialized before many SDL calls will work properly.  Subsequent
   // calls to the GraphicsEngine *NEED* to wait until GraphicsEngine is
   // fininished loading.  This sleep is a work around:
   sleep(2);

   SystemComponent* console;
   char script_fn[50];
   if (argc > 1)
   {
	  // Interactive Shell
	  if (strcmp(argv[1], "-i") == 0)
	  {
          console = new Console(true);
	  }
	  else
	  {
		  strcpy(script_fn, argv[1]);
          console = new Console(std::string(script_fn));
	  }
   }
   else
      console = new Console(false);

   console->open();

   // Wait for user to kill Vear.
   while(1)
      sleep(10);
   
   return 0;
}
