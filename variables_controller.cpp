#include "headers/ph.hpp"

#include "headers/variables_controller.hpp"

#include "headers/postcondition.hpp"
#include "headers/types_controller.hpp"

namespace Semantics
{

VariablesController::Handler
VariablesController::insert( VariableData const & _data )
{
	return m_variablesTable.insert( _data );
}
	
VariablesController::Handler
VariablesController::getHandler(
	std::string const & _name,
	Scope const & _scope
) const
{
	return m_variablesTable.getHandler( _name, _scope );
}
	
VariableData
VariablesController::getData( VariablesController::Handler _handler ) const
{
	return m_variablesTable.getData( _handler );
}

void
VariablesController::calculateVariablesOffsetOnStack(
	TypesController const & _typesController
)
{
	std::map< unsigned, int > variablesOffset;
	std::map< unsigned, int > parametersOffset;
	
	for ( VariablesTable::iterator
			current( m_variablesTable.begin() ),
			end( m_variablesTable.end() )
		; current != end
		; ++current
	)
	{
		unsigned const currentScope = current->getScope().m_function;
		unsigned capacity = _typesController.getData( current->getType() ).getMemoryCapacity();

		if ( current->getVariableType() == VariableType::Parameter )
		{
			int const baseOffset = 4;
			
			parametersOffset[ currentScope ] += capacity;
			current->setStackOffset(
				baseOffset + ( * parametersOffset.find( currentScope ) ).second );
		}
		else
		{
			variablesOffset[ currentScope ] -= capacity;
			current->setStackOffset( ( * variablesOffset.find( currentScope ) ).second );
			m_memoryCapacity[ currentScope ] += abs( capacity );
		}
	}
}

unsigned
VariablesController::getVariablesCapacity( Scope _scope ) const
{
	std::map< unsigned, unsigned >::const_iterator current
		= m_memoryCapacity.find( _scope.m_function );
	
	if ( current == m_memoryCapacity.end() )
	{
		return 0;
	}
	else
	{
		return current->second;	
	}
}

}
