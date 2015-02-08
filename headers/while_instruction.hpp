#ifndef __SYNTAX_WHILE_INSTRUCTION_HPP__
#define __SYNTAX_WHILE_INSTRUCTION_HPP__

#include "headers/instance_counter.hpp"
#include "headers/loop_instruction.hpp"

namespace Syntax
{
	
class IInstruction;
class AssignmentExpression;

class WhileInstruction
	: public LoopInstruction
	, protected Utility::InstanceCounter< WhileInstruction >
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	WhileInstruction(
		boost::shared_ptr< AssignmentExpression > _condition,
		boost::shared_ptr< IInstruction > _loopBody );

	boost::shared_ptr< IInstruction > getBodyChild();
	boost::shared_ptr< AssignmentExpression > getConditionChild();

	std::string getConditionLabel() const;
	std::string getBeginLabel() const;
	std::string getEndLabel() const;
    std::string getContinueLabel() const;

protected:
	boost::shared_ptr< AssignmentExpression > const m_condition;
	boost::shared_ptr< IInstruction > const m_loopBody;
	
	int m_label;
};
	
}

#endif
