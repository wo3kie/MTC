#ifndef __SYNTAX_INSTRUCTIONS_LIST_HPP__
#define __SYNTAX_INSTRUCTIONS_LIST_HPP__

#include "headers/syntax_tree_list.hpp"

namespace Syntax
{

class IInstruction;

typedef SyntaxTreeList< IInstruction > InstructionsList;

}

#endif
