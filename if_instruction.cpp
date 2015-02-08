#include "headers/ph.hpp"

#include "headers/if_instruction.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

IfInstruction::IfInstruction(
	boost::shared_ptr< AssignmentExpression > _condition,
	boost::shared_ptr< IInstruction > _trueBranchInstruction,
	boost::shared_ptr< IInstruction > _falseBranchInstruction
)
	: m_condition( _condition )
	, m_trueBranchInstruction( _trueBranchInstruction )
	, m_falseBranchInstruction( _falseBranchInstruction )
	, m_label( getInstanceCount() )
{
	POSTCONDITION3( m_condition, m_trueBranchInstruction, m_falseBranchInstruction )
}

IfInstruction::IfInstruction(
	boost::shared_ptr< AssignmentExpression > _condition,
	boost::shared_ptr< IInstruction > _trueBranchInstruction
)
	: m_condition( _condition )
	, m_trueBranchInstruction( _trueBranchInstruction )
	, m_falseBranchInstruction( boost::shared_ptr< IInstruction >() )
	, m_label( getInstanceCount() )
{
	POSTCONDITION2( m_condition, m_trueBranchInstruction )
}

boost::shared_ptr< AssignmentExpression >
IfInstruction::getConditionChild()
{
	return m_condition;
}

boost::shared_ptr< IInstruction >
IfInstruction::getTrueBranchChild()
{
	return m_trueBranchInstruction;
}

boost::shared_ptr< IInstruction >
IfInstruction::getFalseBranchChild()
{
	return m_falseBranchInstruction;
}

std::string
IfInstruction::getFalseBranchLabel() const
{
	return std::string( ".LIFFALSE" ) + boost::lexical_cast< std::string >( m_label );
}

std::string
IfInstruction::getTrueBranchLabel() const
{
	return std::string( ".LIFTRUE" ) + boost::lexical_cast< std::string >( m_label );
}

std::string
IfInstruction::getEndLabel() const
{
	return std::string( ".LIFEND" ) + boost::lexical_cast< std::string >( m_label );
}

}
