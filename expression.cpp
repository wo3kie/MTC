#include "headers/ph.hpp"

#include "headers/expression.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

Expression::Expression(
	boost::shared_ptr< Expression > _expression,
	boost::shared_ptr< LogicalOperator > _operator,
	boost::shared_ptr< SimpleExpression  > _simpleExpression
)
	: m_expression( _expression )
	, m_operator( _operator )
	, m_simpleExpression( _simpleExpression )
{
	POSTCONDITION3( m_expression, m_operator, m_simpleExpression )
}

Expression::Expression(
	boost::shared_ptr< SimpleExpression > _simpleExpression
)
	: m_expression( boost::shared_ptr< Expression >() )
	, m_operator( boost::shared_ptr< LogicalOperator >() )
	, m_simpleExpression( _simpleExpression )
{
	POSTCONDITION1( _simpleExpression )
}

boost::shared_ptr< Expression >
Expression::getExpression()
{
	return m_expression;
}

boost::shared_ptr< LogicalOperator >
Expression::getOperator()
{
	return m_operator;
}

boost::shared_ptr< SimpleExpression >
Expression::getSimpleExpression()
{
	return m_simpleExpression;
}

}
