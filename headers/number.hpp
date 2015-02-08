#ifndef __SYNTAX_UNMBER_HPP__
#define __SYNTAX_UNMBER_HPP__

#include "headers/unit.hpp"

namespace Syntax
{

class Number
	: public IUnit
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	explicit Number( int _value );
	
	int getValue() const;
    
    IUnit::AddressingMode getAddressingMode() const;
	
private:
	int const m_value;
};

}

#endif
