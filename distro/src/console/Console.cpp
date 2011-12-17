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
#include "Console.h"
#include "Asgard.h"

Console* Console::instance = NULL;

Console* Console::getInstance() {
   LOG(INFO) << "Console starting ...";
   
   if (Console::instance == NULL) {

      if (Asgard::argc > 1) {
         std::string arg1 = Asgard::argv[1];
         // Interactive Shell
         if (arg1.compare("-i") == 0) {
            Console::instance = new Console(true);

         // Script
         } else {
            Console::instance = new Console(arg1);
         }
      } else {
         Console::instance = new Console(false);
      }

   }

   return Console::instance;
}

Console::Console(std::string filename) {
   this->code = "";
   this->filename = filename;
   this->consoleType = CONSOLETYPE_FILE;
}

Console::Console() {
   this->code = "";
   this->filename = "";
   this->consoleType = CONSOLETYPE_STDIN;
}

Console::Console(bool interactive) {
   this->code = "";
   this->filename = "";

   if (interactive == true)
      this->consoleType = CONSOLETYPE_INTERACTIVE;
   else
      this->consoleType = CONSOLETYPE_STDIN;
}

Console::~Console() {
}

void Console::inputLoop() {
   // If a filename is provided, read that file in and execute it.
   if (this->filename != "")
   {
      this->execPython();
   }

   // Then switch to console input as Asgard is intended to continue running.

   if (this->consoleType == CONSOLETYPE_INTERACTIVE)
      this->prompt();

   while(1)
   {
      int code = this->readCode();
      if (code == Console::FEOF)
      {
         if (this->consoleType == CONSOLETYPE_INTERACTIVE)
         {
            exit(1);
         }
      }

      if (code == Console::CONTINUE_READ)
      {
         if (this->consoleType == CONSOLETYPE_INTERACTIVE)
            this->prompt();
         continue;
      }

      boost::this_thread::sleep(boost::posix_time::milliseconds(10));
   }
}

int Console::readCode() {
   if (!feof(stdin))
   {
      char input[1024];

      char* res = fgets(input, 1024, stdin);

      if (res == NULL && strcmp(input, "") != 0) {
         LOG(ERROR) << "Got error when reading script from STDIN: " << ferror(stdin);
      }

      this->code += input;

      // Interactive Mode: Exec Python each CR.
      if (this->consoleType == CONSOLETYPE_INTERACTIVE)
      {
         // TODO: Handle Failure.
         this->execPython();
      }
      // STDIN Mode: Accumulate all input until stdin is closed.
      else if (!feof(stdin))
      {
         return Console::CONTINUE_READ;
      }
      // STDIN Mode: When stdin stream is closed, execute.
      else
      {
         // TODO: Handle Failure.
         this->execPython();
      }

      // Continue reading input?
      if (feof(stdin))
         return Console::FEOF;
      else
         return Console::CONTINUE_READ;
   }

   return Console::FEOF;
}

int Console::execPython() {
   bool success = false;

   if (this->consoleType == CONSOLETYPE_FILE)
   {
      FILE *fp = fopen(this->filename.c_str(), "r");
      success = PyRun_SimpleFile(fp, this->filename.c_str());
      fclose(fp);
   }
   else
   {
      success = (PyRun_SimpleString(this->code.c_str()) == 0);
   }

   this->code = "";
   if (success)
      return Console::PYTHON_SUCCESS;

   return Console::PYTHON_FAIL;
}

void Console::prompt() {
   std::cout << "> ";
}
