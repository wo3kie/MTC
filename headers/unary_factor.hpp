#ifndef __SYNTAX_UNARY_FACTOR_HPP__
#define __SYNTAX_UNARY_FACTOR_HPP__

#include "headers/syntax_tree_node.hpp"

namespace Syntax
{
	
class UnaryOperator;
class IUnit;

class UnaryFactor
	: public ISyntaxTreeNode
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	UnaryFactor(
		boost::shared_ptr< UnaryOperator > _unaryOperator,
		boost::shared_ptr< IUnit > _unit );
		
	explicit UnaryFactor(
		boost::shared_ptr< IUnit > _unit );

	boost::shared_ptr< UnaryOperator > getOperator();
	boost::shared_ptr< IUnit > getUnit();

protected:
	boost::shared_ptr< UnaryOperator > const m_unaryOperator;
	boost::shared_ptr< IUnit > const m_unit;
};

}

#endif
