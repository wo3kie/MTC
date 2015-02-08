#ifndef __SYNTAX_IF_INSTRUCTION_HPP__
#define __SYNTAX_IF_INSTRUCTION_HPP__

#include "headers/instruction.hpp"

#include "headers/instance_counter.hpp"

namespace Syntax
{

class AssignmentExpression;	
class IInstruction;

class IfInstruction
	: public IInstruction
	, protected Utility::InstanceCounter< IfInstruction >
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
		
	IfInstruction(
		boost::shared_ptr< AssignmentExpression > _condition,
		boost::shared_ptr< IInstruction > _trueBranchInstruction,
		boost::shared_ptr< IInstruction > _falseBranchInstruction );
		
	IfInstruction(
		boost::shared_ptr< AssignmentExpression > _condition,
		boost::shared_ptr< IInstruction > _trueBranchInstruction );
		
	boost::shared_ptr< AssignmentExpression > getConditionChild();
	boost::shared_ptr< IInstruction > getTrueBranchChild();
	boost::shared_ptr< IInstruction > getFalseBranchChild();
	
	std::string getFalseBranchLabel() const;
	std::string getTrueBranchLabel() const;
	std::string getEndLabel() const;

protected:
	boost::shared_ptr< AssignmentExpression > const m_condition;
	boost::shared_ptr< IInstruction > const m_trueBranchInstruction;
	boost::shared_ptr< IInstruction > const m_falseBranchInstruction;
	
	int const m_label;
};
	
}

#endif
