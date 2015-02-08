#include "headers/ph.hpp"

#include "headers/function.hpp"

#include "headers/postcondition.hpp"
#include "headers/symbols_controller_factory.hpp"
#include "headers/type_data.hpp"
#include "headers/types_controller.hpp"

namespace Syntax
{
	
Function::Function(
	boost::shared_ptr< Type > _returnType,
	std::string const & _identifier,
	boost::shared_ptr< ParametersList > _declarationsList,
	boost::shared_ptr< IInstruction > _functionBody
)
	: m_returnType( _returnType )
	, m_functionName( _identifier )
	, m_parametersList( _declarationsList )
	, m_functionBody( _functionBody )
{
	POSTCONDITION4(
		m_returnType,
		! m_functionName.empty(),
		m_parametersList,
		m_functionBody )
}

std::string
Function::getMainFunctionName()
{
	return std::string( "main" );
}

boost::shared_ptr< Type >
Function::getReturnType() const
{
	return m_returnType;
}

std::string
Function::getName() const
{
	return m_functionName;
}

void
Function::setHandler( Semantics::FunctionsController::Handler _handler )
{
	PRECONDITION1( ! _handler.isNull() )
	m_functionHandler = _handler;
}

Semantics::FunctionsController::Handler
Function::getHandler() const
{
	return m_functionHandler;
}


boost::shared_ptr< ParametersList >
Function::getParametersList()
{
	return m_parametersList;
}

boost::shared_ptr< IInstruction >
Function::getFunctionBody()
{
	return m_functionBody;
}

}
