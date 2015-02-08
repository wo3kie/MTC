#ifndef __SYNTAX_VARIABLE_HPP__
#define __SYNTAX_VARIABLE_HPP__

#include "headers/unit.hpp"
#include "headers/variables_controller.hpp"

namespace Semantics
{
class VariableData;
}

namespace Syntax
{

class Variable
	: public IUnit
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	Variable( std::string const & _name );
		
	std::string getName() const;
	
	void setHandler( Semantics::VariablesController::Handler _handler );
	Semantics::VariablesController::Handler getHandler() const;

    IUnit::AddressingMode getAddressingMode() const;

private:
	std::string const m_name;
	Semantics::VariablesController::Handler m_handler;
};

}

#endif
