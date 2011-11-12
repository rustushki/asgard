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

   SystemComponent* db = Database::getInstance();
   SystemComponent* ge = GraphicsEngine::getInstance();
   SystemComponent* ma = Map::getInstance();
   SystemComponent* cn = Console::getInstance(argc, argv);

   db->open();
   ge->open();
   ma->open();
   cn->open();

   // Wait for user to kill Vear.
   while(1) {
      sleep(10);
   }

   return 0;
}
