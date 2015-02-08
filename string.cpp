#include "headers/ph.hpp"

#include "headers/string.hpp"

#include "headers/postcondition.hpp"

namespace Syntax
{

String::String( std::string const & _value )
	: m_value( _value )
{
	POSTCONDITION1( ! m_value.empty() )
}

std::string
String::getValue() const
{
	return m_value;
}

void
String::setHandler( Semantics::StringsController::Handler _handler )
{
	m_handler = _handler;
        POSTCONDITION1( ! m_handler.isNull() );
}

Semantics::StringsController::Handler
String::getHandler() const
{
	POSTCONDITION1( ! m_handler.isNull() );
	return m_handler;
}


IUnit::AddressingMode
String::getAddressingMode() const
{
    assert( false );
    return 0;
}

}
