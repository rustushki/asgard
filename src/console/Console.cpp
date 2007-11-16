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

using std::getline;
using std::cin;
using std::cout;
using std::string;

Console::Console()
{
   this->parser = Parser::getInstance();
}

Console::~Console()
{
   Parser::deleteInstance();
}

int Console::listen()
{
   this->prompt();

   while (this->readline())
      this->prompt();

   return 0;
}

bool Console::readline()
{
   // TODO: 
   // Add more error handling 
   // for reading input
   string line;
   getline(cin, line);

   if (cin.eof())
      return false;
   else
      return this->parser->parseCommand(line);
}

void Console::prompt()
{
   cout << "> ";
}
