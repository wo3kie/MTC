#include "headers/ph.hpp"

#include "headers/parser.hpp"

namespace Syntax
{

ParserWrapper::ParserWrapper(
	std::istream* _in,
	std::ostream* _out
)
	: BisonParser( _in, _out )
{
}

}
