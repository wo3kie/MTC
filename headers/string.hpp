#ifndef __SYNTAX_STRING_HPP__
#define __SYNTAX_STRING_HPP__

#include "headers/unit.hpp"
#include "headers/strings_controller.hpp"

namespace Syntax
{

class String
	: public IUnit
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	/* compiler's generated destructor is fine */
	
	explicit String( std::string const & _value );
	
	std::string getValue() const;
	
	void setHandler( Semantics::StringsController::Handler _handler );
	Semantics::StringsController::Handler getHandler() const;
    
    IUnit::AddressingMode getAddressingMode() const;

private:
	std::string const m_value;
	Semantics::StringsController::Handler m_handler;
};

}

#endif
