#ifndef __SYMBOLS_TABLE_FUNCTION_DATA_HPP__
#define __SYMBOLS_TABLE_FUNCTION_DATA_HPP__

#include "headers/symbol_data.hpp"
#include "headers/types_controller.hpp"

namespace Semantics
{

class FunctionData
	: public SymbolData< std::string >
{
public:
	FunctionData(
		std::string const & _functionName,
		TypesController::Handler _returnValueType,
		Scope _functionDefinedIn,
		Scope _functionBody );
	
	FunctionData(
		std::string const & _functionName,
		TypesController::Handler _returnValueType,
		std::vector< TypesController::Handler > const & _parametersTypes,
		Scope _functionDefinedIn,
		Scope _functionBody );
	
	/* compiler's generated copy constructor is fine */
	/* compiler's generated destructor is fine */
	/* compiler's generated operator= is fine */
	
	TypesController::Handler getReturnValueType() const;
	std::vector< TypesController::Handler > getParametersTypes() const;
	
	void setFunctionBodyScope( Scope _scope );
	Scope getFunctionBodyScope() const;
	
private:	
	TypesController::Handler m_returnValueType;
	std::vector< TypesController::Handler > m_parametersTypes;
	
	Scope m_functionBodyScope;
};

}

#endif
