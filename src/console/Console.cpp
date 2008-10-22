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
#include <iostream>
#include <string>
#include "Console.h"
#include "Parser.h"
#include <boost/bind.hpp>

using std::getline;
using std::cin;
using std::cout;
using std::string;
using std::endl;

Console::Console() : SystemComponent("console")
{
   this->parser = Parser::getInstance();
}

Console::~Console()
{
   Parser::deleteInstance();
}

bool Console::open()
{
   bool status = true;
   
   this->thread->open(boost::bind(&Console::inputLoop, this));
   
   status = SystemComponent::open();
   
   return status;
}

bool Console::close()
{
   bool status = true;
   
   if(!this->thread->isClosed())
   {
      this->thread->close();
   }
   
   status = SystemComponent::close();
   
   return status;
}

void Console::inputLoop()
{
   this->prompt();

   // Only listen if the parser returned success.
   if (this->readline() == true)
      this->listen();
}

bool Console::readline()
{
   // TODO: 
   // Add more error handling 
   // for reading input
   string line;
   getline(cin, line);

   // Handle Ctrl+D
   // TODO
   // More general way of exitting.
   if (cin.eof())
      exit(1);
   else
      return this->parser->parseCommand(line);
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
