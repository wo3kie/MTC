#include "headers/ph.hpp"

#include "headers/assignment_expression.hpp"

#include "headers/postcondition.hpp"
#include "headers/factor.hpp"
#include "headers/unary_factor.hpp"
#include "headers/simple_expression.hpp"
#include "headers/expression.hpp"
#include "headers/unit.hpp"
#include "headers/variable.hpp"

namespace Syntax
{

AssignmentExpression::AssignmentExpression(
	boost::shared_ptr< AssignmentExpression > _assignmentExpression,
	boost::shared_ptr< Expression > _expression
)
	: m_assignmentExpression( _assignmentExpression )
	, m_expression( _expression )
{
	POSTCONDITION2( m_assignmentExpression, m_expression )
}

AssignmentExpression::AssignmentExpression(
	boost::shared_ptr< Expression > _expression
)
	: m_assignmentExpression( boost::shared_ptr< AssignmentExpression >() )
	, m_expression( _expression )
{
	POSTCONDITION1( m_expression )
}

boost::shared_ptr< AssignmentExpression >
AssignmentExpression::getAssignmentExpression()
{
	return m_assignmentExpression;
}

boost::shared_ptr< Expression >
AssignmentExpression::getExpression()
{
	return m_expression;
}

boost::shared_ptr< IUnit >
getUnitAssignFrom( AssignmentExpression & _assignmentExpression )
{
	return _assignmentExpression
		.getExpression()
		->getSimpleExpression()
		->getFactor()
		->getUnaryFactor()
		->getUnit();
}

boost::shared_ptr< IUnit >
getUnitAssignTo( AssignmentExpression & _assignmentExpression )
{
	return _assignmentExpression
		.getAssignmentExpression()
		->getExpression()
		->getSimpleExpression()
		->getFactor()
		->getUnaryFactor()
		->getUnit();
}

}
