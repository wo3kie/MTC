#include "headers/ph.hpp"

#include "headers/for_instruction.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

ForInstruction::ForInstruction(
	boost::shared_ptr< Declaration > _declaration,
	boost::shared_ptr< AssignmentExpression > _condition,
	boost::shared_ptr< IInstruction > _incrementInstruction,
	boost::shared_ptr< IInstruction > _loopBody
)
	: m_declaration( _declaration )
	, m_condition( _condition )
	, m_incrementInstruction( _incrementInstruction )
	, m_loopBody( _loopBody )
	, m_label( getInstanceCount() )
{
	POSTCONDITION4( m_declaration, m_condition, m_incrementInstruction, m_loopBody )
}

boost::shared_ptr< Declaration >
ForInstruction::getDeclarationChild()
{
	return m_declaration;
}

boost::shared_ptr< AssignmentExpression >
ForInstruction::getConditionChild()
{
	return m_condition;
}

boost::shared_ptr< IInstruction >
ForInstruction::getIncrementationChild()
{
	return m_incrementInstruction;
}

boost::shared_ptr< IInstruction >
ForInstruction::getBodyChild()
{
	return m_loopBody;
}

std::string
ForInstruction::getBeginLabel() const
{
	return std::string( ".LFORBEGIN" ) + boost::lexical_cast< std::string >( m_label );
}

std::string
ForInstruction::getEndLabel() const
{
	return std::string( ".LFOREND" ) + boost::lexical_cast< std::string >( m_label );
}

std::string
ForInstruction::getContinueLabel() const
{
    return std::string( ".LFORCONT" ) + boost::lexical_cast< std::string >( m_label );
}

}
