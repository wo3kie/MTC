#ifndef __SYNTAX_EXPRESSION_HPP__
#define __SYNTAX_EXPRESSION_HPP__

#include "headers/instruction.hpp"

namespace Syntax
{
	
class SimpleExpression;
class LogicalOperator;
	
class Expression
	: public IInstruction
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	Expression(
		boost::shared_ptr< Expression > _expression,
		boost::shared_ptr< LogicalOperator > _operator,
		boost::shared_ptr< SimpleExpression > _simpleExpression );

	explicit Expression(
		boost::shared_ptr< SimpleExpression > _simpleExpression );

	boost::shared_ptr< Expression > getExpression();
	boost::shared_ptr< LogicalOperator > getOperator();
	boost::shared_ptr< SimpleExpression > getSimpleExpression();
	
protected:
	boost::shared_ptr< Expression > const m_expression;
	boost::shared_ptr< LogicalOperator > const m_operator;
	boost::shared_ptr< SimpleExpression > const m_simpleExpression;
};
	
}

#endif
