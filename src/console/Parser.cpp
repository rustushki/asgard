#define BOOST_SPIRIT_THREADSAFE
#include <boost/spirit.hpp>

#include "Parser.h"
#include "AsgardGrammar.h" 

using boost::spirit::space_p;
using boost::spirit::parse;

Parser * Parser::instance = NULL;
      
Parser* Parser::getInstance()
{
   if (instance == NULL)
      instance = new Parser();

   return instance;
}

void Parser::deleteInstance()
{
   delete instance;
}

Parser::Parser()
{
   // unspecified.
}

Parser::~Parser()
{
   // unspecified.
}

bool Parser::parseCommand(string command)
{
   bool valid;
   
   valid = parse(command.c_str(),this->grammar,space_p).full;

   return valid;

}
