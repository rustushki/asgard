#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "AsgardGrammar.h" 

using std::string;

class Parser
{
   public:
      static Parser* getInstance();
      static void deleteInstance();

      bool parseCommand(string command);

   private:
      Parser();
      ~Parser();

      static Parser* instance;
      AsgardGrammar grammar;



};

#endif // PARSER_H
