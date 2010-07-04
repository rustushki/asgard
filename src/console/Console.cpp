/*****************************************************************************
 * Copyright (c) 2007 Russ Adams, Sean Eubanks, Asgard Contributors
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
#include <python2.6/Python.h>
#include <iostream>
#include <string>
#include "Console.h"
#include "ConsolePython.h"
#include <boost/bind.hpp>

using std::getline;
using std::cin;
using std::cout;
using std::string;
using std::endl;

Console::Console(string filename) : SystemComponent("console")
{
   this->sessionLog = "";
   this->code = "";
   this->filename = filename;
}

Console::Console() : SystemComponent("console")
{
   this->sessionLog = "";
   this->code = "";
   this->filename = "";
}

Console::~Console()
{
}

bool Console::open()
{
   bool status = true;

	Py_Initialize();

	if (Py_IsInitialized() != true)
	{
		cout << "python not initialized." << endl;
      return SystemComponent::close();
	}

	Py_InitModule("asgard", AsgardMethods);

   
   this->thread->open(boost::bind(&Console::inputLoop, this));
   
   status = SystemComponent::open();
   
   return status;
}

bool Console::close()
{
   bool status = true;

   Py_Finalize();
   
   if(!this->thread->isClosed())
   {
      this->thread->close();
   }
   
   status = SystemComponent::close();
   
   return status;
}

void Console::inputLoop()
{
   // If a filename is provided, read that file in and execute it.
   if (this->filename != "")
   {
      this->execPython();
   }

   // Then switch to console input as Asgard is intended to continue running.
   while(1)
   {
      this->prompt();

      if (this->readCode() != true)
      {
         // output session log
         cout << this->sessionLog;
         exit(1);
      }

      this->listen(10);
   }
}

bool Console::readCode()
{
   char input[1024];
   fgets(input, 1024, stdin);

   if (!feof(stdin))
   {
      // Copy the input.  Otherwise when the stream is closed, our read in data
      // becomes gibberish.
      char tempbuff[1024];
      strcpy(tempbuff, input);

      // Concatentate to session log so far.
      this->sessionLog += string(tempbuff);
      this->code += input;
      return this->execPython();
   }

   return false;
}

bool Console::execPython()
{
   bool success = false;

   if (this->filename != "")
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
   return success;
}

void Console::prompt()
{
   cout << "> ";
}

bool Console::interpretMessage(Message* msg)
{
   bool messageHandled = false;
   if (msg->header.type == MESSAGE_TYPE_PRINT_STRING)
   {
      std::cout << msg->data.printString.output << std::endl;
      messageHandled = true;
   }
   return messageHandled;
}
