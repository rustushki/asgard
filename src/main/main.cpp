//============================================================================
// Name        : Asgard.cpp
// Author      : Ben Markwardt
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "externals.h"
#include "MessageRouter.h"
#include "Console.h"
#include "MessageFactory.h"
#include "Database.h"
#include "GraphicsEngine.h"
#include "Map.h"

int main(int argc, char**argv)
{
   
   // Open MessageRouter first always.
   MessageRouter* mr = MessageRouter::getInstance();
   
   google::InitGoogleLogging("asgard");


   LOG(INFO) << "Loading Asgard SystemComponents.";

   SystemComponent* dbCont  = Database::getInstance();
   SystemComponent* graphicsEngine = GraphicsEngine::getInstance();
   SystemComponent* map = Map::getInstance();

   dbCont->open();
   graphicsEngine->open();
   map->open();

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
