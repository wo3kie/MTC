#include "headers/ph.hpp"

#include "headers/return_instruction.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

ReturnInstruction::ReturnInstruction( )
	: m_assignmentExpression( boost::shared_ptr< AssignmentExpression >() )
{
}


ReturnInstruction::ReturnInstruction(
	boost::shared_ptr< AssignmentExpression > _assignmentExpression
)
	: m_assignmentExpression( _assignmentExpression )
{
	POSTCONDITION1( m_assignmentExpression )
}

boost::shared_ptr< AssignmentExpression >
ReturnInstruction::getAssignmentExpression()
{
	return m_assignmentExpression;
}

void
ReturnInstruction::setProgramFinish( bool _isProgramFinished )
{
    m_isProgramFinish = _isProgramFinished;
}
    
bool
ReturnInstruction::isProgramFinish() const
{
    return m_isProgramFinish;
}

}
