#include "Asgard.h"

Asgard* Asgard::instance = NULL;
int     Asgard::argc     = 0;
char**  Asgard::argv     = NULL;

Asgard* Asgard::getInstance() {
   if (Asgard::instance == NULL) {
      Asgard::instance = new Asgard();
   }

   return Asgard::instance;
}

Asgard::Asgard() {
   LOG(INFO) << "Initting Externals...";
   this->initExternal();

   LOG(INFO) << "Initting Model...";
   this->initModel();
}

void Asgard::initModel() {
   GraphicsEngine::getInstance();
   Database::getInstance();
   Map::getInstance();
   Console::getInstance();
}

void Asgard::controller() {
   // Block until View ungates the Controller.
   this->gate.lock();

   // The View is now ready.

   // Read from the Console.
   Console::getInstance()->inputLoop();
}

void Asgard::initExternal() {
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

Asgard::~Asgard() {
   Py_Finalize();
   SDL_Quit();
}

void Asgard::start() {
   // Gate the Controller Thread.
   this->gate.lock();

   // Activate the View Thread.
   boost::function<void()> viewMethod = boost::bind(&GraphicsEngine::play, GraphicsEngine::getInstance());
   boost::thread viewThread(viewMethod);

   // Activate the Controller Thread.
   boost::thread contThread(&Asgard::controller, this);

   // Wait for them to both to end.
   contThread.join();
   viewThread.join();
}


