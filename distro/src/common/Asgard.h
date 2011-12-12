#ifndef ASGARD_H
#define ASGARD_H

#include "externals.h"
#include "Screen.h"
#include "Console.h"
#include "GraphicsEngine.h"
#include "Database.h"
#include "Map.h"
#include "ConsolePython.h"

class Asgard {
   public:
      static Asgard* getInstance();
      ~Asgard();

      void start();

      boost::mutex gate;

      static char** argv;
      static int argc;

   private:
      static Asgard* instance;

      Asgard();
      void initExternal();
      void initModel();
      void controller();
};

#endif//ASGARD_H
