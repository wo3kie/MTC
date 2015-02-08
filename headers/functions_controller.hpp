#ifndef __SEMANTICS_FUNCTIONS_CONTROLLER_HPP__
#define __SEMANTICS_FUNCTIONS_CONTROLLER_HPP__

#include "headers/symbols_table.hpp"
#include "headers/function_data.hpp"

#include <loki/Singleton.h>

namespace Semantics
{

typedef SymbolsTable< FunctionData > FunctionsTable;

class FunctionsController
{
public:
	typedef FunctionsTable::Handler Handler;

public:
	Handler insert( FunctionData const & _data )
		{ return m_functionsTable.insert( _data ); }
		
 	Handler getHandler( std::string const & _name, Scope const & _scope ) const
 		{ return m_functionsTable.getHandler( _name, _scope ); }
 		
 	FunctionData getData( Handler _handler ) const
 		{ return m_functionsTable.getData( _handler ); }

protected:
	FunctionsTable m_functionsTable;
};

typedef Loki::SingletonHolder< FunctionsController > FunctionsControllerSingleton;

}

#endif
