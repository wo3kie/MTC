#ifndef __SYNTAX_PROGRAM_HPP__
#define __SYNTAX_PROGRAM_HPP__

#include "headers/functions_list.hpp"
#include "headers/syntax_tree_node.hpp"

namespace Syntax
{

class Program
	: public ISyntaxTreeNode
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
		
	explicit Program( boost::shared_ptr< FunctionsList > _functionsList );
	
	boost::shared_ptr< FunctionsList > getFunctionsList();
		
protected:
	boost::shared_ptr< FunctionsList > const m_functionsList;
};

}

#endif
