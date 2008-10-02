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
#include "Console.h"
#include "Database.h"
#include "unistd.h"

int main() 
{
   
   MessageRouter* mr = MessageRouter::getInstance();
   SystemComponent* console = new Console();
   SystemComponent* dbCont  = Database::getInstance();

   dbCont->open();
   console->open();

   while(1)
      sleep(10);
   
   //AsgardThread asgardThread;
   //asgardThread.open(Console::);
   
   
   return 0;
}
