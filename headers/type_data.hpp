#ifndef __SEMANTICS_TYPE_DATA_HPP__
#define __SEMANTICS_TYPE_DATA_HPP__

#include "headers/symbol_data.hpp"
#include "headers/type.hpp"

namespace Semantics
{

class TypeData
	: public SymbolData< boost::shared_ptr< Type > >
{
public:
	explicit TypeData(
		SymbolData< boost::shared_ptr< Type > >::SymbolDataKey const & _type,
		Scope _scope = Scope() );
	
	/* compiler's generated copy constructor is fine */
	/* compiler's generated destructor is fine */
	/* compiler's generated operator= is fine */
	
	unsigned getMemoryCapacity() const;
	
private:
	unsigned m_memoryCapacity;
};

}

#endif
