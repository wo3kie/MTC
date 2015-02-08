#ifndef __SEMANTICS_STRINGS_CONTROLLER_HPP__
#define __SEMANTICS_STRINGS_CONTROLLER_HPP__

#include "headers/symbols_table.hpp"
#include "headers/string_data.hpp"

#include <loki/Singleton.h>

namespace CodeGenerating
{

class CodeGenerator;

}

namespace Semantics
{

typedef SymbolsTable< StringData > StringsTable;

class StringsController
{
public:
	typedef StringsTable::Handler Handler;

public:
	Handler insert( StringData const & _data );
 	Handler getHandler( std::string const & _name, Scope const & _scope ) const;
 	StringData getData( Handler _handler ) const;
 	
 	void generateCode( CodeGenerating::CodeGenerator const & _cG ) const;

protected:
	StringsTable m_stringsTable;
};

typedef Loki::SingletonHolder< StringsController > StringsControllerSingleton;

}

#endif
