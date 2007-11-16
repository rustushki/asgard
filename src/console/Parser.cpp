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
