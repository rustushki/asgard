#include "externals.h"
#include "Screen.h"
#include "GraphicsEngine.h"

/*
#include "MessageRouter.h"
#include "Console.h"
#include "MessageFactory.h"
#include "Database.h"
#include "Map.h"
*/

GraphicsEngine* ge;

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
}

int main(int argc, char**argv)
{
   initExternal();
   initModel();

   boost::function<void()> viewMethod = boost::bind(&GraphicsEngine::initScreen, ge);

   boost::thread contThread(controller);
   boost::thread viewThread(viewMethod);

   contThread.join();
   viewThread.join();

   return 0;
}
