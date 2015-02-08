#ifndef __FRAMEWORK_APPLICATION_HPP__
#define __FRAMEWORK_APPLICATION_HPP__

#include "headers/semantic_value_stack.hpp"
#include "headers/scanner.hpp"
#include "headers/parser.hpp"

namespace Framework
{

class Application
	: public boost::noncopyable
{
public:
	Application();
	
	/* compiler's generated copy constructor is fine */
	/* compiler's generated destructor is fine */
	
	int execute( int argc, char* argv[] );

protected:
	boost::scoped_ptr< Syntax::Parser > m_parser;
};

}

#endif
