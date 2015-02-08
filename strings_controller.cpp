
#include "headers/ph.hpp"

#include "headers/strings_controller.hpp"

#include "headers/code_generator.hpp"

namespace Semantics
{

StringsController::Handler
StringsController::insert( StringData const & _data )
{
	return m_stringsTable.insert( _data );
}

StringsController::Handler
StringsController::getHandler(
	std::string const & _name,
	Scope const & _scope
) const
{
	return m_stringsTable.getHandler( _name, _scope );
}

StringData
StringsController::getData(
	StringsController::Handler _handler
) const
{
	return m_stringsTable.getData( _handler );
}

void
StringsController::generateCode( CodeGenerating::CodeGenerator const & _cG ) const
{
	using std::cout;
	using std::endl;
		
	StringsTable::const_iterator current( m_stringsTable.begin() );
	StringsTable::const_iterator const begin( m_stringsTable.begin() );
	StringsTable::const_iterator const end( m_stringsTable.end() );
		
	if ( current == end )
	{
		return;
	}
		
	cout << endl;
	
	cout << _cG.generateReadOnlySection() << endl;
	
	cout << endl;

	for ( /*empty*/ ; current != end ; ++current )
	{
		cout 
			<< _cG.generateStringLabelPattern()
			<< getHandler( current->getString(), current->getScope() ).getRawHandler()
			<< ':'
			<< endl
			<< _cG.generateTabulatorsAsString( 1 )
			<< _cG.generateStringType()
			<< ' '
			<< current->getString()
			<< endl;
	}

	cout << endl;
}

}
