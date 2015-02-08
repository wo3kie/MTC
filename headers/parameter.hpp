#ifndef __SYNTAX_PARAMETER_HPP__
#define __SYNTAX_PARAMETER_HPP__

#include "headers/instruction.hpp"
#include "headers/types_controller.hpp"
#include "headers/variables_controller.hpp"

namespace Syntax
{

class Declaration;
class Type;

class Parameter
	: public IInstruction
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
			
	Parameter( boost::shared_ptr< Declaration > _declaration );
	
	/* compiler's generated destructor is fine */

    boost::shared_ptr< Type > getType() const;
	std::string getVariableName() const;
	void setVariableHandler( Semantics::VariablesController::Handler _handler );
	Semantics::VariablesController::Handler getVariableHandler() const;
	
	std::string getVariable() const;
	
protected:
	boost::shared_ptr< Declaration > m_declaration;
};

}

#endif
