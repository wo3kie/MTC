#ifndef __SYNTAX_FUNCTION_DEFINITION_HPP__
#define __SYNTAX_FUNCTION_DEFINITION_HPP__

#include "headers/syntax_tree_node.hpp"

#include "headers/declaration.hpp"
#include "headers/functions_controller.hpp"
#include "headers/parameters_list.hpp"

namespace Syntax
{

class IInstruction;
class IType;

class Function
	: public ISyntaxTreeNode
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	Function(
		boost::shared_ptr< Type > _returnType,
		std::string const & _identifier,
		boost::shared_ptr< ParametersList > _parametersList,
		boost::shared_ptr< IInstruction > _functionBody );
	
	/* compiler's generated copy constructor is fine */
	/* compiler's generated destructor is fine */
			
	static std::string getMainFunctionName();
	
	boost::shared_ptr< Type > getReturnType() const;
	
	std::string getName() const;
	void setHandler( Semantics::FunctionsController::Handler _handler );
	Semantics::FunctionsController::Handler getHandler() const;
	
	boost::shared_ptr< ParametersList > getParametersList();
	boost::shared_ptr< IInstruction > getFunctionBody();
		
protected:
	boost::shared_ptr< Type > m_returnType;
	
	std::string const m_functionName;
	Semantics::FunctionsController::Handler m_functionHandler;
	
	boost::shared_ptr< ParametersList > const m_parametersList;
	boost::shared_ptr< IInstruction > const m_functionBody;
};

}

#endif
