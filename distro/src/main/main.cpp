#include "externals.h"
#include "Screen.h"
#include "GraphicsEngine.h"
#include "Database.h"

/*
#include "MessageRouter.h"
#include "Console.h"
#include "MessageFactory.h"
#include "Map.h"
*/

GraphicsEngine* ge;
Database      * db;

void controller() {
   std::cout << "Controller.";
}

void initExternal() {
   // Initialize SDL
   SDL_Init(SDL_INIT_VIDEO);
   SDL_SetVideoMode(Screen::WIDTH, Screen::HEIGHT, 16, SDL_DOUBLEBUF);

   // Initialize Google Logger.
   google::InitGoogleLogging("asgard");
}

void initModel() {
   ge = GraphicsEngine::getInstance();
   db =       Database::getInstance();
}

void startThreads() {
   boost::function<void()> viewMethod = boost::bind(&GraphicsEngine::play, ge);

   boost::thread contThread(controller);
   boost::thread viewThread(viewMethod);

   contThread.join();
   viewThread.join();
}

int main(int argc, char**argv)
{
   initExternal();
   initModel();
   startThreads();

   return 0;
}
