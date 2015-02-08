#ifndef __SYNTAX_RETURN_INSTRUCTION_HPP__
#define __SYNTAX_RETURN_INSTRUCTION_HPP__

#include "headers/instruction.hpp"

namespace Syntax
{
	
class AssignmentExpression;

class ReturnInstruction
	: public IInstruction
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	ReturnInstruction( );
	
	explicit ReturnInstruction(
		boost::shared_ptr< AssignmentExpression > _assignmentExpression );

	boost::shared_ptr< AssignmentExpression > getAssignmentExpression();
    
    void setProgramFinish( bool _isProgramFinish );
    bool isProgramFinish() const;

protected:
    bool m_isProgramFinish;
	boost::shared_ptr< AssignmentExpression > const m_assignmentExpression;
};
	
}

#endif
