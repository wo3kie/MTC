#include "headers/ph.hpp"

#include "headers/dereference.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

boost::shared_ptr< Dereference >
Dereference::create( boost::shared_ptr< IUnit > _unit )
{
    return boost::shared_ptr< Dereference >( new Dereference( _unit ) );
}
    
Dereference::Dereference( boost::shared_ptr< IUnit > _unit )
    : m_unit( _unit )
{
	POSTCONDITION1( m_unit )
}

boost::shared_ptr< IUnit >
Dereference::getUnit()
{
	return m_unit;
}

IUnit::AddressingMode
Dereference::getAddressingMode() const
{
    return & CodeGenerating::CodeGenerator::generateIndirectAddressingMode;
}

void
Dereference::setAssignmentSide( AssignmentSide::Enum _assignmentSide )
{
    m_assignmentSide = _assignmentSide;
}
    
Dereference::AssignmentSide::Enum
Dereference::getAssignmentSide() const
{
    return m_assignmentSide;
}

}
