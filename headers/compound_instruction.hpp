#ifndef __SYNTAX_COMPOUND_INSTRUCTION_HPP__
#define __SYNTAX_COMPOUND_INSTRUCTION_HPP__

#include "headers/instruction.hpp"
#include "headers/instructions_list.hpp"

namespace Syntax
{

class CompoundInstruction
	: public IInstruction
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	explicit CompoundInstruction(
		boost::shared_ptr< InstructionsList > _instructionsList );

	boost::shared_ptr< InstructionsList > getInstructionsList();

protected:
	boost::shared_ptr< InstructionsList > const m_instructionsList;
};

}

#endif
