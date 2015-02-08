#ifndef __SYNTAX_DO_WHILE_INSTRUCTION_HPP__
#define __SYNTAX_DO_WHILE_INSTRUCTION_HPP__

#include "headers/instance_counter.hpp"
#include "headers/instruction.hpp"

namespace Syntax
{
	
class IInstruction;
class AssignmentExpression;

class DoWhileInstruction
	: public IInstruction
	, protected Utility::InstanceCounter< DoWhileInstruction >
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	DoWhileInstruction(
		boost::shared_ptr< IInstruction > _loopBody,
		boost::shared_ptr< AssignmentExpression > _condition );
		
	boost::shared_ptr< IInstruction > getBodyChild();
	boost::shared_ptr< AssignmentExpression > getConditionChild();
	
	std::string getBeginLabel() const;
	std::string getEndLabel() const;

protected:
	boost::shared_ptr< IInstruction > const m_loopBody;
	boost::shared_ptr< AssignmentExpression > const m_condition;
	
	int const m_label;
};
	
}

#endif
