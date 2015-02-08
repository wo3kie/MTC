#include "headers/ph.hpp"

#include "headers/simple_expression.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

SimpleExpression::SimpleExpression(
	boost::shared_ptr< SimpleExpression > _simpleExpression,
	boost::shared_ptr< AdditiveOperator > _operator,
	boost::shared_ptr< Factor > _factor
)
	: m_simpleExpression( _simpleExpression )
	, m_operator( _operator )
	, m_factor( _factor )
{
	POSTCONDITION3( m_simpleExpression, m_operator, m_factor )
}

SimpleExpression::SimpleExpression(
	boost::shared_ptr< Factor > _factor
)
	: m_simpleExpression( boost::shared_ptr< SimpleExpression >() )
	, m_operator( boost::shared_ptr< AdditiveOperator >() )
	, m_factor( _factor )
{
	POSTCONDITION1( m_factor )
}

boost::shared_ptr< SimpleExpression >
SimpleExpression::getSimpleExpression()
{
	return m_simpleExpression;
}

boost::shared_ptr< AdditiveOperator >
SimpleExpression::getOperator()
{
	return m_operator;
}

boost::shared_ptr< Factor >
SimpleExpression::getFactor()
{
	return m_factor;
}

}
