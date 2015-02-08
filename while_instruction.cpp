#include "headers/ph.hpp"

#include "headers/while_instruction.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

WhileInstruction::WhileInstruction(
	boost::shared_ptr< AssignmentExpression > _condition,
	boost::shared_ptr< IInstruction > _loopBody
)
	: m_condition( _condition )
	, m_loopBody( _loopBody )
	, m_label( getInstanceCount() )
{
	POSTCONDITION2( m_condition, m_loopBody )
}

boost::shared_ptr< AssignmentExpression >
WhileInstruction::getConditionChild()
{
	return m_condition;
}

boost::shared_ptr< IInstruction >
WhileInstruction::getBodyChild()
{
	return m_loopBody;
}

std::string
WhileInstruction::getConditionLabel() const
{
	return std::string( ".LWHILECOND" ) + boost::lexical_cast< std::string >( m_label );
}

std::string
WhileInstruction::getBeginLabel() const
{
	return std::string( ".LWHILEBEGIN" ) + boost::lexical_cast< std::string >( m_label );
}

std::string
WhileInstruction::getEndLabel() const
{
	return std::string( ".LWHILEEND" ) + boost::lexical_cast< std::string >( m_label );
}

std::string
WhileInstruction::getContinueLabel() const
{
    return getBeginLabel();
}

}
