#include "headers/ph.hpp"

#include "headers/program.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

Program::Program( boost::shared_ptr< FunctionsList > _functionsList )
	: m_functionsList( _functionsList )
{
	POSTCONDITION1(  m_functionsList )
}

boost::shared_ptr< FunctionsList >
Program::getFunctionsList()
{
	return m_functionsList;
}

}
