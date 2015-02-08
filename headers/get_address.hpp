#ifndef __GET_ADDRESS_HPP__
#define __GET_ADDRESS_HPP__

#include "headers/unit.hpp"
#include "headers/variable.hpp"

namespace Syntax
{

class GetAddress
	: public IUnit
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
		
	static boost::shared_ptr< GetAddress > create( boost::shared_ptr< Variable > _variable );

	boost::shared_ptr< Variable > getVariable();
    
    AddressingMode getAddressingMode() const;

private:
    GetAddress( boost::shared_ptr< Variable > _variable );
    
protected:
	boost::shared_ptr< Variable > const m_variable;
};

}

#endif
