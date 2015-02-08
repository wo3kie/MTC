#ifndef __SYNTAX_FUNCTION_CALL_HPP__
#define __SYNTAX_FUNCTION_CALL_HPP__

#include "headers/expressions_list.hpp"
#include "headers/functions_controller.hpp"
#include "headers/unit.hpp"

namespace Syntax
{

class FunctionCall
	: public IUnit
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	FunctionCall(
		std::string const & _functionName,
		boost::shared_ptr< ExpressionsList > _expressionsList );
		
	std::string getFunctionName() const;
	
	void setHandler( Semantics::FunctionsController::Handler _handler );
	Semantics::FunctionsController::Handler getHandler() const;
	
	boost::shared_ptr< ExpressionsList > getExpressionsList();
    
    IUnit::AddressingMode getAddressingMode() const;
	
protected:
	std::string const m_functionName;
	Semantics::FunctionsController::Handler m_handler;
	boost::shared_ptr< ExpressionsList > const m_expressionsList;
};

}

#endif
