#ifndef __SYNTAX_ASSIGNMENT_EXPRESSION_HPP__
#define __SYNTAX_ASSIGNMENT_EXPRESSION_HPP__

#include "headers/instruction.hpp"

namespace Syntax
{

class IUnit;
class Expression;

class AssignmentExpression
	: public IInstruction
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	AssignmentExpression(
		boost::shared_ptr< AssignmentExpression > _assignmentExpression,
		boost::shared_ptr< Expression > _expression );

	AssignmentExpression(
		boost::shared_ptr< Expression > _expression );

	boost::shared_ptr< AssignmentExpression > getAssignmentExpression();
	boost::shared_ptr< Expression > getExpression();
	
protected:
	boost::shared_ptr< AssignmentExpression > const m_assignmentExpression;
	boost::shared_ptr< Expression > const m_expression;
};

boost::shared_ptr< IUnit >
getUnitAssignFrom( AssignmentExpression & _assignmentExpression );

boost::shared_ptr< IUnit >
getUnitAssignTo( AssignmentExpression & _assignmentExpression );

}

#endif
