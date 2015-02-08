#include "headers/ph.hpp"

#include "headers/compound_instruction.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

CompoundInstruction::CompoundInstruction(
	boost::shared_ptr< InstructionsList > _instructionsList
)
	: m_instructionsList( _instructionsList )
{
	POSTCONDITION1( m_instructionsList )
}

boost::shared_ptr< InstructionsList >
CompoundInstruction::getInstructionsList()
{
	return m_instructionsList;
}

}
