#ifndef __SYNTAX_INSTRUCTION_HPP__
#define __SYNTAX_INSTRUCTION_HPP__

#include "headers/syntax_tree_node.hpp"

namespace Syntax
{

class IInstruction
	: public ISyntaxTreeNode
{
public:
	/*virtual*/ ~IInstruction(){}
};

}

#endif
