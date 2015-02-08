#include "headers/ph.hpp"

#include "headers/string_data.hpp"

#include "headers/postcondition.hpp"
#include "headers/symbols_controller_factory.hpp"
#include "headers/type_data.hpp"

namespace Semantics
{

StringData::StringData(
	std::string const & _string,
	Scope _scope
)
	: SymbolData< std::string >( _string, _scope )
{	
	//m_type = SymbolsControllerFactory::createTypesController().insert(
	//	TypeData( "string" ) );
	
	POSTCONDITION1( ! getKey().empty() )
}

std::string
StringData::getString() const
{
	return getKey();
}

Scope
StringData::getScope() const
{
	return SymbolData< std::string >::getScope();
}

TypesController::Handler
StringData::getType() const
{
	return m_type;
}

}
