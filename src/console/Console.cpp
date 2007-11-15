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
