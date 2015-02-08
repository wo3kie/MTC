#ifndef __SEMANTICS_STRING_DATA_HPP__
#define __SEMANTICS_STRING_DATA_HPP__

#include "headers/symbol_data.hpp"
#include "headers/types_controller.hpp"

namespace Semantics
{

class StringData
	: public SymbolData< std::string >
{
public:	
	/* compiler's generated copy constructor is fine */
	/* compiler's generated destructor is fine */
	/* compiler's generated operator= is fine */
	
	StringData(
		std::string const & _string,
		Scope _scope );
		
	std::string getString() const;
	Scope getScope() const;
	TypesController::Handler getType() const;
	
private:
	TypesController::Handler m_type;
};

}

#endif
