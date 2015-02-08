#include "headers/ph.hpp"

#include "headers/do_while_instruction.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

DoWhileInstruction::DoWhileInstruction(
	boost::shared_ptr< IInstruction > _loopBody,
	boost::shared_ptr< AssignmentExpression > _condition
)
	: m_loopBody( _loopBody )
	, m_condition( _condition )
	, m_label( getInstanceCount() )
{
	POSTCONDITION2( m_loopBody, m_condition )
}

boost::shared_ptr< IInstruction >
DoWhileInstruction::getBodyChild()
{
	return m_loopBody;
}

boost::shared_ptr< AssignmentExpression >
DoWhileInstruction::getConditionChild()
{
	return m_condition;
}

std::string
DoWhileInstruction::getBeginLabel() const
{
	return std::string( ".LDOWHILEBEGIN" ) + boost::lexical_cast< std::string >( m_label );
}

std::string
DoWhileInstruction::getEndLabel() const
{
	return std::string( ".LDOWHILEEND" ) + boost::lexical_cast< std::string >( m_label );
}

}
