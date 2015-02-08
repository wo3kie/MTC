#include "headers/ph.hpp"

#include "headers/type_data.hpp"

#include "headers/postcondition.hpp"

namespace Semantics
{

TypeData::TypeData(
	SymbolData< boost::shared_ptr< Type > >::SymbolDataKey const & _type,
	Scope _scope
)
	: SymbolData< boost::shared_ptr< Type > >( _type, _scope )
	, m_memoryCapacity( 4 )
{
}

unsigned
TypeData::getMemoryCapacity() const
{
	return m_memoryCapacity;
}

}
