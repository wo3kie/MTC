#ifndef __SYNTAX_FACTOR_HPP__
#define __SYNTAX_FACTOR_HPP__

#include "headers/syntax_tree_node.hpp"

namespace Syntax
{
	
class MultiplicativeOperator;
class UnaryFactor;

class Factor
	: public ISyntaxTreeNode
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	Factor(
		boost::shared_ptr< Factor > _factor,
		boost::shared_ptr< MultiplicativeOperator > _multiplicativeOperator,
		boost::shared_ptr< UnaryFactor > _unaryFactor );

	explicit Factor(
		boost::shared_ptr< UnaryFactor > _unaryFactor );

	boost::shared_ptr< Factor > getFactor();
	boost::shared_ptr< MultiplicativeOperator > getOperator();
	boost::shared_ptr< UnaryFactor > getUnaryFactor();

protected:
	boost::shared_ptr< Factor > const m_factor;
	boost::shared_ptr< MultiplicativeOperator > const m_multiplicativeOperator;
	boost::shared_ptr< UnaryFactor > const m_unaryFactor;
};
	
}

#endif
