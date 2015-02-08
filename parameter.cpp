#include "headers/ph.hpp"

#include "headers/parameter.hpp"

#include "headers/declaration.hpp"

#include "headers/postcondition.hpp"
#include "headers/precondition.hpp"
#include "headers/symbols_controller_factory.hpp"
#include "headers/type_data.hpp"

namespace Syntax
{

Parameter::Parameter( boost::shared_ptr< Declaration > _declaration )
	: m_declaration( _declaration )
{
	POSTCONDITION1( m_declaration );
}

boost::shared_ptr< Type >
Parameter::getType() const
{
    return m_declaration->getType();
}        
    
std::string
Parameter::getVariableName() const
{
	return m_declaration->getVariableName();
}

void
Parameter::setVariableHandler( Semantics::VariablesController::Handler _handler )
{
	PRECONDITION1( m_declaration->getVariableHandler().isNull() )	// one may call this function only once
	m_declaration->setVariableHandler( _handler );
}

Semantics::VariablesController::Handler
Parameter::getVariableHandler() const
{
	return m_declaration->getVariableHandler();
}

}
