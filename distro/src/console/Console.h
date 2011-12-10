/*****************************************************************************
 * Copyright (c) 2011 Russ Adams, Sean Eubanks, Asgard Contributors
 * This file is part of Asgard.
 * 
 * Asgard is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Asgard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License
 * along with Asgard; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 ****************************************************************************/
#ifndef CONSOLE_H
#define CONSOLE_H

#include "ConsoleType.h"
#include "ConsolePython.h"
#include "externals.h"


using std::string;

class Console
{
   public:
      static Console* getInstance(int argc, char** argv);
      ~Console();

      void inputLoop();
   private:
      static Console* instance;

      Console();
      Console(bool interactive);
      Console(string filename);

      int readCode();
      int execPython();
      void prompt();

      string code;
      string sessionLog;
      string filename;

      ConsoleType consoleType;
   
      static const int CONTINUE_READ  = 100;
      static const int PYTHON_SUCCESS = 200;
      static const int PYTHON_FAIL    = 300;
      static const int FEOF           = 400;
};

#endif // CONSOLE_H
