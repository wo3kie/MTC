#include "headers/ph.hpp"

#include "headers/factor.hpp"

#include "headers/operators.hpp"
#include "headers/postcondition.hpp"

namespace Syntax
{

Factor::Factor(
	boost::shared_ptr< Factor > _factor,
	boost::shared_ptr< MultiplicativeOperator > _multiplicativeOperator,
	boost::shared_ptr< UnaryFactor > _unaryFactor
)
	: m_factor( _factor )
	, m_multiplicativeOperator( _multiplicativeOperator )
	, m_unaryFactor( _unaryFactor )
{
	POSTCONDITION3( m_factor, m_multiplicativeOperator, m_unaryFactor )
}

Factor::Factor(
	boost::shared_ptr< UnaryFactor > _unaryFactor
)
	: m_factor( boost::shared_ptr< Factor >() )
	, m_multiplicativeOperator( boost::shared_ptr< MultiplicativeOperator >() )
	, m_unaryFactor( _unaryFactor )
{
	POSTCONDITION1( m_unaryFactor )
}

boost::shared_ptr< Factor >
Factor::getFactor()
{
	return m_factor;
}

boost::shared_ptr< MultiplicativeOperator >
Factor::getOperator()
{
	return m_multiplicativeOperator;
}

boost::shared_ptr< UnaryFactor >
Factor::getUnaryFactor()
{
	return m_unaryFactor;
}

}
