#include "externals.h"
#include "Screen.h"
#include "GraphicsEngine.h"
#include "Database.h"
#include "Console.h"
#include "Map.h"

int    argCount;
char** argStrings;

GraphicsEngine* ge;
      Database* db;
       Console* cl;
           Map* ma;

void controller() {
   cl->inputLoop();
}

void initExternal() {
   // Initialize SDL
   SDL_Init(SDL_INIT_VIDEO);
   SDL_SetVideoMode(Screen::WIDTH, Screen::HEIGHT, 16, SDL_DOUBLEBUF);

   // Initialize Google Logger.
   google::InitGoogleLogging("asgard");

   // Initialize Python
   Py_Initialize();

   if (Py_IsInitialized() != true) {
      std::cout << "Python failed to initialize." << std::endl;
      exit(0);
   }

   Py_InitModule("asgard", AsgardMethods);
   Py_InitModule("map",    MapMethods);

}

void killExternals() {
   Py_Finalize();
   SDL_Quit();
}

void initModel() {
   ge = GraphicsEngine::getInstance();
   db =       Database::getInstance();
   cl =        Console::getInstance(argCount, argStrings);
   ma =            Map::getInstance();
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
   argCount   = argc;
   argStrings = argv;

   initExternal();
   initModel();
   startThreads();

   // Wait for the User to Kill Vear.

   killExternals();

   return 0;
}
