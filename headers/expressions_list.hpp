#ifndef __SYNTAX_EXPRESSIONS_LIST_HPP__
#define __SYNTAX_EXPRESSIONS_LIST_HPP__

#include "headers/syntax_tree_list.hpp"

namespace Syntax
{

class AssignmentExpression;

typedef SyntaxTreeList< AssignmentExpression > ExpressionsList;

}

#endif
