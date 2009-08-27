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
#ifndef ASGARD_GRAMMAR_H
#define ASGARD_GRAMMAR_H

#define BOOST_SPIRIT_THREADSAFE
#include <boost/spirit.hpp>
#include "Message.h"
#include "MessageFactory.h"

using boost::spirit::grammar;
using boost::spirit::str_p;
using boost::spirit::int_p;
using boost::spirit::rule;

struct AsgardGrammar : public grammar<AsgardGrammar>
{
   // TODO:
   // Include state-information for a 
   // generic way of handling recognized
   // parameters.
   // ...

   template <typename ScannerT>
   struct definition
   {
      definition(AsgardGrammar const& self)
      {
         command              =    load_phrase
                                   ;

         load_phrase          =    str_p("load")
                                >> loadable_object_type
                                   ;
                                

         loadable_object_type =    boundingbox
                                   ;

         boundingbox          =    str_p("boundingbox")
                                >> boundingbox_parms
                                   ;

         boundingbox_parms    =    int_p[&MessageFactory::makeLoadBoundingBox]
                                   ;

      }

      rule<ScannerT> command;
      rule<ScannerT> load_phrase;
      rule<ScannerT> loadable_object_type;
      rule<ScannerT> boundingbox;
      rule<ScannerT> boundingbox_parms;

      rule <ScannerT> const&
      start() const {return command;};

      Message* generatedMsg;

   };
};

#endif // ASGARD_GRAMMAR_H