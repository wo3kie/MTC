#ifndef __SYNTAX_PARENTHESIS_HPP__
#define __SYNTAX_PARENTHESIS_HPP__

#include "headers/unit.hpp"

namespace Syntax
{

class AssignmentExpression;
	
class Parenthesis
	: public IUnit
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	explicit Parenthesis(
		boost::shared_ptr< AssignmentExpression > const _assignmentExpression );

	boost::shared_ptr< AssignmentExpression > getAssignmentExpression();
    
    IUnit::AddressingMode getAddressingMode() const;
	
protected:
	boost::shared_ptr< AssignmentExpression > const m_assignmentExpression;
};

}

#endif
