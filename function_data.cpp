#include "headers/ph.hpp"

#include "headers/function_data.hpp"

#include "headers/postcondition.hpp"

namespace Semantics
{

FunctionData::FunctionData(
	std::string const & _functionName,
	TypesController::Handler _returnValueType,
	Scope _functionDefinedIn,
	Scope _functionBody
)
	: SymbolData< std::string >( _functionName, _functionDefinedIn )
	, m_returnValueType( _returnValueType )
	, m_functionBodyScope( _functionBody )
{
	POSTCONDITION2( ! getKey().empty(), ! m_returnValueType.isNull() )
}

FunctionData::FunctionData(
	std::string const & _functionName,
	TypesController::Handler _returnValueType,
	std::vector< TypesController::Handler > const & _parametersTypes,
	Scope _functionDefinedIn,
	Scope _functionBody
)
	: SymbolData< std::string >( _functionName, _functionDefinedIn )
	, m_returnValueType( _returnValueType )
	, m_parametersTypes( _parametersTypes )
	, m_functionBodyScope( _functionBody )
{
	POSTCONDITION3( ! getKey().empty(), ! m_returnValueType.isNull(), ! m_parametersTypes.empty() )
}
	
TypesController::Handler
FunctionData::getReturnValueType() const
{
	return m_returnValueType;
}

std::vector< TypesController::Handler >
FunctionData::getParametersTypes() const
{
	return m_parametersTypes;
}

void
FunctionData::setFunctionBodyScope( Scope _scope )
{
	m_functionBodyScope = _scope;
}

Scope
FunctionData::getFunctionBodyScope() const
{
	return m_functionBodyScope;
}

}
