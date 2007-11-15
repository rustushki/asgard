#ifndef CONSOLE_H
#define CONSOLE_H

#include "Parser.h"

class Console
{
   public:
      Console();
      ~Console();
      int listen();

   private:
      Parser* parser;

      bool readline();
      void prompt();


};

#endif // CONSOLE_H
