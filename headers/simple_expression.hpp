#ifndef __SYNTAX_SIMPLE_EXPRESSION_HPP__
#define __SYNTAX_SIMPLE_EXPRESSION_HPP__

#include "headers/syntax_tree_node.hpp"

namespace Syntax
{
	
class Factor;
class AdditiveOperator;

class SimpleExpression
	: public ISyntaxTreeNode
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	SimpleExpression(
		boost::shared_ptr< SimpleExpression > _simpleExpression,
		boost::shared_ptr< AdditiveOperator > _operator,
		boost::shared_ptr< Factor > _factor );

	explicit SimpleExpression(
			boost::shared_ptr< Factor > _factor );

	boost::shared_ptr< SimpleExpression > getSimpleExpression();
	boost::shared_ptr< AdditiveOperator > getOperator();
	boost::shared_ptr< Factor > getFactor();

protected:
	boost::shared_ptr< SimpleExpression > const m_simpleExpression;
	boost::shared_ptr< AdditiveOperator > m_operator;
	boost::shared_ptr< Factor > const m_factor;
};
	
}

#endif
