#ifndef __DEREFERENCE_HPP__
#define __DEREFERENCE_HPP__

#include "headers/unit.hpp"

namespace Syntax
{

class Dereference
	: public IUnit
{
public:
    struct AssignmentSide {
        enum Enum {
            Left = 1,
            Right = 2
        };
    };

public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
		
	static boost::shared_ptr< Dereference > create( boost::shared_ptr< IUnit > _unit );

	boost::shared_ptr< IUnit > getUnit();

    AddressingMode getAddressingMode() const;
    
    void setAssignmentSide( AssignmentSide::Enum _assignmentSide );
    AssignmentSide::Enum getAssignmentSide() const;

private:
    Dereference( boost::shared_ptr< IUnit > _unit );
    
protected:
	boost::shared_ptr< IUnit > const m_unit;
    AssignmentSide::Enum m_assignmentSide;
};

}

#endif
