#include "headers/ph.hpp"

#include "headers/declaration.hpp"

#include "headers/postcondition.hpp"
#include "headers/precondition.hpp"
#include "headers/symbols_controller_factory.hpp"
#include "headers/type_data.hpp"

namespace Syntax
{

Declaration::Declaration(
	boost::shared_ptr< Type > _type,
	std::string const & _variable,
	boost::shared_ptr< Expression > _initializingExpression
)
	: m_type( _type )
	, m_variableName( _variable )
	, m_initializingExpression( _initializingExpression )
{
	POSTCONDITION3( m_type, ! m_variableName.empty(), m_initializingExpression )
}

Declaration::Declaration(
	boost::shared_ptr< Type > _type,
	std::string const & _variable
)
	: m_type( _type )
	, m_variableName( _variable )
	, m_initializingExpression( boost::shared_ptr< Expression >() )
{
	POSTCONDITION2( m_type, ! m_variableName.empty() )
}

std::string
Declaration::getVariableName() const
{
	return m_variableName;	
}

void
Declaration::setVariableHandler( Semantics::VariablesController::Handler _handler )
{
	PRECONDITION1( m_variableHandler.isNull() )	// one may call this function only once
	m_variableHandler = _handler;
}

Semantics::VariablesController::Handler
Declaration::getVariableHandler() const
{
	return m_variableHandler;
}

boost::shared_ptr< Expression >
Declaration::getInitializationChild()
{
	return m_initializingExpression;
}

}
