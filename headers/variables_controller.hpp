#ifndef __SEMANTICS_VARIABLE_CONTROLLER_HPP__
#define __SEMANTICS_VARIABLE_CONTROLLER_HPP__

#include "headers/symbols_table.hpp"
#include "headers/variable_data.hpp"

#include <loki/Singleton.h>

#include <map>

namespace Semantics
{

class TypesController;

typedef SymbolsTable< VariableData > VariablesTable;

class VariablesController
{
public:
	typedef VariablesTable::Handler Handler;

public:
	Handler insert( VariableData const & _data );
 	Handler getHandler( std::string const & _name, Scope const & _scope ) const;
 	VariableData getData( Handler _handler ) const;

	unsigned getVariablesCapacity( Scope _scope ) const;
	void calculateVariablesOffsetOnStack( TypesController const & _typesController );

protected:
	VariablesTable m_variablesTable;
	
	std::map< unsigned, unsigned > m_memoryCapacity;
};

typedef Loki::SingletonHolder< VariablesController > VariablesControllerSingleton;

}

#endif
