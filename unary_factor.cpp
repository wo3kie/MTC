#include "headers/ph.hpp"

#include "headers/unary_factor.hpp"

#include "headers/operators.hpp"
#include "headers/postcondition.hpp"

namespace Syntax
{

UnaryFactor::UnaryFactor(
	boost::shared_ptr< UnaryOperator > _unaryOperator,
	boost::shared_ptr< IUnit > _unit
)
	: m_unaryOperator( _unaryOperator )
	, m_unit( _unit )
{
	POSTCONDITION2( m_unaryOperator, m_unit )
}

UnaryFactor::UnaryFactor( 
	boost::shared_ptr< IUnit > _unit
)
	: m_unaryOperator( boost::shared_ptr< UnaryOperator >() )
	, m_unit( _unit )
{
	POSTCONDITION1( m_unit )
}

boost::shared_ptr< UnaryOperator >
UnaryFactor::getOperator()
{
	return m_unaryOperator;
}

boost::shared_ptr< IUnit >
UnaryFactor::getUnit()
{
	return m_unit;
}

}
