#ifndef __SYNTAX_PARSER_HPP__
#define __SYNTAX_PARSER_HPP__

#include "headers/semantic_value_stack.hpp"
#include "headers/scanner.hpp"
#include "headers/bison_parser.hpp"

namespace Syntax
{

class ParserWrapper
	: public BisonParser
	, public boost::noncopyable
{
public:
	ParserWrapper( std::istream* _in, std::ostream* _out );
};

typedef ParserWrapper Parser;

}

#endif
