#include "externals.h"
#include "Screen.h"

/*
#include "MessageRouter.h"
#include "Console.h"
#include "MessageFactory.h"
#include "Database.h"
#include "GraphicsEngine.h"
#include "Map.h"
*/

void controller() {
   std::cout << "Controller.";
}

void view() {
   std::cout << "View.";
}

int main(int argc, char**argv)
{

   // Initialize SDL
   SDL_Init(SDL_INIT_VIDEO);
   SDL_SetVideoMode(Screen::WIDTH, Screen::HEIGHT, 16, SDL_DOUBLEBUF);

   // Initialize Google Logger.
   google::InitGoogleLogging("asgard");

   boost::thread contThread(controller);
   boost::thread viewThread(view);

   contThread.join();
   viewThread.join();

   return 0;
}
