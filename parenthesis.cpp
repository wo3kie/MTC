#include "headers/ph.hpp"

#include "headers/parenthesis.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

Parenthesis::Parenthesis(
	boost::shared_ptr< AssignmentExpression > const _assignmentExpression
)
	: m_assignmentExpression( _assignmentExpression )
{
	POSTCONDITION1( m_assignmentExpression )
}

boost::shared_ptr< AssignmentExpression >
Parenthesis::getAssignmentExpression()
{
	return m_assignmentExpression;
}


IUnit::AddressingMode
Parenthesis::getAddressingMode() const
{
    return & CodeGenerating::CodeGenerator::generateDirectAddressingMode;
}

}
