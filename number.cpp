#include "headers/ph.hpp"

#include "headers/number.hpp"

namespace Syntax
{

Number::Number(
	int _value
)
	: m_value( _value )
{
}

int
Number::getValue() const
{
	return m_value;
}


IUnit::AddressingMode
Number::getAddressingMode() const
{
    return & CodeGenerating::CodeGenerator::generateDirectAddressingMode;
}

}
