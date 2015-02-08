#include "headers/ph.hpp"

#include "headers/function_call.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

FunctionCall::FunctionCall(
	std::string const & _functionName,
	boost::shared_ptr< ExpressionsList > _expressionsList
)
	: m_functionName( _functionName )
	, m_expressionsList( _expressionsList )
{
	POSTCONDITION1( /*m_expressionsList - may be null*/ ! m_functionName.empty() )
}

std::string
FunctionCall::getFunctionName() const
{
	return m_functionName;
}

void
FunctionCall::setHandler( Semantics::FunctionsController::Handler _handler )
{
	m_handler = _handler;
}

Semantics::FunctionsController::Handler
FunctionCall::getHandler() const
{
	POSTCONDITION1( ! m_handler.isNull() )
	return m_handler;
}

boost::shared_ptr< ExpressionsList >
FunctionCall::getExpressionsList()
{
	return m_expressionsList;
}


IUnit::AddressingMode
FunctionCall::getAddressingMode() const
{
    return & CodeGenerating::CodeGenerator::generateDirectAddressingMode;
}

}
