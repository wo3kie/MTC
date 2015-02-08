#include "headers/ph.hpp"

#include "headers/get_address.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

boost::shared_ptr< GetAddress >
GetAddress::create( boost::shared_ptr< Variable > _variable )
{
    return boost::shared_ptr< GetAddress >( new GetAddress( _variable ) );
}
    
GetAddress::GetAddress( boost::shared_ptr< Variable > _variable )
    : m_variable( _variable )
{
	POSTCONDITION1( m_variable )
}

boost::shared_ptr< Variable >
GetAddress::getVariable()
{
	return m_variable;
}

IUnit::AddressingMode
GetAddress::getAddressingMode() const
{
    return & CodeGenerating::CodeGenerator::generateDirectAddressingMode;
}

}
