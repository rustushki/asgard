#ifndef ASGARDGRAMMAR_H
#define ASGARDGRAMMAR_H

#define BOOST_SPIRIT_THREADSAFE
#include <boost/spirit.hpp>
#include "MessageFactory.h"

using boost::spirit::grammar;
using boost::spirit::str_p;
using boost::spirit::uint_p;
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

         boundingbox_parms    =    uint_p[&MessageFactory::makeLoadBoundingBox]
                                   ;
      }

      rule<ScannerT> command;
      rule<ScannerT> load_phrase;
      rule<ScannerT> loadable_object_type;
      rule<ScannerT> boundingbox;
      rule<ScannerT> boundingbox_parms;

      rule <ScannerT> const&
      start() const {return command;};
      
   };
};

#endif // ASGARDGRAMMAR_H
