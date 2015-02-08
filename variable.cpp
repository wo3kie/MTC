#include "headers/ph.hpp"

#include "headers/variable.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

Variable::Variable( std::string const & _name )
	: m_name( _name )
{
	POSTCONDITION1( ! m_name.empty() )
}

std::string
Variable::getName() const
{
	return m_name;
}

void
Variable::setHandler( Semantics::VariablesController::Handler _handler )
{
	m_handler = _handler;
	POSTCONDITION1( ! m_handler.isNull() )
}

Semantics::VariablesController::Handler
Variable::getHandler() const
{
	return m_handler;
}

IUnit::AddressingMode
Variable::getAddressingMode() const
{
    return & CodeGenerating::CodeGenerator::generateDirectAddressingMode;    
}

}
