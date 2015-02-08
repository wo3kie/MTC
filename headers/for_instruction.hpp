#ifndef __SYNTAX_FOR_INSTRUCTION_HPP__
#define __SYNTAX_FOR_INSTRUCTION_HPP__

#include "headers/instance_counter.hpp"
#include "headers/loop_instruction.hpp"

namespace Syntax
{

class Declaration;
class AssignmentExpression;	
class IInstruction;

class ForInstruction
	: public LoopInstruction
	, protected Utility::InstanceCounter< ForInstruction >
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	ForInstruction(
		boost::shared_ptr< Declaration > _declaration,
		boost::shared_ptr< AssignmentExpression > _condition,
		boost::shared_ptr< IInstruction > _incrementInstruction,
		boost::shared_ptr< IInstruction > _loopBody );

	boost::shared_ptr< Declaration > getDeclarationChild();
	boost::shared_ptr< AssignmentExpression > getConditionChild();
	boost::shared_ptr< IInstruction > getIncrementationChild();
	boost::shared_ptr< IInstruction > getBodyChild();
	
	std::string getBeginLabel() const;
	std::string getEndLabel() const;
	std::string getContinueLabel() const;

protected:
	boost::shared_ptr< Declaration > const m_declaration;
	boost::shared_ptr< AssignmentExpression > const m_condition;
	boost::shared_ptr< IInstruction > const m_incrementInstruction;
	boost::shared_ptr< IInstruction > const m_loopBody;
	
	int const m_label;
};
	
}

#endif
